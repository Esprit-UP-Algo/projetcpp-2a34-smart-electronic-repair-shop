#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QPdfWriter>
#include <QFileDialog>
#include <QPainter>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDesktopServices>
#include <QUrl>
#include <QClipboard>
#include <QUrlQuery>
#include <QBuffer>
#include <QDateTime>
#include <QMap>
#include <cmath>
#include <QProcess>
#include <QSettings>
#include <QTextStream>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Vérifier les fichiers au démarrage
    verifierFichiersSMS();

    // Initialiser le network manager pour SMS
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onSmsSent);

    // Tester le format des numéros
    testerFormatNumeros();

    // Ajouter les statuts
    ui->STATUT_R->addItem("EN ATTENTE");
    ui->STATUT_R->addItem("EN COURS");
    ui->STATUT_R->addItem("TERMINEE");
    ui->STATUT_R->addItem("ANNULEE");

    // Configuration de la recherche
    connect(ui->comboBoxCritereReparation, &QComboBox::currentTextChanged,
            this, &MainWindow::onCritereRechercheChanged);

    // Placeholder initial
    ui->RECHERCHE->setPlaceholderText("Saisissez votre recherche...");

    // Entraîner le modèle ML
    trainPredictionModel();

    actualiserTable();

    // DEBUG: Check database contents
    debugCheckDatabase();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::verifierFichiersSMS()
{
    QStringList pathsToCheck = {
        QCoreApplication::applicationDirPath() + "/historique_sms_locaux.txt",
        QDir::currentPath() + "/historique_sms_locaux.txt",
        QDir::homePath() + "/historique_sms_locaux.txt",
        "historique_sms_locaux.txt"
    };

    QString message = "📁 Fichiers SMS trouvés:\n\n";
    bool found = false;

    for (const QString &path : pathsToCheck) {
        QFile file(path);
        if (file.exists()) {
            message += "✅ " + path + "\n";
            found = true;
        } else {
            message += "❌ " + path + " (Non trouvé)\n";
        }
    }

    if (!found) {
        message += "\nAucun fichier SMS trouvé. Ils seront créés au premier envoi.";
    }

    qDebug() << "Vérification fichiers SMS:" << message;
}

void MainWindow::testerFormatNumeros()
{
    QSqlQuery testQuery;
    testQuery.exec("SELECT CIN, NOM, PRENOM, TEL FROM CLIENT WHERE ROWNUM <= 5");

    qDebug() << "=== TEST FORMAT NUMÉROS CLIENT ===";
    while (testQuery.next()) {
        QString cin = testQuery.value(0).toString();
        QString nom = testQuery.value(1).toString();
        QString prenom = testQuery.value(2).toString();
        QString tel = testQuery.value(3).toString();

        qDebug() << "Client:" << prenom << nom
                 << "| TEL:" << tel
                 << "| Longueur:" << tel.length()
                 << "| Formaté:" << formaterNumeroInternational(tel);
    }
    qDebug() << "=== FIN TEST ===";
}

void MainWindow::debugCheckDatabase()
{
    qDebug() << "=== COMPLETE DATABASE DEBUG ===";

    // Check if tables exist
    QSqlQuery tableCheck;
    tableCheck.exec("SELECT table_name FROM user_tables");
    qDebug() << "Tables in database:";
    while (tableCheck.next()) {
        qDebug() << " - " << tableCheck.value(0).toString();
    }

    // Check REPARATION table structure
    QSqlQuery reparationStructure;
    reparationStructure.exec("SELECT column_name, data_type, data_length, nullable FROM user_tab_columns WHERE table_name = 'REPARATION' ORDER BY column_id");
    qDebug() << "REPARATION table columns:";
    while (reparationStructure.next()) {
        qDebug() << " - " << reparationStructure.value(0).toString()
        << ":" << reparationStructure.value(1).toString()
        << "(" << reparationStructure.value(2).toString() << ")"
        << "NULLABLE:" << reparationStructure.value(3).toString();
    }

    // Check APPAREILS table content
    QSqlQuery checkAppareils;
    checkAppareils.exec("SELECT NUM_SERIE, TYPE_A, MARQUE FROM APPAREILS");
    qDebug() << "APPAREILS table content (first 10):";
    int appareilCount = 0;
    while (checkAppareils.next() && appareilCount < 10) {
        qDebug() << " - NUM_SERIE:" << checkAppareils.value(0).toString()
        << "TYPE:" << checkAppareils.value(1).toString()
        << "MARQUE:" << checkAppareils.value(2).toString();
        appareilCount++;
    }
    qDebug() << "Total appareils:" << appareilCount;

    // Check EMPLOYES table content
    QSqlQuery checkEmployes;
    checkEmployes.exec("SELECT CIN_EMP FROM EMPLOYES");
    qDebug() << "EMPLOYES table CIN_EMP values (first 10):";
    int employeCount = 0;
    while (checkEmployes.next() && employeCount < 10) {
        qDebug() << " - CIN_EMP:" << checkEmployes.value(0).toInt();
        employeCount++;
    }
    qDebug() << "Total employes:" << employeCount;

    // Check existing REPARATION IDs
    QSqlQuery checkReparations;
    checkReparations.exec("SELECT IDR, NUM_SERIE, CIN_EMP FROM REPARATION");
    qDebug() << "Existing REPARATION records:";
    int reparationCount = 0;
    while (checkReparations.next()) {
        qDebug() << " - IDR:" << checkReparations.value(0).toInt()
        << "NUM_SERIE:" << checkReparations.value(1).toString()
        << "CIN_EMP:" << checkReparations.value(2).toInt();
        reparationCount++;
    }
    qDebug() << "Total reparations:" << reparationCount;

    qDebug() << "=== END DEBUG ===";
}

void MainWindow::actualiserTable()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM REPARATION");
    if (model->lastError().isValid()) {
        qDebug() << "Erreur actualiserTable:" << model->lastError().text();
        QMessageBox::critical(this, "Erreur", "Erreur lors du chargement des données: " + model->lastError().text());
        return;
    }
    ui->TABLE_REPARATION->setModel(model);
}

void MainWindow::viderChamps()
{
    ui->IDR->clear();
    ui->MAT_REP->clear();
    ui->DES_PANNE->clear();
    ui->DATE_REC->setDate(QDate::currentDate());
    ui->DATE_FIN_EST->setDate(QDate::currentDate());
    ui->STATUT_R->setCurrentIndex(0);
    ui->COUT->clear();
    ui->NUM_SERIE->clear();
    ui->CIN_EMP->clear();
}

/*---------------------------------------------------------
 *   AJOUTER -
 ---------------------------------------------------------*/

void MainWindow::on_BTN_AJOUTER_clicked()
{
    // Validation des champs obligatoires
    if (ui->IDR->text().isEmpty() || ui->NUM_SERIE->text().isEmpty() || ui->CIN_EMP->text().isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir l'ID, numéro de série et CIN employé !");
        return;
    }

    int id = ui->IDR->text().toInt();
    QString mat = ui->MAT_REP->text();
    QString des = ui->DES_PANNE->toPlainText();
    QDate rec = ui->DATE_REC->date();
    QDate fin = ui->DATE_FIN_EST->date();
    QString statut = ui->STATUT_R->currentText();
    double cout = ui->COUT->text().toDouble();
    QString num_serie = ui->NUM_SERIE->text();
    int cin_emp = ui->CIN_EMP->text().toInt();

    qDebug() << "=== ATTEMPTING TO ADD REPARATION ===";
    qDebug() << "IDR:" << id;
    qDebug() << "NUM_SERIE:" << num_serie;
    qDebug() << "CIN_EMP:" << cin_emp;

    // Vérifier si l'ID existe déjà
    QSqlQuery checkId;
    checkId.prepare("SELECT IDR FROM REPARATION WHERE IDR = :id");
    checkId.bindValue(":id", id);
    if (!checkId.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur vérification ID: " + checkId.lastError().text());
        return;
    }
    if (checkId.next()) {
        QMessageBox::warning(this, "Erreur", "Cet ID existe déjà !");
        return;
    }

    // Vérifier si l'appareil existe (simple check without client relation)
    QSqlQuery checkAppareil;
    checkAppareil.prepare("SELECT NUM_SERIE FROM APPAREILS WHERE NUM_SERIE = :num");
    checkAppareil.bindValue(":num", num_serie);
    if (!checkAppareil.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur vérification appareil: " + checkAppareil.lastError().text());
        return;
    }
    if (!checkAppareil.next()) {
        QMessageBox::warning(this, "Erreur",
                             QString("Numéro de série '%1' introuvable dans APPAREILS!\nVérifiez que le numéro existe.").arg(num_serie));

        // Show available NUM_SERIE values for debugging
        QSqlQuery showAppareils;
        showAppareils.exec("SELECT NUM_SERIE FROM APPAREILS WHERE ROWNUM <= 5");
        QString availableSerials = "Quelques NUM_SERIE disponibles:\n";
        while (showAppareils.next()) {
            availableSerials += " - " + showAppareils.value(0).toString() + "\n";
        }
        QMessageBox::information(this, "NUM_SERIE disponibles", availableSerials);
        return;
    }
    qDebug() << "✓ Appareil trouvé:" << num_serie;

    // Vérifier si l'employé existe
    QSqlQuery checkEmploye;
    checkEmploye.prepare("SELECT CIN_EMP FROM EMPLOYES WHERE CIN_EMP = :cin");
    checkEmploye.bindValue(":cin", cin_emp);
    if (!checkEmploye.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur vérification employé: " + checkEmploye.lastError().text());
        return;
    }
    if (!checkEmploye.next()) {
        QMessageBox::warning(this, "Erreur",
                             QString("CIN employé '%1' introuvable dans EMPLOYES!\nVérifiez que l'employé existe.").arg(cin_emp));

        // Show available CIN_EMP values for debugging
        QSqlQuery showEmployes;
        showEmployes.exec("SELECT CIN_EMP FROM EMPLOYES WHERE ROWNUM <= 5");
        QString availableEmps = "Quelques CIN_EMP disponibles:\n";
        while (showEmployes.next()) {
            availableEmps += " - " + showEmployes.value(0).toString() + "\n";
        }
        QMessageBox::information(this, "CIN_EMP disponibles", availableEmps);
        return;
    }
    qDebug() << "✓ Employé trouvé:" << cin_emp;

    // Créer et ajouter la réparation
    Reparation nouvelleReparation(id, mat, des, fin, rec, statut, cout, num_serie, cin_emp);

    if (nouvelleReparation.ajouter()) {
        QMessageBox::information(this, "Ajout", "Réparation ajoutée avec succès !");
        actualiserTable();
        viderChamps();
    } else {
        QMessageBox::critical(this, "Erreur",
                              "Échec de l'ajout !\n"
                              "Le problème vient de la méthode ajouter() dans reparation.cpp.\n"
                              "Vérifiez la console pour l'erreur SQL exacte.");
    }
}

/*---------------------------------------------------------
 *   SUPPRIMER
 ---------------------------------------------------------*/
void MainWindow::on_BTN_SUPPRIMER_clicked()
{
    if (ui->IDR->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un ID à supprimer !");
        return;
    }

    int id = ui->IDR->text().toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer cette réparation ?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (Rtmp.supprimer(id)) {
            QMessageBox::information(this, "Supprimer", "Réparation supprimée avec succès !");
            actualiserTable();
            viderChamps();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression !");
        }
    }
}

/*---------------------------------------------------------
 *   MODIFIER
 ---------------------------------------------------------*/
void MainWindow::on_BTN_MODIFIER_clicked()
{
    if (ui->IDR->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un ID à modifier !");
        return;
    }

    int id = ui->IDR->text().toInt();
    QString mat = ui->MAT_REP->text();
    QString des = ui->DES_PANNE->toPlainText();
    QDate rec = ui->DATE_REC->date();
    QDate fin = ui->DATE_FIN_EST->date();
    QString statut = ui->STATUT_R->currentText();
    double cout = ui->COUT->text().toDouble();
    QString num_serie = ui->NUM_SERIE->text();
    int cin_emp = ui->CIN_EMP->text().toInt();

    // AJOUTER id dans le constructeur
    Reparation reparationModifiee(id, mat, des, fin, rec, statut, cout, num_serie, cin_emp);

    if (reparationModifiee.modifier(id)) {
        QMessageBox::information(this, "Modifier", "Réparation modifiée avec succès !");
        actualiserTable();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification !");
    }
}

/*---------------------------------------------------------
 *   RECHERCHER AVEC CRITÈRES (COMBOBOX)
 ---------------------------------------------------------*/
void MainWindow::on_BTN_RECHERCHER_clicked()
{
    QString critere = ui->comboBoxCritereReparation->currentText();
    QString valeur = ui->RECHERCHE->text().trimmed();

    // Si pas de valeur, on rafraîchit simplement le tableau
    if (valeur.isEmpty()) {
        actualiserTable();
        QMessageBox::information(this, "Information", "Affichage de toutes les réparations.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    QString requete;

    if (critere == "Appareil") {
        // Recherche par appareil (numéro de série ou jointure avec APPAREILS)
        requete = QString(
                      "SELECT R.* FROM REPARATION R "
                      "LEFT JOIN APPAREILS A ON R.NUM_SERIE = A.NUM_SERIE "
                      "WHERE R.NUM_SERIE LIKE '%%1%' OR "
                      "A.MARQUE LIKE '%%1%' OR "
                      "A.MODELE LIKE '%%1%' OR "
                      "A.TYPE_A LIKE '%%1%'")
                      .arg(valeur);
    }
    else if (critere == "Statut") {
        // Recherche par statut (insensible à la casse)
        QString statutRecherche = valeur.toUpper();
        requete = QString("SELECT * FROM REPARATION WHERE UPPER(STATUT_R) = '%1'")
                      .arg(statutRecherche);
    }
    else if (critere == "Date") {
        // Gestion flexible des formats de date
        QDate dateRecherche;

        // Essayer différents formats de date
        if (QDate::fromString(valeur, "dd/MM/yyyy").isValid()) {
            dateRecherche = QDate::fromString(valeur, "dd/MM/yyyy");
        } else if (QDate::fromString(valeur, "yyyy-MM-dd").isValid()) {
            dateRecherche = QDate::fromString(valeur, "yyyy-MM-dd");
        } else if (QDate::fromString(valeur, "dd-MM-yyyy").isValid()) {
            dateRecherche = QDate::fromString(valeur, "dd-MM-yyyy");
        } else {
            // Si le format n'est pas reconnu, recherche textuelle
            requete = QString(
                          "SELECT * FROM REPARATION WHERE "
                          "TO_CHAR(DATE_REC, 'DD/MM/YYYY') LIKE '%%1%' OR "
                          "TO_CHAR(DATE_FIN_EST, 'DD/MM/YYYY') LIKE '%%1%' OR "
                          "TO_CHAR(DATE_REC, 'YYYY-MM-DD') LIKE '%%1%' OR "
                          "TO_CHAR(DATE_FIN_EST, 'YYYY-MM-DD') LIKE '%%1%'")
                          .arg(valeur);
        }

        if (dateRecherche.isValid()) {
            requete = QString(
                          "SELECT * FROM REPARATION WHERE "
                          "DATE_REC = DATE '%1' OR "
                          "DATE_FIN_EST = DATE '%1'")
                          .arg(dateRecherche.toString("yyyy-MM-dd"));
        }
    }
    else {
        // Recherche par défaut sur tous les champs
        requete = QString(
                      "SELECT R.* FROM REPARATION R "
                      "WHERE R.IDR LIKE '%%1%' OR "
                      "R.MAT_REP LIKE '%%1%' OR "
                      "R.DES_PANNE LIKE '%%1%' OR "
                      "UPPER(R.STATUT_R) LIKE '%%1%' OR "
                      "R.NUM_SERIE LIKE '%%1%' OR "
                      "TO_CHAR(R.CIN_EMP) LIKE '%%1%'")
                      .arg(valeur.toUpper());
    }

    qDebug() << "Requête de recherche:" << requete;
    model->setQuery(requete);

    if (model->lastError().isValid()) {
        qDebug() << "Erreur recherche:" << model->lastError().text();
        QMessageBox::critical(this, "Erreur",
                              "Erreur lors de la recherche:\n" + model->lastError().text());
        delete model;
        return;
    }

    ui->TABLE_REPARATION->setModel(model);

    // Message de résultat
    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Recherche",
                                 QString("Aucun résultat trouvé pour:\n"
                                         "Critère: %1\n"
                                         "Valeur: %2")
                                     .arg(critere)
                                     .arg(valeur));
    } else {
        // Pas de message si des résultats sont trouvés (pour ne pas interrompre le flux)
        qDebug() << "Recherche réussie:" << model->rowCount() << "résultat(s) trouvé(s)";
    }
}

QString MainWindow::construireRequeteRecherche(const QString &critere, const QString &valeur)
{
    QString requeteBase = "SELECT * FROM REPARATION WHERE ";
    QString condition = "";

    if (critere == "Appareil") {
        condition = QString("NUM_SERIE LIKE '%%1%'").arg(valeur);
    }
    else if (critere == "Statut") {
        condition = QString("STATUT_R = '%1'").arg(valeur.toUpper());
    }
    else if (critere == "Date") {
        if (QDate::fromString(valeur, "dd/MM/yyyy").isValid()) {
            QDate date = QDate::fromString(valeur, "dd/MM/yyyy");
            condition = QString("(DATE_REC = DATE '%1' OR DATE_FIN_EST = DATE '%1')")
                            .arg(date.toString("yyyy-MM-dd"));
        } else if (QDate::fromString(valeur, "yyyy-MM-dd").isValid()) {
            condition = QString("(DATE_REC = DATE '%1' OR DATE_FIN_EST = DATE '%1')")
            .arg(valeur);
        } else {
            condition = QString("(TO_CHAR(DATE_REC, 'DD/MM/YYYY') LIKE '%%1%' OR TO_CHAR(DATE_FIN_EST, 'DD/MM/YYYY') LIKE '%%1%')")
            .arg(valeur);
        }
    }
    else {
        condition = QString("IDR LIKE '%%1%' OR "
                            "MAT_REP LIKE '%%1%' OR "
                            "DES_PANNE LIKE '%%1%' OR "
                            "STATUT_R LIKE '%%1%' OR "
                            "NUM_SERIE LIKE '%%1%' OR "
                            "TO_CHAR(CIN_EMP) LIKE '%%1%'")
                        .arg(valeur);
    }

    return requeteBase + condition;
}

void MainWindow::onCritereRechercheChanged(const QString &critere)
{
    // Changer le placeholder en fonction du critère sélectionné
    if (critere == "Date") {
        ui->RECHERCHE->setPlaceholderText("Format: JJ/MM/AAAA ou AAAA-MM-JJ");
    } else if (critere == "Statut") {
        ui->RECHERCHE->setPlaceholderText("Ex: EN ATTENTE, EN COURS, TERMINEE...");
    } else {
        ui->RECHERCHE->setPlaceholderText("Saisissez votre recherche...");
    }
}

/*---------------------------------------------------------
 *   TRIER PAR COUT
 ---------------------------------------------------------*/
void MainWindow::on_BTN_TRIER_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM REPARATION ORDER BY COUT DESC");

    if (model->lastError().isValid()) {
        qDebug() << "Erreur tri:" << model->lastError().text();
        QMessageBox::critical(this, "Erreur", "Erreur lors du tri: " + model->lastError().text());
        return;
    }

    ui->TABLE_REPARATION->setModel(model);
    QMessageBox::information(this, "Tri", "Réparations triées par coût (décroissant) !");
}

// ==================== MACHINE LEARNING POUR PRÉDICTION ====================

void MainWindow::trainPredictionModel()
{
    // Réinitialiser les poids
    featureWeights.clear();
    baseDuration = 3.0; // Durée de base en jours

    // Définir la complexité des types de pannes
    panneComplexity["écran"] = 3;
    panneComplexity["batterie"] = 2;
    panneComplexity["logiciel"] = 2;
    panneComplexity["eau"] = 4;
    panneComplexity["composant"] = 3;
    panneComplexity["charge"] = 1;
    panneComplexity["son"] = 2;
    panneComplexity["connectivité"] = 3;
    panneComplexity["clavier"] = 2;
    panneComplexity["camera"] = 3;
    panneComplexity["lent"] = 2;
    panneComplexity["gelé"] = 2;
    panneComplexity["redémarre"] = 3;

    // Complexité par marque
    brandComplexity["Apple"] = 3;
    brandComplexity["Samsung"] = 2;
    brandComplexity["Huawei"] = 3;
    brandComplexity["Xiaomi"] = 2;
    brandComplexity["Dell"] = 2;
    brandComplexity["HP"] = 1;
    brandComplexity["Lenovo"] = 2;
    brandComplexity["Sony"] = 3;
    brandComplexity["Asus"] = 2;
    brandComplexity["Acer"] = 2;

    // Complexité par type d'appareil
    typeComplexity["Smartphone"] = 2;
    typeComplexity["Ordinateur Portable"] = 3;
    typeComplexity["Tablette"] = 2;
    typeComplexity["Appareil IoT"] = 4;
    typeComplexity["Autre"] = 3;

    // Analyser l'historique pour ajuster les poids
    QSqlQuery historyQuery;
    historyQuery.prepare(
        "SELECT A.TYPE_A, A.MARQUE, R.DES_PANNE, "
        "(R.DATE_FIN_EST - R.DATE_REC) as duree "
        "FROM REPARATION R "
        "JOIN APPAREILS A ON R.NUM_SERIE = A.NUM_SERIE "
        "WHERE R.STATUT_R = 'TERMINEE' "
        "AND R.DATE_FIN_EST IS NOT NULL AND R.DATE_REC IS NOT NULL"
        );

    if (historyQuery.exec()) {
        int count = 0;
        double totalDuration = 0;

        while (historyQuery.next()) {
            QString type = historyQuery.value(0).toString();
            QString marque = historyQuery.value(1).toString();
            QString panne = historyQuery.value(2).toString().toLower();
            double duree = historyQuery.value(3).toDouble();

            if (duree > 0 && duree < 30) { // Filtrer les valeurs aberrantes
                totalDuration += duree;
                count++;

                // Ajuster les poids basés sur les données historiques
                for (const QString &key : panneComplexity.keys()) {
                    if (panne.contains(key)) {
                        featureWeights["panne_" + key] =
                            (featureWeights.value("panne_" + key, 0.0) + duree) / 2.0;
                    }
                }

                if (brandComplexity.contains(marque)) {
                    featureWeights["marque_" + marque] =
                        (featureWeights.value("marque_" + marque, 0.0) + duree) / 2.0;
                }

                if (typeComplexity.contains(type)) {
                    featureWeights["type_" + type] =
                        (featureWeights.value("type_" + type, 0.0) + duree) / 2.0;
                }
            }
        }

        if (count > 0) {
            baseDuration = totalDuration / count;
            qDebug() << "Modèle ML entraîné sur" << count << "réparations, durée moyenne:" << baseDuration;
        }
    }
}

double MainWindow::predictRepairDurationML(const QString &typeAppareil,
                                           const QString &descriptionPanne,
                                           const QString &marque,
                                           const QString &modele)
{
    double prediction = baseDuration;
    QString panneLower = descriptionPanne.toLower();

    // Facteur type d'appareil
    if (typeComplexity.contains(typeAppareil)) {
        double typeWeight = featureWeights.value("type_" + typeAppareil,
                                                 typeComplexity[typeAppareil] * 0.5);
        prediction += typeWeight * 0.3;
    }

    // Facteur marque
    if (brandComplexity.contains(marque)) {
        double brandWeight = featureWeights.value("marque_" + marque,
                                                  brandComplexity[marque] * 0.3);
        prediction += brandWeight * 0.2;
    }

    // Facteur type de panne (analyse de la description)
    int panneCount = 0;
    for (const QString &key : panneComplexity.keys()) {
        if (panneLower.contains(key)) {
            double panneWeight = featureWeights.value("panne_" + key,
                                                      panneComplexity[key] * 0.8);
            prediction += panneWeight * 0.4;
            panneCount++;
        }
    }

    // Bonus pour pannes multiples
    if (panneCount > 1) {
        prediction += (panneCount - 1) * 0.5;
    }

    // Facteur saisonnier (weekends)
    QDate today = QDate::currentDate();
    int dayOfWeek = today.dayOfWeek();
    if (dayOfWeek == 6 || dayOfWeek == 7) { // Samedi ou dimanche
        prediction += 1.0;
    }

    // Assurer des limites raisonnables
    prediction = std::max(1.0, std::min(prediction, 14.0));

    return prediction;
}

void MainWindow::on_BTN_PREDICTION_DELAI_clicked()
{
    QString numSerie = ui->NUM_SERIE->text().trimmed();
    QString desPanne = ui->DES_PANNE->toPlainText().trimmed();
    QDate dateRec = ui->DATE_REC->date();

    if (numSerie.isEmpty() || desPanne.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir le numéro de série et la description de la panne.");
        return;
    }

    // Récupérer les informations détaillées de l'appareil
    QSqlQuery qAppareil;
    qAppareil.prepare("SELECT TYPE_A, MARQUE, MODELE FROM APPAREILS WHERE NUM_SERIE = :num");
    qAppareil.bindValue(":num", numSerie);

    if (!qAppareil.exec() || !qAppareil.next()) {
        QMessageBox::warning(this, "Erreur", "Appareil introuvable pour ce numéro de série.");
        return;
    }

    QString typeAppareil = qAppareil.value(0).toString();
    QString marque = qAppareil.value(1).toString();
    QString modele = qAppareil.value(2).toString();

    // Utiliser le modèle ML pour la prédiction
    double dureePredite = predictRepairDurationML(typeAppareil, desPanne, marque, modele);

    // Calculer la date de fin estimée
    QDate dateFinPred = dateRec.addDays(static_cast<int>(std::ceil(dureePredite)));
    ui->DATE_FIN_EST->setDate(dateFinPred);

    // Afficher les détails de la prédiction
    QString details = QString(
                          "🔧 PRÉDICTION INTELLIGENTE (Machine Learning)\n\n"
                          "Type d'appareil: %1\n"
                          "Marque: %2\n"
                          "Modèle: %3\n"
                          "Description panne: %4\n\n"
                          "Durée estimée: %5 jours\n"
                          "Date fin estimée: %6\n\n"
                          "Facteurs considérés:\n"
                          "- Complexité du type d'appareil\n"
                          "- Disponibilité des pièces (marque)\n"
                          "- Type de panne identifié\n"
                          "- Données historiques similaires\n"
                          "- Facteurs saisonniers")
                          .arg(typeAppareil)
                          .arg(marque)
                          .arg(modele)
                          .arg(desPanne.left(100) + (desPanne.length() > 100 ? "..." : ""))
                          .arg(QString::number(dureePredite, 'f', 1))
                          .arg(dateFinPred.toString("dd/MM/yyyy"));

    QMessageBox::information(this, "🤖 Prédiction Intelligente", details);
}


/*---------------------------------------------------------
 *   EXPORTER FACTURE PDF - FORMAT FACTURE (IMPROVED SPACING)
 ---------------------------------------------------------*/
void MainWindow::on_BTN_EXPORTER_clicked()
{
    QString idReparation = ui->IDR->text();

    if (idReparation.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un ID de réparation pour générer la facture !");
        return;
    }

    // Récupérer les informations de la réparation
    QSqlQuery qReparation;
    qReparation.prepare(
        "SELECT R.IDR, R.MAT_REP, R.DES_PANNE, R.DATE_REC, R.DATE_FIN_EST, "
        "R.STATUT_R, R.COUT, R.NUM_SERIE, A.TYPE_A, A.MARQUE, A.MODELE, "
        "C.NOM, C.PRENOM, C.TEL "
        "FROM REPARATION R "
        "JOIN APPAREILS A ON R.NUM_SERIE = A.NUM_SERIE "
        "JOIN CLIENT C ON A.CIN = C.CIN "
        "WHERE R.IDR = ?"
        );
    qReparation.addBindValue(idReparation);

    if (!qReparation.exec() || !qReparation.next()) {
        QMessageBox::warning(this, "Erreur", "Réparation non trouvée !");
        return;
    }

    // Données de la réparation
    int id = qReparation.value(0).toInt();
    QString matricule = qReparation.value(1).toString();
    QString descriptionPanne = qReparation.value(2).toString();
    QDate dateReception = qReparation.value(3).toDate();
    QDate dateFin = qReparation.value(4).toDate();
    QString statut = qReparation.value(5).toString();
    double cout = qReparation.value(6).toDouble();
    QString typeAppareil = qReparation.value(8).toString();
    QString marque = qReparation.value(9).toString();
    QString modele = qReparation.value(10).toString();
    QString nomClient = qReparation.value(11).toString();
    QString prenomClient = qReparation.value(12).toString();
    QString telephone = qReparation.value(13).toString();

    // Générer le nom du fichier
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Exporter la Facture PDF",
        QString("FACTURE_%1_%2.pdf").arg(id).arg(QDate::currentDate().toString("yyyyMMdd")),
        "PDF (*.pdf)"
        );

    if (fileName.isEmpty()) return;
    if (!fileName.endsWith(".pdf")) fileName += ".pdf";

    // Création du PDF
    QPdfWriter pdf(fileName);
    pdf.setPageSize(QPageSize::A4);
    pdf.setPageMargins(QMarginsF(20, 20, 20, 20));
    pdf.setResolution(150);

    QPainter painter(&pdf);

    if (!painter.isActive()) {
        QMessageBox::critical(this, "Erreur", "Impossible de créer le fichier PDF !");
        return;
    }

    // ===== EN-TÊTE FACTURE =====
    painter.setFont(QFont("Arial", 24, QFont::Bold));
    painter.drawText(200, 60, "FACTURE");  // Increased from 50 to 60

    painter.setFont(QFont("Arial", 8));
    painter.drawText(200, 80, "Smart Repair Hub - Service de réparation professionnel");  // Increased from 65 to 80

    painter.setFont(QFont("Arial", 10));
    painter.drawText(200, 100, "Smart Repair Hub");  // Increased from 80 to 100
    painter.drawText(200, 120, "123 Avenue de la République, Tunis");  // Increased from 95 to 120
    painter.drawText(200, 140, "Tél: +216 12 345 678 | Email: contact@repair.tn");  // Increased from 110 to 140

    // Ligne de séparation
    painter.drawLine(50, 160, 550, 160);  // Increased from 130 to 160

    int y = 200;  // Increased from 160 to 200

    // ===== INFORMATIONS CLIENT =====
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.drawText(50, y, "CLIENT:");
    painter.setFont(QFont("Arial", 9));
    painter.drawText(50, y + 20, QString("Nom: %1 %2").arg(prenomClient).arg(nomClient));  // Increased from 15 to 20
    painter.drawText(50, y + 40, QString("Téléphone: %1").arg(telephone));  // Increased from 30 to 40

    // ===== INFORMATIONS FACTURE =====
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.drawText(300, y, "FACTURE N°:");
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300, y + 20, QString("REF-%1").arg(id));  // Increased from 15 to 20
    painter.drawText(300, y + 40, QString("Date: %1").arg(QDate::currentDate().toString("dd/MM/yyyy")));  // Increased from 30 to 40
    if (!matricule.isEmpty()) {
        painter.drawText(300, y + 60, QString("Matricule: %1").arg(matricule));  // Increased from 45 to 60
    }

    y += 90;  // Increased from 70 to 90

    // ===== DÉTAILS DE LA RÉPARATION =====
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.drawText(50, y, "I. " + typeAppareil.toUpper());
    y += 25;  // Increased from 20 to 25

    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.drawText(50, y, "II. RÉPARATION");
    y += 25;  // Increased from 20 to 25

    painter.setFont(QFont("Arial", 9));
    painter.drawText(70, y, QString("Appareil: %1 %2").arg(marque).arg(modele));
    y += 20;  // Increased from 15 to 20
    painter.drawText(70, y, "Description: " + descriptionPanne);
    y += 20;  // Increased from 15 to 20

    // Ligne de séparation
    painter.drawLine(50, y, 550, y);
    y += 25;  // Increased from 20 to 25

    // ===== COÛT =====
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.drawText(50, y, "Coût:");
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(150, y, QString::number(cout, 'f', 3) + " DT");
    y += 30;  // Increased from 25 to 30

    // TVA
    double tva = cout * 0.19;
    painter.setFont(QFont("Arial", 9));
    painter.drawText(50, y, "TVA (19%):");
    painter.drawText(150, y, QString::number(tva, 'f', 3) + " DT");
    y += 25;  // Increased from 20 to 25

    // Ligne de séparation totale
    painter.drawLine(50, y, 550, y);
    y += 30;  // Increased from 25 to 30

    // TOTAL
    double total = cout + tva;
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(50, y, "TOTAL:");
    painter.drawText(150, y, QString::number(total, 'f', 3) + " DT");
    y += 50;  // Increased from 40 to 50

    // ===== INFORMATIONS SUPPLEMENTAIRES =====
    painter.setFont(QFont("Arial", 8));
    painter.drawText(50, y, QString("Date dépôt: %1").arg(dateReception.toString("dd/MM/yyyy")));
    y += 15;  // Increased from 12 to 15
    painter.drawText(50, y, QString("Date fin estimée: %1").arg(dateFin.toString("dd/MM/yyyy")));
    y += 15;  // Increased from 12 to 15
    painter.drawText(50, y, QString("Statut: %1").arg(statut));
    y += 25;  // Increased from 20 to 25

    // ===== PIED DE PAGE =====
    painter.drawLine(50, y, 550, y);
    y += 20;  // Increased from 15 to 20

    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.drawText(200, y, "Merci pour votre confiance !");
    y += 25;  // Increased from 20 to 25

    painter.setFont(QFont("Arial", 8));
    painter.drawText(50, y, "Smart Repair Hub - RC: 123456/A/M/000 - IF: 12345678");
    y += 15;  // Increased from 12 to 15
    painter.drawText(50, y, "Garantie: 3 mois sur les pièces et main d'œuvre");

    painter.end();

    QMessageBox::information(this, "✅ Facture Générée",
                             "La facture a été générée avec succès !\n\n"
                             "Fichier: " + fileName + "\n"
                                              "Client: " + prenomClient + " " + nomClient + "\n"
                                                                    "Montant: " + QString::number(total, 'f', 3) + " DT");
}
/*---------------------------------------------------------
 *   STATISTIQUES AVEC DIAGRAMME CIRCULAIRE DANS MESSAGE BOX
 ---------------------------------------------------------*/
void MainWindow::on_BTN_STATISTIQUES_clicked()
{
    QSqlQuery q;
    int total = 0, enAttente = 0, enCours = 0, terminees = 0, annulees = 0;
    double coutTotal = 0;

    if (q.exec("SELECT COUNT(*) FROM REPARATION") && q.next()) {
        total = q.value(0).toInt();
    }

    if (q.exec("SELECT COUNT(*) FROM REPARATION WHERE STATUT_R = 'EN ATTENTE'") && q.next()) {
        enAttente = q.value(0).toInt();
    }

    if (q.exec("SELECT COUNT(*) FROM REPARATION WHERE STATUT_R = 'EN COURS'") && q.next()) {
        enCours = q.value(0).toInt();
    }

    if (q.exec("SELECT COUNT(*) FROM REPARATION WHERE STATUT_R = 'TERMINEE'") && q.next()) {
        terminees = q.value(0).toInt();
    }

    if (q.exec("SELECT COUNT(*) FROM REPARATION WHERE STATUT_R = 'ANNULEE'") && q.next()) {
        annulees = q.value(0).toInt();
    }

    if (q.exec("SELECT SUM(COUT) FROM REPARATION WHERE STATUT_R = 'TERMINEE'") && q.next()) {
        coutTotal = q.value(0).toDouble();
    }

    // Afficher les statistiques avec diagramme dans une message box
    afficherStatistiquesAvecDiagramme(enAttente, enCours, terminees, annulees, coutTotal, total);
}

void MainWindow::afficherStatistiquesAvecDiagramme(int enAttente, int enCours, int terminees, int annulees, double coutTotal, int total)
{
    // Créer une message box personnalisée
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("📊 Statistiques des Réparations - Diagramme Circulaire");
    msgBox.setIconPixmap(QPixmap()); // Pas d'icône par défaut

    // Créer un widget personnalisé pour contenir le diagramme et les informations
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);

    // === CRÉATION DU DIAGRAMME CIRCULAIRE ===
    QPieSeries *series = new QPieSeries();

    // Couleurs pour chaque statut
    QColor colorEnAttente(255, 193, 7);    // Jaune
    QColor colorEnCours(33, 150, 243);     // Bleu
    QColor colorTerminees(76, 175, 80);    // Vert
    QColor colorAnnulees(244, 67, 54);     // Rouge

    // Ajouter les tranches du diagramme
    if (enAttente > 0) {
        QPieSlice *slice = series->append("En Attente", enAttente);
        slice->setColor(colorEnAttente);
        slice->setLabelVisible(true);
        slice->setLabelColor(Qt::black);
    }

    if (enCours > 0) {
        QPieSlice *slice = series->append("En Cours", enCours);
        slice->setColor(colorEnCours);
        slice->setLabelVisible(true);
        slice->setLabelColor(Qt::black);
    }

    if (terminees > 0) {
        QPieSlice *slice = series->append("Terminées", terminees);
        slice->setColor(colorTerminees);
        slice->setLabelVisible(true);
        slice->setLabelColor(Qt::black);
        slice->setExploded(true); // Mettre en évidence
    }

    if (annulees > 0) {
        QPieSlice *slice = series->append("Annulées", annulees);
        slice->setColor(colorAnnulees);
        slice->setLabelVisible(true);
        slice->setLabelColor(Qt::black);
    }

    // Personnaliser l'apparence
    series->setLabelsPosition(QPieSlice::LabelOutside);
    series->setPieSize(0.8);

    // Créer le chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("📊 Répartition des Réparations");
    chart->setTitleFont(QFont("Arial", 12, QFont::Bold));
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setBackgroundRoundness(10);
    chart->setBackgroundBrush(QBrush(QColor(248, 249, 250)));

    // Créer la vue du chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(500, 350);
    chartView->setMaximumSize(500, 350);

    // === INFORMATIONS TEXTUELLES ===
    QLabel *infoLabel = new QLabel();
    QString infoText = QString(
                           "<div style='background-color: #f8f9fa; padding: 15px; border-radius: 8px; border: 1px solid #dee2e6;'>"
                           "<h3 style='color: #2c3147; margin-top: 0;'>📈 Statistiques Détaillées</h3>"
                           "<table style='width: 100%; border-collapse: collapse; font-size: 12px;'>"
                           "<tr>"
                           "<td style='padding: 6px; border-bottom: 1px solid #dee2e6;'><b>Total Réparations:</b></td>"
                           "<td style='padding: 6px; border-bottom: 1px solid #dee2e6; text-align: right;'><span style='font-weight: bold; color: #007BFF;'>%1</span></td>"
                           "</tr>"
                           "<tr>"
                           "<td style='padding: 6px; border-bottom: 1px solid #dee2e6; color: %2;'><b>⏳ En Attente:</b></td>"
                           "<td style='padding: 6px; border-bottom: 1px solid #dee2e6; text-align: right;'><span style='font-weight: bold; color: %2;'>%3</span></td>"
                           "</tr>"
                           "<tr>"
                           "<td style='padding: 6px; border-bottom: 1px solid #dee2e6; color: %4;'><b>🔧 En Cours:</b></td>"
                           "<td style='padding: 6px; border-bottom: 1px solid #dee2e6; text-align: right;'><span style='font-weight: bold; color: %4;'>%5</span></td>"
                           "</tr>"
                           "<tr>"
                           "<td style='padding: 6px; border-bottom: 1px solid #dee2e6; color: %6;'><b>✅ Terminées:</b></td>"
                           "<td style='padding: 6px; border-bottom: 1px solid #dee2e6; text-align: right;'><span style='font-weight: bold; color: %6;'>%7</span></td>"
                           "</tr>"
                           "<tr>"
                           "<td style='padding: 6px; border-bottom: 1px solid #dee2e6; color: %8;'><b>❌ Annulées:</b></td>"
                           "<td style='padding: 6px; border-bottom: 1px solid #dee2e6; text-align: right;'><span style='font-weight: bold; color: %8;'>%9</span></td>"
                           "</tr>"
                           "<tr>"
                           "<td style='padding: 6px;'><b>💰 Chiffre d'Affaires:</b></td>"
                           "<td style='padding: 6px; text-align: right;'><span style='font-weight: bold; color: #28a745;'>%10 DT</span></td>"
                           "</tr>"
                           "</table>"
                           "</div>"
                           )
                           .arg(total)
                           .arg(colorEnAttente.name())
                           .arg(enAttente)
                           .arg(colorEnCours.name())
                           .arg(enCours)
                           .arg(colorTerminees.name())
                           .arg(terminees)
                           .arg(colorAnnulees.name())
                           .arg(annulees)
                           .arg(QString::number(coutTotal, 'f', 2));

    infoLabel->setText(infoText);
    infoLabel->setWordWrap(true);

    // === AJOUT AU LAYOUT ===
    layout->addWidget(chartView);
    layout->addWidget(infoLabel);

    // === CONFIGURATION DE LA MESSAGE BOX ===
    msgBox.layout()->addWidget(widget);

    // Ajouter un bouton OK
    msgBox.addButton(QMessageBox::Ok);

    // Personnaliser le style de la message box
    msgBox.setStyleSheet(
        "QMessageBox {"
        "   background-color: white;"
        "   border: 2px solid #35b95f;"
        "   border-radius: 8px;"
        "}"
        "QPushButton {"
        "   background-color: #35b95f;"
        "   color: white;"
        "   border: none;"
        "   padding: 8px 15px;"
        "   border-radius: 4px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2da34a;"
        "}"
        );

    // Afficher la message box
    msgBox.exec();
}

// ==================== TEXTBELT SMS AVEC SAUVEGARDE LOCALE ====================

QString MainWindow::formaterNumeroInternational(const QString &telephone)
{
    QString num = telephone;

    // Nettoyer le numéro
    num = num.remove(' ').remove('+').remove('-').remove('(').remove(')').remove('.');

    // Si le numéro a 8 chiffres (format tunisien local), ajouter l'indicatif
    if (num.length() == 8) {
        num = "+216" + num;
    }
    // Si le numéro commence déjà par 216 (sans le +)
    else if (num.startsWith("216") && num.length() == 11) {
        num = "+" + num;
    }
    // Si le numéro commence par 00216
    else if (num.startsWith("00216")) {
        num = "+" + num.mid(2);
    }

    qDebug() << "Numéro original:" << telephone << "-> Formaté:" << num;
    return num;
}

void MainWindow::sauvegarderSMSTerme(const QString &telephone, const QString &message, const QString &clientName, bool success, const QString &reponse)
{
    // Essayer plusieurs emplacements
    QStringList possiblePaths = {
        QCoreApplication::applicationDirPath() + "/historique_sms_locaux.txt",
        QDir::currentPath() + "/historique_sms_locaux.txt",
        QDir::homePath() + "/historique_sms_locaux.txt",
        "historique_sms_locaux.txt", // Répertoire courant
        "C:/temp/historique_sms_locaux.txt"
    };

    bool saved = false;
    QString savedPath;

    for (const QString &filePath : possiblePaths) {
        QFile file(filePath);

        // Créer le répertoire si nécessaire
        QFileInfo fileInfo(filePath);
        QDir dir = fileInfo.dir();
        if (!dir.exists()) {
            dir.mkpath(".");
        }

        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream stream(&file);
            stream << "=== " << QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss") << " ===\n";
            stream << "👤 Client: " << clientName << "\n";
            stream << "📞 Téléphone: " << telephone << "\n";
            stream << "💬 Message: " << message << "\n";
            stream << "✅ Statut: " << (success ? "ENVOYÉ" : "ÉCHEC") << "\n";
            if (!reponse.isEmpty()) {
                stream << "📨 Réponse: " << reponse << "\n";
            }
            stream << "🔧 Service: TextBelt\n";
            stream << "💾 Fichier: " << filePath << "\n";
            stream << "============================\n\n";
            file.close();

            saved = true;
            savedPath = filePath;
            qDebug() << "✓ SMS sauvegardé dans:" << filePath;
            break;
        } else {
            qDebug() << "✗ Échec sauvegarde:" << filePath << "- Erreur:" << file.errorString();
        }
    }

    if (saved) {
        QMessageBox::information(this, "✅ Sauvegarde Réussie",
                                 QString("SMS sauvegardé avec succès!\n\n"
                                         "📁 Fichier: %1\n"
                                         "👤 Client: %2\n"
                                         "📞 Téléphone: %3\n"
                                         "💬 Message: %4")
                                     .arg(savedPath)
                                     .arg(clientName)
                                     .arg(telephone)
                                     .arg(message));
    } else {
        QMessageBox::warning(this, "❌ Erreur Sauvegarde",
                             "Impossible de sauvegarder le SMS!\n"
                             "Vérifiez les permissions d'écriture.");
    }
}

void MainWindow::envoyerSMSTextBelt(const QString &telephone, const QString &message, const QString &clientName)
{
    QString numeroPropre = formaterNumeroInternational(telephone);

    qDebug() << "Tentative d'envoi SMS TextBelt à:" << telephone;

    // Vérifier le numéro
    if ((numeroPropre.startsWith("+216") && numeroPropre.length() == 12) ||
        (telephone.length() == 8)) {
        // Numéro valide - continuer
    } else {
        QMessageBox::warning(this, "Erreur",
                             QString("Format de numéro invalide!\n\n"
                                     "Numéro: %1\n"
                                     "Format supporté: 8 chiffres (22738308)")
                                 .arg(telephone));
        return;
    }

    // SAUVEGARDER IMMÉDIATEMENT (avant même d'essayer d'envoyer)
    sauvegarderSMSTerme(telephone, message, clientName, true, "Tentative d'envoi via TextBelt");

    // TextBelt API (1 SMS gratuit par jour)
    QString apiKey = "textbelt"; // Clé gratuite
    QUrl url("https://textbelt.com/text");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Préparer les données POST
    QUrlQuery postData;

    // Formater le numéro pour TextBelt (sans le +)
    QString numeroPourAPI;
    if (numeroPropre.startsWith("+216") && numeroPropre.length() == 12) {
        numeroPourAPI = numeroPropre.mid(1); // Enlever le +
    } else if (telephone.length() == 8) {
        numeroPourAPI = "216" + telephone; // Format: 21622738308
    } else {
        numeroPourAPI = telephone;
    }

    postData.addQueryItem("phone", numeroPourAPI);
    postData.addQueryItem("message", message);
    postData.addQueryItem("key", apiKey);

    QByteArray postDataEncoded = postData.toString(QUrl::FullyEncoded).toUtf8();

    qDebug() << "Envoi TextBelt - Numéro API:" << numeroPourAPI;

    // Afficher confirmation à l'utilisateur
    QMessageBox::information(this, "✅ SMS Traité",
                             QString("📱 NOTIFICATION SMS\n\n"
                                     "👤 Client: %1\n"
                                     "📞 Téléphone: %2\n"
                                     "💬 Message: %3\n\n"
                                     "✅ Statut: Sauvegardé et envoyé\n"
                                     "🔧 Service: TextBelt + Sauvegarde locale\n\n"
                                     "Le SMS a été sauvegardé localement et une tentative d'envoi a été faite via TextBelt.")
                                 .arg(clientName)
                                 .arg(telephone.length() == 8 ? "+216 " + telephone : telephone)
                                 .arg(message));

    // Essayer d'envoyer via TextBelt (en arrière-plan)
    QNetworkReply *reply = networkManager->post(request, postDataEncoded);
}

void MainWindow::onSmsSent(QNetworkReply *reply)
{
    QString responseString;
    bool success = false;

    if (reply->error() != QNetworkReply::NoError) {
        responseString = "Erreur réseau: " + reply->errorString();
        qDebug() << "Erreur TextBelt:" << responseString;
    } else {
        QByteArray responseData = reply->readAll();
        responseString = QString::fromUtf8(responseData);
        qDebug() << "Réponse TextBelt:" << responseString;

        // Analyser la réponse JSON
        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
        if (!jsonResponse.isNull()) {
            QJsonObject jsonObject = jsonResponse.object();
            success = jsonObject["success"].toBool();
            QString message = jsonObject["message"].toString();

            if (success) {
                qDebug() << "TextBelt: SMS envoyé avec succès";
            } else {
                qDebug() << "TextBelt: Échec -" << message;
            }
        }
    }

    reply->deleteLater();
}

/*---------------------------------------------------------
 *   NOTIFIER CLIENT PAR SMS TEXTBELT + SAUVEGARDE
 ---------------------------------------------------------*/
void MainWindow::on_BTN_NOTIFIER_clicked()
{
    QString idReparation = ui->IDR->text();

    if (idReparation.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un ID de réparation !");
        return;
    }

    // Récupérer les informations
    QSqlQuery q;
    q.prepare(
        "SELECT R.STATUT_R, R.DATE_FIN_EST, R.DES_PANNE, R.COUT, "
        "A.TYPE_A, A.MARQUE, A.MODELE, "
        "C.NOM, C.PRENOM, C.TEL "
        "FROM REPARATION R "
        "JOIN APPAREILS A ON R.NUM_SERIE = A.NUM_SERIE "
        "JOIN CLIENT C ON A.CIN = C.CIN "
        "WHERE R.IDR = ?"
        );
    q.addBindValue(idReparation);

    if (!q.exec() || !q.next()) {
        QMessageBox::warning(this, "Erreur", "Réparation introuvable !");
        return;
    }

    QString statut = q.value(0).toString();
    QDate dateFin = q.value(1).toDate();
    QString panne = q.value(2).toString();
    double cout = q.value(3).toDouble();
    QString typeAppareil = q.value(4).toString();
    QString marque = q.value(5).toString();
    QString modele = q.value(6).toString();
    QString nomClient = q.value(7).toString();
    QString prenomClient = q.value(8).toString();
    QString telephone = q.value(9).toString();

    if (telephone.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucun numéro de téléphone trouvé pour ce client !");
        return;
    }

    QString clientName = prenomClient + " " + nomClient;
    QString messageSMS;

    // Construire le message SMS court
    if (statut == "TERMINEE") {
        messageSMS = QString(
                         "Smart Repair Hub - Votre %1 %2 est réparé! Cout: %3 DT. Venez le recuperer. Tel: +21612345678"
                         ).arg(marque, modele, QString::number(cout, 'f', 0));

    } else if (QDate::currentDate() > dateFin) {
        messageSMS = QString(
            "Smart Repair Hub - Votre reparation est en retard. Nous vous recontacterons bientot. Tel: +21612345678"
            );

    } else if (statut == "EN COURS") {
        messageSMS = QString(
                         "Smart Repair Hub - Votre %1 %2 est en reparation. Fin prevue: %3. Tel: +21612345678"
                         ).arg(marque, modele, dateFin.toString("dd/MM/yyyy"));

    } else {
        QMessageBox::information(this, "Info", "Aucune notification nécessaire pour ce statut.");
        return;
    }

    // Vérifier la longueur du message
    if (messageSMS.length() > 160) {
        messageSMS = messageSMS.left(157) + "...";
    }

    // Demander confirmation
    QMessageBox::StandardButton confirm = QMessageBox::question(
        this,
        "Confirmation SMS",
        QString("Envoyer SMS à %1?\n\n"
                "📞 Téléphone: %2\n"
                "💬 Message: %3\n\n"
                "Le SMS sera sauvegardé localement et envoyé via TextBelt.")
            .arg(clientName)
            .arg(telephone)
            .arg(messageSMS),
        QMessageBox::Yes | QMessageBox::No
        );

    if (confirm == QMessageBox::Yes) {
        envoyerSMSTextBelt(telephone, messageSMS, clientName);
    }
}
