#include "mainwindow.h"
#include "config.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QInputDialog>
#include <QDialog>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QDialogButtonBox>
#include <QRegularExpression>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QToolTip>
#include <QSignalBlocker>
#include <QSqlError>
#include <QSerialPort>        // ← À AJOUTER OBLIGATOIREMENT
#include <QSerialPortInfo>    // ← À AJOUTER AUSSI
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupValidators();
    setupAdvancedFeatures();
    // Vérifier les fichiers WhatsApp au démarrage
    verifierFichiersWhatsApp();
    //arduino//
    setupArduino();

    // Initialiser le network manager pour Twilio
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onTwilioSent);
    // Tester le format des numéros
    testerFormatNumeros();




    // Ajouter des placeholders pour les champs obligatoires
    ui->lineEditId->setPlaceholderText("CIN * (Obligatoire)");
    ui->lineEditMarque_3->setPlaceholderText("Nom * (Obligatoire)");
    ui->lineEditMarque_2->setPlaceholderText("Prénom * (Obligatoire)");
    ui->lineEditIdClient->setPlaceholderText("CIN * (Obligatoire)");
    ui->lineEditNom->setPlaceholderText("Nom * (Obligatoire)");
    ui->lineEditPrenom->setPlaceholderText("Prénom * (Obligatoire)");
    ui->lineEditTelephone->setPlaceholderText("Téléphone * (Obligatoire)");
    ui->lineEditNumeroSerie->setPlaceholderText("Numéro série * (Obligatoire)");
    ui->lineEditMarque->setPlaceholderText("Marque * (Obligatoire)");
    ui->lineEditModele->setPlaceholderText("Modèle * (Obligatoire)");
    ui->lineEdit_2->setPlaceholderText("ID Réparation * (Obligatoire)");
    ui->lineEdit->setPlaceholderText("Matricule * (Obligatoire)");
    ui->lineEdit_3->setPlaceholderText("CIN Employé * (Obligatoire)");
    ui->lineEdit_4->setPlaceholderText("Numéro Série * (Obligatoire)");
    ui->textEditPanne->setPlaceholderText("Description de la panne * (Obligatoire)");

    // Connexions pour le contrôle de saisie en temps réel
    connect(ui->lineEditMarque_3, &QLineEdit::textChanged, this, &MainWindow::onTextChanged);
    connect(ui->lineEditMarque_2, &QLineEdit::textChanged, this, &MainWindow::onTextChanged);
    connect(ui->lineEditNom, &QLineEdit::textChanged, this, &MainWindow::onTextChanged);
    connect(ui->lineEditPrenom, &QLineEdit::textChanged, this, &MainWindow::onTextChanged);
    connect(ui->lineEditMarque, &QLineEdit::textChanged, this, &MainWindow::onTextChanged);

    // Connexion pour le tri par en-tête
    connect(ui->tableViewReparationsListe->horizontalHeader(), &QHeaderView::sectionClicked,
            this, &MainWindow::onHeaderReparationClicked);
    // Connexions pour les métiers innovants
    connect(ui->btnAnalyserFidelite, &QPushButton::clicked, this, &MainWindow::on_btnAnalyserFidelite_clicked);
    connect(ui->btnMaintenancePreventive, &QPushButton::clicked, this, &MainWindow::on_btnMaintenancePreventive_clicked);
    //arduino sirine//
    connect(arduinoManager, &SerialPortManager::reparationRequested,
            this, &MainWindow::onReparationRequested);


    // Entraîner le modèle ML
    trainPredictionModel();


    refreshEmployeTable();
    refreshClientTable();
    refreshAppareilTable();
    refreshReparationTable();
    loadComboBoxData();
    //arduino2//
    setupArduinos();

}

MainWindow::~MainWindow()
{
    if (arduinoManager) {
        arduinoManager->disconnectArduino();
    }
    delete ui;
}
// ------------sirine----------------
void MainWindow::verifierFichiersWhatsApp()
{
    QStringList pathsToCheck = {
        QCoreApplication::applicationDirPath() + "/historique_whatsapp.txt",
        QDir::currentPath() + "/historique_whatsapp.txt",
        QDir::homePath() + "/historique_whatsapp.txt",
        "historique_whatsapp.txt"
    };

    QString message = "📁 Fichiers WhatsApp trouvés:\n\n";
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
        message += "\nAucun fichier WhatsApp trouvé. Ils seront créés au premier envoi.";
    }

    qDebug() << "Vérification fichiers WhatsApp:" << message;
}

void MainWindow::testerFormatNumeros()
{
    QSqlQuery testQuery;
    testQuery.exec("SELECT CIN_CLIENT, NOM, PRENOM, TEL FROM CLIENT WHERE ROWNUM <= 5");

    qDebug() << "=== TEST FORMAT NUMÉROS CLIENT ===";
    while (testQuery.next()) {
        QString cin = testQuery.value(0).toString();
        QString nom = testQuery.value(1).toString();
        QString prenom = testQuery.value(2).toString();
        QString tel = testQuery.value(3).toString();

        qDebug() << "Client:" << prenom << nom
                 << "| TEL:" << tel
                 << "| Longueur:" << tel.length()
                 << "| Formaté Twilio:" << formaterNumeroTwilio(tel);
    }
    qDebug() << "=== FIN TEST ===";
}

void MainWindow::setupAdvancedFeatures()
{
    // On ne crée la fenêtre qu'une seule fois
    if (!statisticsWindow) {
        statisticsWindow = new Statistics(nullptr);  // parent = nullptr pour fenêtre indépendante
        statisticsWindow->setWindowTitle("Tableau de Bord - Statistiques Avancées");
        statisticsWindow->resize(1200, 800);
        statisticsWindow->setWindowIcon(QIcon(":/icons/statistics.png")); // optionnel
    }

    pdfExporter = new PDFExporter(this);
}

void MainWindow::on_btnShowStatistics_clicked()
{
    if (!statisticsWindow) {
        setupAdvancedFeatures();
    }

    statisticsWindow->refreshAllStats();
    statisticsWindow->show();
    statisticsWindow->raise();
    statisticsWindow->activateWindow();
}

void MainWindow::on_btnExportPDF_clicked()
{
    QString defaultName = "Rapport_SmartRepairHub_" + QDate::currentDate().toString("dd-MM-yyyy") + ".pdf";
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Exporter le Rapport PDF",
                                                    QDir::homePath() + "/" + defaultName,
                                                    "Fichiers PDF (*.pdf)");

    if (fileName.isEmpty()) return;

    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive))
        fileName += ".pdf";

    ui->statusbar->showMessage("Génération du rapport PDF en cours...", 5000);

    if (pdfExporter->exportClientReport(fileName)) {
        QMessageBox::information(this, "Succès",
                                 "Rapport généré avec succès !\n\nFichier enregistré :\n" + fileName);
        ui->statusbar->showMessage("Rapport PDF généré", 5000);
    } else {
        QMessageBox::critical(this, "Échec",
                              "Impossible de générer le PDF.\n\nVérifiez la console pour les erreurs SQL.");
        ui->statusbar->showMessage("Échec génération PDF", 5000);
    }
}

void MainWindow::setupValidators()
{
    // Validateurs pour les champs numériques
    QIntValidator *cinValidator = new QIntValidator(1, 99999999, this);
    QIntValidator *numSerieValidator = new QIntValidator(1, 999999999, this);
    QDoubleValidator *coutValidator = new QDoubleValidator(0, 999999.99, 2, this);

    // Validateur pour les champs texte (pas de chiffres)
    QRegularExpressionValidator *texteValidator = new QRegularExpressionValidator(QRegularExpression("[A-Za-zÀ-ÿ\\s'-]+"), this);
    QRegularExpressionValidator *emailValidator = new QRegularExpressionValidator(QRegularExpression("[A-Za-z0-9._%+-@]+"), this);
    QRegularExpressionValidator *adresseValidator = new QRegularExpressionValidator(QRegularExpression("[A-Za-z0-9À-ÿ\\s,'-]+"), this);

    // Employés
    ui->lineEditId->setValidator(cinValidator);
    ui->lineEditModele_2->setValidator(new QIntValidator(10000000, 99999999, this));
    ui->lineEditMarque_3->setValidator(texteValidator); // Nom
    ui->lineEditMarque_2->setValidator(texteValidator); // Prénom
    ui->lineEditNumeroSerie_2->setValidator(emailValidator); // Email

    // Clients
    ui->lineEditIdClient->setValidator(cinValidator);
    ui->lineEditTelephone->setValidator(new QIntValidator(10000000, 99999999, this));
    ui->lineEditNom->setValidator(texteValidator);
    ui->lineEditPrenom->setValidator(texteValidator);
    ui->lineEditEmail->setValidator(emailValidator);
    ui->lineEditAdresse->setValidator(adresseValidator);

    // Appareils
    ui->lineEditNumeroSerie->setValidator(numSerieValidator);
    ui->lineEditMarque->setValidator(texteValidator);
    ui->lineEditModele->setValidator(adresseValidator); // Modèle peut contenir chiffres

    // Réparations
    ui->lineEditCout->setValidator(coutValidator);
    ui->lineEdit_3->setValidator(cinValidator); // CIN employé
    ui->lineEdit_4->setValidator(numSerieValidator); // Numéro série
    ui->lineEdit_2->setValidator(cinValidator); // ID réparation
    ui->lineEdit->setValidator(adresseValidator); // Matricule réparation
}

// ==================== MÉTHODES DE VALIDATION ====================

bool MainWindow::validateCIN(const QString& cinStr, int& cin)
{
    bool ok;
    cin = cinStr.toInt(&ok);
    return ok && cin > 0 && cin <= 99999999;
}

bool MainWindow::validateTelephone(const QString& telephone)
{
    QRegularExpression regex("^[0-9]{8}$");
    return regex.match(telephone).hasMatch();
}

bool MainWindow::validateEmail(const QString& email)
{
    if (email.isEmpty()) return true;
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return regex.match(email).hasMatch();
}

bool MainWindow::validateNomPrenom(const QString& texte)
{
    QRegularExpression regex("^[a-zA-ZÀ-ÿ\\s'-]{2,50}$");
    return regex.match(texte).hasMatch();
}

bool MainWindow::validateNumSerie(const QString& numStr, int& numSerie)
{
    bool ok;
    numSerie = numStr.toInt(&ok);
    return ok && numSerie > 0;
}

bool MainWindow::validateCout(const QString& coutStr, double& cout)
{
    bool ok;
    QString cleanedStr = coutStr;
    cout = cleanedStr.toDouble(&ok);
    return ok && cout >= 0;
}

bool MainWindow::validateIdReparation(const QString& idStr, int& idReparation)
{
    bool ok;
    idReparation = idStr.toInt(&ok);
    return ok && idReparation > 0;
}

bool MainWindow::validateTextField(const QString& text, const QString& fieldName)
{
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Champ requis",
                             QString("Le champ '%1' ne peut pas être vide!").arg(fieldName));
        return false;
    }

    // Vérifier s'il y a des chiffres
    if (text.contains(QRegularExpression("[0-9]"))) {
        QMessageBox::warning(this, "Erreur de saisie",
                             QString("Le champ '%1' ne peut pas contenir de chiffres!").arg(fieldName));
        return false;
    }

    return true;
}
bool MainWindow::validateRequiredFields(const QStringList& fields, const QStringList& values, const QString& formName)
{
    bool allValid = true;
    for (int i = 0; i < fields.size(); ++i) {
        if (values[i].isEmpty()) {
            allValid = false;
        }
    }

    if (!allValid) {
        highlightEmptyFields(fields, values);
        QMessageBox::warning(this, "Champs obligatoires manquants",
                             QString("Veuillez remplir tous les champs obligatoires pour %1!")
                                 .arg(formName));
        return false;
    }

    return true;
}

// ==================== NOUVELLES MÉTHODES ====================

void MainWindow::onTextChanged(const QString& text)
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(sender());
    if (!lineEdit) return;

    // Supprimer les chiffres
    QString cleanedText = text;
    cleanedText.remove(QRegularExpression("[0-9]"));

    if (cleanedText != text) {
        // Bloquer la saisie et afficher un message
        QSignalBlocker blocker(lineEdit);
        lineEdit->setText(cleanedText);

        // Message d'avertissement
        QToolTip::showText(lineEdit->mapToGlobal(QPoint(0, 0)),
                           "Les chiffres ne sont pas autorisés dans ce champ",
                           lineEdit);
    }
}

void MainWindow::onHeaderReparationClicked(int logicalIndex)
{
    if (logicalIndex == 5) { // Index de la colonne "Coût"
        QSqlQueryModel* model = qobject_cast<QSqlQueryModel*>(ui->tableViewReparationsListe->model());
        if (!model) return;

        // Déterminer l'ordre de tri actuel
        static bool triCoutAscendant = true;
        QString ordreTri = triCoutAscendant ? "ASC" : "DESC";

        QSqlQueryModel* newModel = new QSqlQueryModel();
        newModel->setQuery(QString("SELECT IDR, DES_PANNE, DATE_REC, DATE_FIN_EST, STATUT_R, COUT, CIN_EMP, NUM_SERIE, MAT_REP FROM REPARATIONS ORDER BY COUT %1").arg(ordreTri));

        // Copier les en-têtes
        for (int i = 0; i < newModel->columnCount(); ++i) {
            newModel->setHeaderData(i, Qt::Horizontal, model->headerData(i, Qt::Horizontal));
        }

        ui->tableViewReparationsListe->setModel(newModel);
        delete model;

        triCoutAscendant = !triCoutAscendant;
    }
}

// ==================== MÉTHODES DE RAFRAÎCHISSEMENT ====================

void MainWindow::refreshEmployeTable()
{
    ui->tableViewAppareils_2->setModel(emp.afficher());
}

void MainWindow::refreshClientTable()
{
    ui->tableViewClients->setModel(clt.afficher());
    ui->labelTotalClients->setText(QString("Total: %1 clients").arg(ui->tableViewClients->model()->rowCount()));
}

void MainWindow::refreshAppareilTable()
{
    ui->tableViewAppareils->setModel(app.afficher());
    ui->labelTotalAppareils->setText(QString("Total: %1 appareils").arg(ui->tableViewAppareils->model()->rowCount()));
}

void MainWindow::refreshReparationTable()
{
    ui->tableViewReparationsListe->setModel(rep.afficher());
    ui->labelTotalReparations->setText(QString("Total: %1 réparations").arg(ui->tableViewReparationsListe->model()->rowCount()));
}

void MainWindow::loadComboBoxData()
{
    // Les combobox pour appareils et employés sont remplacées par des saisies manuelles
}

// ==================== MÉTHODES DE NETTOYAGE ====================

void MainWindow::clearEmployeFields()
{
    ui->lineEditId->clear();
    ui->lineEditMarque_3->clear();
    ui->lineEditMarque_2->clear();
    // Using the correct widget names from the UI
    ui->lineEditTelephone->clear();
    ui->lineEditEmail->clear();
    ui->lineEditAdresse->clear();
    // Using the available date edit widget or remove if not needed
    // ui->dateEditInscription->setDate(QDate::currentDate());
    // Using the available combo box or remove if not needed
    // ui->comboBoxType->setCurrentIndex(0);
}

void MainWindow::clearClientFields()
{
    ui->lineEditIdClient->clear();
    ui->lineEditNom->clear();
    ui->lineEditPrenom->clear();
    ui->lineEditTelephone->clear();
    ui->lineEditEmail->clear();
    ui->lineEditAdresse->clear();
    ui->dateEditInscription->setDate(QDate::currentDate());
}

void MainWindow::clearAppareilFields()
{
    ui->lineEditNumeroSerie->clear();
    ui->comboBoxType->setCurrentIndex(0);
    ui->lineEditMarque->clear();
    ui->lineEditModele->clear();
    ui->dateEditAchat->setDate(QDate::currentDate());
}

void MainWindow::clearReparationFields()
{
    ui->lineEdit->clear(); // Matricule réparation
    ui->textEditPanne->clear();
    ui->lineEditCout->clear();
    ui->dateEditDepot->setDate(QDate::currentDate());
    ui->dateEditRetourPrevue->setDate(QDate::currentDate());
    ui->comboBoxStatutReparation->setCurrentIndex(0);
    ui->lineEdit_4->clear(); // Numéro série appareil
    ui->lineEdit_3->clear(); // CIN employé
    ui->lineEdit_2->clear(); // ID réparation
}

// ==================== GESTION DES EMPLOYÉS ====================

void MainWindow::on_btnAjouter_clicked()
{
    // Validation des champs obligatoires
    QStringList requiredFields = {"CIN", "Nom", "Prénom"};
    QStringList fieldValues = {
        ui->lineEditId->text().trimmed(),
        ui->lineEditMarque_3->text().trimmed(),
        ui->lineEditMarque_2->text().trimmed()
    };

    if (!validateRequiredFields(requiredFields, fieldValues, "l'ajout d'un employé")) {
        return;
    }

    int cin;
    if(!validateCIN(ui->lineEditId->text(), cin)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le CIN doit être un nombre positif entre 1 et 99,999,999!");
        return;
    }

    QString nom = ui->lineEditMarque_3->text();
    QString prenom = ui->lineEditMarque_2->text();
    QString telephone = ui->lineEditModele_2->text();
    QString email = ui->lineEditNumeroSerie_2->text();

    // Validation des champs texte
    if(!validateTextField(nom, "Nom")) return;
    if(!validateTextField(prenom, "Prénom")) return;

    if(!validateNomPrenom(nom)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le nom n'est pas valide!");
        return;
    }

    if(!validateNomPrenom(prenom)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le prénom n'est pas valide!");
        return;
    }

    if(!telephone.isEmpty() && !validateTelephone(telephone)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le téléphone doit contenir 8 chiffres!");
        return;
    }

    if(!email.isEmpty() && !validateEmail(email)) {
        QMessageBox::warning(this, "Erreur de saisie", "L'email n'est pas valide!");
        return;
    }

    Employe e(cin, nom, prenom, telephone, email);
    bool test = e.ajouter();

    if(test) {
        QMessageBox::information(this, "Succès", "Employé ajouté avec succès!");
        refreshEmployeTable();
        clearEmployeFields();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de l'employé!");
    }
}

void MainWindow::on_btnModifier_clicked()
{
    int cin;
    if(!validateCIN(ui->lineEditId->text(), cin)) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez sélectionner un employé à modifier!");
        return;
    }

    QString nom = ui->lineEditMarque_3->text();
    QString prenom = ui->lineEditMarque_2->text();
    QString telephone = ui->lineEditModele_2->text();
    QString email = ui->lineEditNumeroSerie_2->text();

    // Validation des champs texte
    if(!validateTextField(nom, "Nom")) return;
    if(!validateTextField(prenom, "Prénom")) return;

    if(!validateNomPrenom(nom)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le nom n'est pas valide!");
        return;
    }

    if(!validateNomPrenom(prenom)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le prénom n'est pas valide!");
        return;
    }

    if(!telephone.isEmpty() && !validateTelephone(telephone)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le téléphone doit contenir 8 chiffres!");
        return;
    }

    if(!email.isEmpty() && !validateEmail(email)) {
        QMessageBox::warning(this, "Erreur de saisie", "L'email n'est pas valide!");
        return;
    }

    Employe e(cin, nom, prenom, telephone, email);
    bool test = e.modifier(cin);

    if(test) {
        QMessageBox::information(this, "Succès", "Employé modifié avec succès!");
        refreshEmployeTable();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification de l'employé!");
    }
}

void MainWindow::on_btnSupprimer_clicked()
{
    int cin;
    if(!validateCIN(ui->lineEditId->text(), cin)) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez sélectionner un employé à supprimer!");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer cet employé?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        bool test = emp.supprimer(cin);

        if(test) {
            QMessageBox::information(this, "Succès", "Employé supprimé avec succès!");
            refreshEmployeTable();
            clearEmployeFields();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression de l'employé!");
        }
    }
}

void MainWindow::on_btnRechercher_clicked()
{
    QString critere = ui->comboBoxCritere->currentText();
    QString valeur = ui->lineEditMarque_3->text();

    if(valeur.isEmpty()) {
        QMessageBox::warning(this, "Champ requis", "Veuillez saisir un terme de recherche!");
        return;
    }

    QSqlQueryModel* model = new QSqlQueryModel();

    if(critere == "nom") {
        model->setQuery("SELECT * FROM EMPLOYER WHERE NOM LIKE '%" + valeur + "%'");
    }

    ui->tableViewAppareils_2->setModel(model);
}

void MainWindow::on_btnReinitialiser_clicked()
{
    // Tri par nom comme indiqué dans l'interface "tri par nom"
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CIN_EMPLOYER, NOM, PRENOM, TELEPHONE, EMAIL FROM EMPLOYER ORDER BY NOM, PRENOM");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));

    ui->tableViewAppareils_2->setModel(model);
    clearEmployeFields();
}

void MainWindow::on_tableViewAppareils_2_clicked(const QModelIndex &index)
{
    int row = index.row();

    ui->lineEditId->setText(ui->tableViewAppareils_2->model()->index(row, 0).data().toString());
    ui->lineEditMarque_3->setText(ui->tableViewAppareils_2->model()->index(row, 1).data().toString());
    ui->lineEditMarque_2->setText(ui->tableViewAppareils_2->model()->index(row, 2).data().toString());
    ui->lineEditModele_2->setText(ui->tableViewAppareils_2->model()->index(row, 3).data().toString());
    ui->lineEditNumeroSerie_2->setText(ui->tableViewAppareils_2->model()->index(row, 4).data().toString());
}

// ==================== MÉTHODES DE STATISTIQUES ====================

void MainWindow::on_btnStatistiquesAppareil_clicked()
{
    // Vérifier la connexion à la base de données
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Erreur de connexion", "La base de données n'est pas connectée");
        return;
    }

    // Vérifier si la table APPAREILLES existe
    if (!db.tables().contains("APPAREILLES")) {
        QMessageBox::critical(this, "Erreur", "La table APPAREILLES n'existe pas dans la base de données");
        return;
    }

    // Récupérer les statistiques des appareils par marque
    QSqlQuery query;
    if (!query.exec("SELECT MARQUE, COUNT(*) as nombre FROM APPAREILLES GROUP BY MARQUE")) {
        QMessageBox::critical(this, "Erreur", "Impossible de récupérer les statistiques: " + query.lastError().text());
        return;
    }

    // Créer une série de données pour le graphique
    QPieSeries *series = new QPieSeries();
    int totalAppareils = 0;

    // Récupérer le nombre total d'appareils
    QString debugInfo = "Données récupérées :\n";
    bool hasData = false;

    if (query.next()) {
        do {
            QString marque = query.value(0).toString();
            int count = query.value(1).toInt();
            totalAppareils += count;
            series->append(marque, count);
            debugInfo += QString("Marque: %1, Nombre: %2\n").arg(marque).arg(count);
            hasData = true;
        } while (query.next());
    }

    // Afficher les données de débogage
    qDebug() << debugInfo;

    if (!hasData) {
        QMessageBox::information(this, "Information", "Aucune donnée trouvée dans la table APPAREILS.");
        return;
    }

    // Si aucun appareil trouvé
    if (totalAppareils == 0) {
        QMessageBox::information(this, "Information", "Aucun appareil trouvé dans la base de données.");
        return;
    }

    // Mettre à jour les pourcentages et les légendes
    for (auto slice : series->slices()) {
        double percentage = (slice->value() / totalAppareils) * 100.0;
        QString marque = slice->label();

        // Stocker les informations complètes dans la légende
        slice->setLabel(QString("%1: %2% (%3)")
                            .arg(marque)
                            .arg(percentage, 0, 'f', 1)
                            .arg(slice->value()));

        // Afficher uniquement le pourcentage dans la tranche
        slice->setLabelVisible(true);
        slice->setLabelPosition(QPieSlice::LabelInsideHorizontal);

        // Ajuster la police pour les étiquettes
        QFont font;
        font.setBold(true);
        slice->setLabelFont(font);
    }

    // Activer les étiquettes pour la légende
    series->setLabelsVisible(true);

    // Définir le style des étiquettes
    series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);

    // Créer le graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des appareils par marque");

    // Configurer la légende
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->setMarkerShape(QLegend::MarkerShapeRectangle);

    // Ajuster la taille de la police de la légende
    QFont legendFont = chart->legend()->font();
    legendFont.setPointSize(10);
    chart->legend()->setFont(legendFont);

    // Activer les animations
    chart->setAnimationOptions(QChart::AllAnimations);

    // Créer la vue du graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(800, 600);

    // Créer une boîte de dialogue pour afficher le graphique
    QDialog *chartDialog = new QDialog(this);
    chartDialog->setWindowTitle("Statistiques des appareils par marque");
    chartDialog->setMinimumSize(850, 650);
    QVBoxLayout *layout = new QVBoxLayout(chartDialog);
    layout->addWidget(chartView);

    // Ajouter un bouton pour exporter en PDF
    QPushButton *btnExportPDF = new QPushButton("Exporter en PDF", chartDialog);
    btnExportPDF->setStyleSheet("background-color: #DC3545; color: white; font-weight: bold; padding: 8px;");
    connect(btnExportPDF, &QPushButton::clicked, this, [=]() {
        QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer le graphique",
                                                        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                                        "Fichiers PDF (*.pdf)");
        if (!fileName.isEmpty()) {
            if (!fileName.endsWith(".pdf", Qt::CaseInsensitive))
                fileName += ".pdf";

            QPdfWriter writer(fileName);
            writer.setPageSize(QPageSize(QPageSize::A4));

            QPainter painter(&writer);
            chartView->render(&painter);
            painter.end();

            QMessageBox::information(this, "Succès", "Le graphique a été exporté avec succès !");
        }
    });

    layout->addWidget(btnExportPDF, 0, Qt::AlignRight | Qt::AlignBottom);

    chartDialog->exec();
}

// ==================== GESTION DES CLIENTS ====================

void MainWindow::on_btnAjouterClient_clicked()
{
    // Validation des champs obligatoires
    QStringList requiredFields = {"CIN", "Nom", "Prénom", "Téléphone"};
    QStringList fieldValues = {
        ui->lineEditIdClient->text().trimmed(),
        ui->lineEditNom->text().trimmed(),
        ui->lineEditPrenom->text().trimmed(),
        ui->lineEditTelephone->text().trimmed()
    };

    if (!validateRequiredFields(requiredFields, fieldValues, "l'ajout d'un client")) {
        return;
    }

    int cin;
    if(!validateCIN(ui->lineEditIdClient->text(), cin)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le CIN doit être un nombre positif entre 1 et 99,999,999!");
        return;
    }

    QString nom = ui->lineEditNom->text();
    QString prenom = ui->lineEditPrenom->text();
    QString telephone = ui->lineEditTelephone->text();
    QString email = ui->lineEditEmail->text();
    QString adresse = ui->lineEditAdresse->text();
    QDate dateNaissance = ui->dateEditInscription->date();

    // Validation des champs texte
    if(!validateTextField(nom, "Nom")) return;
    if(!validateTextField(prenom, "Prénom")) return;

    if(!validateNomPrenom(nom)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le nom n'est pas valide!");
        return;
    }

    if(!validateNomPrenom(prenom)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le prénom n'est pas valide!");
        return;
    }

    if(!validateTelephone(telephone)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le téléphone doit contenir 8 chiffres!");
        return;
    }

    if(!email.isEmpty() && !validateEmail(email)) {
        QMessageBox::warning(this, "Erreur de saisie", "L'email n'est pas valide!");
        return;
    }

    Client c(cin, nom, prenom, telephone, email, adresse, dateNaissance);
    bool test = c.ajouter();

    if(test) {
        QMessageBox::information(this, "Succès", "Client ajouté avec succès!");
        refreshClientTable();
        clearClientFields();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du client!");
    }
}

void MainWindow::on_btnModifierClient_clicked()
{
    int cin;
    if(!validateCIN(ui->lineEditIdClient->text(), cin)) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez sélectionner un client à modifier!");
        return;
    }

    QString nom = ui->lineEditNom->text();
    QString prenom = ui->lineEditPrenom->text();
    QString telephone = ui->lineEditTelephone->text();
    QString email = ui->lineEditEmail->text();
    QString adresse = ui->lineEditAdresse->text();
    QDate dateNaissance = ui->dateEditInscription->date();

    // Validation des champs texte
    if(!validateTextField(nom, "Nom")) return;
    if(!validateTextField(prenom, "Prénom")) return;

    if(!validateNomPrenom(nom)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le nom n'est pas valide!");
        return;
    }

    if(!validateNomPrenom(prenom)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le prénom n'est pas valide!");
        return;
    }

    if(!telephone.isEmpty() && !validateTelephone(telephone)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le téléphone doit contenir 8 chiffres!");
        return;
    }

    if(!email.isEmpty() && !validateEmail(email)) {
        QMessageBox::warning(this, "Erreur de saisie", "L'email n'est pas valide!");
        return;
    }

    Client c(cin, nom, prenom, telephone, email, adresse, dateNaissance);
    bool test = c.modifier(cin);

    if(test) {
        QMessageBox::information(this, "Succès", "Client modifié avec succès!");
        refreshClientTable();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification du client!");
    }
}

void MainWindow::on_btnSupprimerClient_clicked()
{
    int cin;
    if(!validateCIN(ui->lineEditIdClient->text(), cin)) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez sélectionner un client à supprimer!");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer ce client?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        bool test = clt.supprimer(cin);

        if(test) {
            QMessageBox::information(this, "Succès", "Client supprimé avec succès!");
            refreshClientTable();
            clearClientFields();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression du client!");
        }
    }
}

void MainWindow::on_btnRechercherClient_clicked()
{
    QString critere = ui->comboBoxCritereClient->currentText();
    QString valeur = ui->lineEditRechercheClient->text();

    if(valeur.isEmpty()) {
        QMessageBox::warning(this, "Champ requis", "Veuillez saisir un terme de recherche!");
        return;
    }

    ui->tableViewClients->setModel(clt.rechercher(critere, valeur));
}

void MainWindow::on_btnReinitialiserClient_clicked()
{
    // Tri par nom comme indiqué dans l'interface "trier par nom"
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CIN_CLIENT, NOM, PRENOM, TELEPHONE, EMAIL, ADRESSE, DATEN FROM CLIENT ORDER BY NOM, PRENOM");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date Naissance"));

    ui->tableViewClients->setModel(model);
    ui->lineEditRechercheClient->clear();
}

void MainWindow::on_tableViewClients_clicked(const QModelIndex &index)
{
    int row = index.row();

    ui->lineEditIdClient->setText(ui->tableViewClients->model()->index(row, 0).data().toString());
    ui->lineEditNom->setText(ui->tableViewClients->model()->index(row, 1).data().toString());
    ui->lineEditPrenom->setText(ui->tableViewClients->model()->index(row, 2).data().toString());
    ui->lineEditTelephone->setText(ui->tableViewClients->model()->index(row, 3).data().toString());
    ui->lineEditEmail->setText(ui->tableViewClients->model()->index(row, 4).data().toString());
    ui->lineEditAdresse->setText(ui->tableViewClients->model()->index(row, 5).data().toString());
    ui->dateEditInscription->setDate(ui->tableViewClients->model()->index(row, 6).data().toDate());
}

// ==================== GESTION DES APPAREILS ====================

void MainWindow::on_btnAjouterAppareil_clicked()
{
    // Validation des champs obligatoires
    QStringList requiredFields = {"Numéro de série", "Type", "Marque", "Modèle"};
    QStringList fieldValues = {
        ui->lineEditNumeroSerie->text().trimmed(),
        ui->comboBoxType->currentText().trimmed(),
        ui->lineEditMarque->text().trimmed(),
        ui->lineEditModele->text().trimmed()
    };

    if (!validateRequiredFields(requiredFields, fieldValues, "l'ajout d'un appareil")) {
        return;
    }

    int numSerie;
    if(!validateNumSerie(ui->lineEditNumeroSerie->text(), numSerie)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le numéro de série doit être un nombre positif!");
        return;
    }

    QString type = ui->comboBoxType->currentText();
    QString marque = ui->lineEditMarque->text();
    QString modele = ui->lineEditModele->text();
    QDate dateAchat = ui->dateEditAchat->date();

    // Validation des champs texte
    if(!validateTextField(marque, "Marque")) return;

    bool ok;
    int cinClient = QInputDialog::getInt(this, "Sélection du client",
                                         "Veuillez saisir le CIN du client propriétaire:",
                                         0, 1, 99999999, 1, &ok);

    if (!ok) {
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM CLIENT WHERE CIN_CLIENT = :cinClient");
    query.bindValue(":cinClient", cinClient);
    query.exec();
    query.next();
    int count = query.value(0).toInt();

    if(count == 0) {
        QMessageBox::warning(this, "Client introuvable",
                             "Le client avec CIN " + QString::number(cinClient) + " n'existe pas!\n"
                                                                                  "Veuillez d'abord ajouter ce client.");
        return;
    }

    Appareils a(numSerie, type, marque, modele, dateAchat, "Fonctionnel", cinClient);
    bool test = a.ajouter();

    if(test) {
        QMessageBox::information(this, "Succès", "Appareil ajouté avec succès!");
        refreshAppareilTable();
        clearAppareilFields();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de l'appareil!");
    }
}

void MainWindow::on_btnModifierAppareil_clicked()
{
    int numSerie;
    if(!validateNumSerie(ui->lineEditNumeroSerie->text(), numSerie)) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez sélectionner un appareil à modifier!");
        return;
    }

    QString type = ui->comboBoxType->currentText();
    QString marque = ui->lineEditMarque->text();
    QString modele = ui->lineEditModele->text();
    QDate dateAchat = ui->dateEditAchat->date();

    // Validation des champs texte
    if(!validateTextField(marque, "Marque")) return;

    if(marque.isEmpty()) {
        QMessageBox::warning(this, "Champ requis", "La marque est obligatoire!");
        return;
    }

    if(modele.isEmpty()) {
        QMessageBox::warning(this, "Champ requis", "Le modèle est obligatoire!");
        return;
    }

    bool ok;
    int cinClient = QInputDialog::getInt(this, "Sélection du client",
                                         "Veuillez saisir le CIN du client propriétaire:",
                                         0, 1, 99999999, 1, &ok);

    if (!ok) {
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM CLIENT WHERE CIN_CLIENT = :cinClient");
    query.bindValue(":cinClient", cinClient);
    query.exec();
    query.next();
    int count = query.value(0).toInt();

    if(count == 0) {
        QMessageBox::warning(this, "Client introuvable",
                             "Le client avec CIN " + QString::number(cinClient) + " n'existe pas!");
        return;
    }

    Appareils a(numSerie, type, marque, modele, dateAchat, "Fonctionnel", cinClient);
    bool test = a.modifier(numSerie);

    if(test) {
        QMessageBox::information(this, "Succès", "Appareil modifié avec succès!");
        refreshAppareilTable();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification de l'appareil!");
    }
}

void MainWindow::on_btnSupprimerAppareil_clicked()
{
    int numSerie;
    if(!validateNumSerie(ui->lineEditNumeroSerie->text(), numSerie)) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez sélectionner un appareil à supprimer!");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer cet appareil?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        bool test = app.supprimer(numSerie);

        if(test) {
            QMessageBox::information(this, "Succès", "Appareil supprimé avec succès!");
            refreshAppareilTable();
            clearAppareilFields();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression de l'appareil!");
        }
    }
}

// Fonction utilitaire pour afficher les noms des champs de texte
void MainWindow::afficherChampsTexte() {
    qDebug() << "Liste des champs de texte (QLineEdit) dans l'interface :";
    QList<QLineEdit*> lineEdits = findChildren<QLineEdit*>();
    for (QLineEdit* lineEdit : lineEdits) {
        qDebug() << "- " << lineEdit->objectName();
    }
}

void MainWindow::on_btnRechercherAppareil_clicked()
{
    // Afficher les noms des champs de texte pour le débogage
    afficherChampsTexte();

    // Utiliser directement le champ lineEdit_5 qui est le bon champ de recherche
    QString valeur = ui->lineEdit_5->text();
    QString critere = ui->comboBoxCritereAppareil->currentText();

    qDebug() << "Champ de recherche utilisé: lineEdit_5";

    qDebug() << "Recherche en cours - Valeur:" << valeur << "Critère:" << critere;

    if(valeur.isEmpty()) {
        qDebug() << "Erreur: Champ de recherche vide";
        QMessageBox::warning(this, "Champ requis", "Veuillez saisir une valeur de recherche !");
        return;
    }

    // If searching by serial number, validate it's a number
    if (critere == "Numéro Série") {
        bool ok;
        int numSerie = valeur.toInt(&ok);
        if (!ok || numSerie <= 0) {
            qDebug() << "Erreur: Numéro de série invalide";
            QMessageBox::warning(this, "Format invalide", "Le numéro de série doit être un nombre positif !");
            return;
        }
    }

    qDebug() << "Appel de app.rechercher avec valeur:" << valeur << "et critère:" << critere;

    // Call the search function with the search criteria
    QSqlQueryModel *model = app.rechercher(valeur, critere);

    qDebug() << "Nombre de résultats trouvés:" << model->rowCount();

    if (model->rowCount() == 0) {
        qDebug() << "Aucun résultat trouvé pour la recherche";
        QMessageBox::information(this, "Recherche", "Aucun appareil trouvé avec ces critères.");
    } else {
        qDebug() << "Résultats trouvés, mise à jour du modèle";
    }

    ui->tableViewAppareils->setModel(model);
    qDebug() << "Modèle de table mis à jour";
}

void MainWindow::on_btnReinitialiserAppareil_clicked()
{
    // Clear the search input field
    ui->lineEdit->clear();

    // Reset the search criteria to default (Numéro Série)
    ui->comboBoxCritereAppareil->setCurrentIndex(0);

    // Refresh the table to show all devices
    refreshAppareilTable();

    // Toggle sort order and update button text
    sortOrderAscending_ = !sortOrderAscending_;
    QString buttonText = sortOrderAscending_ ? "Trier par date ↑" : "Trier par date ↓";
    ui->btnReinitialiserAppareil->setText(buttonText);

    // Exécuter la requête avec le tri approprié
    QSqlQueryModel* model = new QSqlQueryModel();
    QString query = "SELECT NUM_SERIE, TYPE, MARQUE, MODELE, DATE_ACQ, ETAT, CIN_CLIENT FROM APPAREILLES ";
    query += sortOrderAscending_ ? "ORDER BY DATE_ACQ ASC" : "ORDER BY DATE_ACQ DESC";

    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Numéro Série"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Marque"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Modèle"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date Acquisition"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("État"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("CIN Client"));

    ui->tableViewAppareils->setModel(model);
    clearAppareilFields();
}

void MainWindow::on_tableViewAppareils_clicked(const QModelIndex &index)
{
    int row = index.row();

    ui->lineEditNumeroSerie->setText(ui->tableViewAppareils->model()->index(row, 0).data().toString());
    ui->comboBoxType->setCurrentText(ui->tableViewAppareils->model()->index(row, 1).data().toString());
    ui->lineEditMarque->setText(ui->tableViewAppareils->model()->index(row, 2).data().toString());
    ui->lineEditModele->setText(ui->tableViewAppareils->model()->index(row, 3).data().toString());
    ui->dateEditAchat->setDate(ui->tableViewAppareils->model()->index(row, 4).data().toDate());
}

void MainWindow::on_btnVieAppareil_clicked()
{
    // Vérifier si un appareil est sélectionné
    QModelIndexList selectedIndexes = ui->tableViewAppareils->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un appareil pour afficher son historique de vie.");
        return;
    }

    // Récupérer le numéro de série de l'appareil sélectionné
    int row = selectedIndexes.first().row();
    int numSerie = ui->tableViewAppareils->model()->index(row, 0).data().toInt();
    QString marque = ui->tableViewAppareils->model()->index(row, 2).data().toString();
    QString modele = ui->tableViewAppareils->model()->index(row, 3).data().toString();

    // Créer une requête pour récupérer l'historique des réparations de l'appareil
    QSqlQuery query;
    query.prepare("SELECT DATE_REC, DATE_FIN_EST, DES_PANNE, COUT, STATUT_R AS STATUT "
                  "FROM REPARATIONS "
                  "WHERE NUM_SERIE = :numSerie "
                  "ORDER BY DATE_REC DESC");
    query.bindValue(":numSerie", numSerie);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la récupération de l'historique des réparations: " + query.lastError().text());
        return;
    }

    // Créer une boîte de dialogue pour afficher l'historique
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Vie de l'appareil - " + marque + " " + modele + " (S/N: " + QString::number(numSerie) + ")");
    dialog->setMinimumSize(800, 400);

    QVBoxLayout *layout = new QVBoxLayout(dialog);

    // Créer un tableau pour afficher les réparations
    QTableView *tableView = new QTableView(dialog);
    QStandardItemModel *model = new QStandardItemModel(0, 5, dialog);

    // Configurer les en-têtes du tableau
    model->setHorizontalHeaderLabels({"Date début", "Date fin", "Description", "Coût", "Statut"});

    // Remplir le tableau avec les données de la requête
    int rowCount = 0;
    while (query.next()) {
        model->insertRow(rowCount);
        model->setData(model->index(rowCount, 0), query.value(0).toDate().toString("dd/MM/yyyy"));
        model->setData(model->index(rowCount, 1), query.value(1).toDate().toString("dd/MM/yyyy"));
        model->setData(model->index(rowCount, 2), query.value(2));
        model->setData(model->index(rowCount, 3), QString::number(query.value(3).toDouble(), 'f', 2) + " DT");
        model->setData(model->index(rowCount, 4), query.value(4));
        rowCount++;
    }

    // Configurer le tableau
    tableView->setModel(model);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Ajouter un résumé
    QLabel *summaryLabel = new QLabel(dialog);
    summaryLabel->setText(QString("<b>Résumé pour l'appareil %1 %2 (S/N: %3):</b> %4 réparation(s) trouvée(s)")
                              .arg(marque, modele, QString::number(numSerie), QString::number(rowCount)));

    // Ajouter les widgets au layout
    layout->addWidget(summaryLabel);
    layout->addWidget(tableView);

    // Ajouter un bouton de fermeture
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, dialog);
    layout->addWidget(buttonBox);

    // Connecter le bouton de fermeture
    connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);

    // Afficher la boîte de dialogue modale
    dialog->setLayout(layout);
    dialog->exec();
}

// ==================== GESTION DES RÉPARATIONS ====================

void MainWindow::on_btnAjouterReparation_clicked()
{
    // Validation des champs obligatoires
    QStringList requiredFields = {
        "ID Réparation",
        "Matricule Réparation",
        "Description Panne",
        "CIN Employé",
        "Numéro Série"
    };
    QStringList fieldValues = {
        ui->lineEdit_2->text().trimmed(),
        ui->lineEdit->text().trimmed(),
        ui->textEditPanne->toPlainText().trimmed(),
        ui->lineEdit_3->text().trimmed(),
        ui->lineEdit_4->text().trimmed()
    };

    if (!validateRequiredFields(requiredFields, fieldValues, "l'ajout d'une réparation")) {
        return;
    }

    int idr;
    if(!validateIdReparation(ui->lineEdit_2->text(), idr)) {
        QMessageBox::warning(this, "Erreur de saisie", "L'ID de réparation doit être un nombre positif!");
        return;
    }

    int numSerie;
    if(!validateNumSerie(ui->lineEdit_4->text(), numSerie)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le numéro de série doit être un nombre positif!");
        return;
    }

    QString descriptionPanne = ui->textEditPanne->toPlainText();
    QDate dateDepot = ui->dateEditDepot->date();
    QDate dateRetourPrevue = ui->dateEditRetourPrevue->date();
    QString statut = ui->comboBoxStatutReparation->currentText();

    double cout;
    if(!validateCout(ui->lineEditCout->text(), cout)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le coût doit être un nombre positif!");
        return;
    }

    int cinEmploye;
    if(!validateCIN(ui->lineEdit_3->text(), cinEmploye)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le CIN employé doit être un nombre entre 1 et 99,999,999!");
        return;
    }

    QString matRep = ui->lineEdit->text();

    if(dateRetourPrevue < dateDepot) {
        QMessageBox::warning(this, "Erreur de saisie", "La date de retour ne peut pas être avant la date de dépôt!");
        return;
    }

    // Vérifier que l'appareil existe
    QSqlQuery queryAppareil;
    queryAppareil.prepare("SELECT COUNT(*) FROM APPAREILLES WHERE NUM_SERIE = :numSerie");
    queryAppareil.bindValue(":numSerie", numSerie);
    queryAppareil.exec();
    queryAppareil.next();
    int countAppareil = queryAppareil.value(0).toInt();

    if(countAppareil == 0) {
        QMessageBox::warning(this, "Appareil introuvable",
                             "L'appareil avec numéro de série " + QString::number(numSerie) + " n'existe pas!");
        return;
    }

    // Vérifier que l'employé existe
    QSqlQuery queryEmploye;
    queryEmploye.prepare("SELECT COUNT(*) FROM EMPLOYER WHERE CIN_EMPLOYER = :cinEmploye");
    queryEmploye.bindValue(":cinEmploye", cinEmploye);
    queryEmploye.exec();
    queryEmploye.next();
    int countEmploye = queryEmploye.value(0).toInt();

    if(countEmploye == 0) {
        QMessageBox::warning(this, "Employé introuvable",
                             "L'employé avec CIN " + QString::number(cinEmploye) + " n'existe pas!");
        return;
    }

    Reparations r(idr, descriptionPanne, dateDepot, dateRetourPrevue, statut, cout, cinEmploye, numSerie, matRep);
    bool test = r.ajouter();

    if(test) {
        QMessageBox::information(this, "Succès", "Réparation ajoutée avec succès!");
        refreshReparationTable();
        clearReparationFields();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de la réparation!");
    }
}

void MainWindow::on_btnModifierReparation_clicked()
{
    int idr;
    // Utiliser lineEdit_2 pour l'ID de réparation
    if(!validateIdReparation(ui->lineEdit_2->text(), idr)) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez sélectionner une réparation à modifier!");
        return;
    }

    // Récupérer le numéro de série depuis lineEdit_4
    int numSerie;
    if(!validateNumSerie(ui->lineEdit_4->text(), numSerie)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le numéro de série doit être un nombre positif!");
        return;
    }

    QString descriptionPanne = ui->textEditPanne->toPlainText();
    QDate dateDepot = ui->dateEditDepot->date();
    QDate dateRetourPrevue = ui->dateEditRetourPrevue->date();
    QString statut = ui->comboBoxStatutReparation->currentText();

    double cout;
    if(!validateCout(ui->lineEditCout->text(), cout)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le coût doit être un nombre positif!");
        return;
    }

    // Récupérer le CIN employé depuis lineEdit_3
    int cinEmploye;
    if(!validateCIN(ui->lineEdit_3->text(), cinEmploye)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le CIN employé doit être un nombre entre 1 et 99,999,999!");
        return;
    }

    // Récupérer le matricule réparation depuis lineEdit (premier champ)
    QString matRep = ui->lineEdit->text();
    if(matRep.isEmpty()) {
        QMessageBox::warning(this, "Champ requis", "Le matricule de réparation est obligatoire!");
        return;
    }

    if(descriptionPanne.isEmpty()) {
        QMessageBox::warning(this, "Champ requis", "La description de la panne est obligatoire!");
        return;
    }

    if(dateRetourPrevue < dateDepot) {
        QMessageBox::warning(this, "Erreur de saisie", "La date de retour ne peut pas être avant la date de dépôt!");
        return;
    }

    // Vérifier que l'appareil existe
    QSqlQuery queryAppareil;
    queryAppareil.prepare("SELECT COUNT(*) FROM APPAREILLES WHERE NUM_SERIE = :numSerie");
    queryAppareil.bindValue(":numSerie", numSerie);
    queryAppareil.exec();
    queryAppareil.next();
    int countAppareil = queryAppareil.value(0).toInt();

    if(countAppareil == 0) {
        QMessageBox::warning(this, "Appareil introuvable",
                             "L'appareil avec numéro de série " + QString::number(numSerie) + " n'existe pas!");
        return;
    }

    // Vérifier que l'employé existe
    QSqlQuery queryEmploye;
    queryEmploye.prepare("SELECT COUNT(*) FROM EMPLOYER WHERE CIN_EMPLOYER = :cinEmploye");
    queryEmploye.bindValue(":cinEmploye", cinEmploye);
    queryEmploye.exec();
    queryEmploye.next();
    int countEmploye = queryEmploye.value(0).toInt();

    if(countEmploye == 0) {
        QMessageBox::warning(this, "Employé introuvable",
                             "L'employé avec CIN " + QString::number(cinEmploye) + " n'existe pas!");
        return;
    }

    Reparations r(idr, descriptionPanne, dateDepot, dateRetourPrevue, statut, cout, cinEmploye, numSerie, matRep);
    bool test = r.modifier(idr);

    if(test) {
        QMessageBox::information(this, "Succès", "Réparation modifiée avec succès!");
        refreshReparationTable();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification de la réparation!");
    }
}

void MainWindow::on_btnSupprimerReparation_clicked()
{
    int idr;
    // Utiliser lineEdit_2 pour l'ID de réparation
    if(!validateIdReparation(ui->lineEdit_2->text(), idr)) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez sélectionner une réparation à supprimer!");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer cette réparation?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        bool test = rep.supprimer(idr);

        if(test) {
            QMessageBox::information(this, "Succès", "Réparation supprimée avec succès!");
            refreshReparationTable();
            clearReparationFields();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression de la réparation!");
        }
    }
}

void MainWindow::on_btnRechercherReparation_clicked()
{
    QString critere = ui->comboBoxCritereReparation->currentText();
    QString valeur = ui->lineEditRechercheReparation->text();

    if(valeur.isEmpty()) {
        QMessageBox::warning(this, "Champ requis", "Veuillez saisir un terme de recherche!");
        return;
    }

    ui->tableViewReparationsListe->setModel(rep.rechercher(critere, valeur));
}

void MainWindow::on_btnReinitialiserReparation_clicked()
{
    // Tri par coût comme indiqué dans l'interface "trier par cout"
    QSqlQueryModel* model = new QSqlQueryModel();

    // Vérifier l'ordre de tri (croissant ou décroissant)
    static bool triAscendant = false;
    QString ordreTri = triAscendant ? "ASC" : "DESC";

    model->setQuery(QString("SELECT IDR, DES_PANNE, DATE_REC, DATE_FIN_EST, STATUT_R, COUT, CIN_EMP, NUM_SERIE, MAT_REP FROM REPARATIONS ORDER BY COUT %1").arg(ordreTri));

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Réparation"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Description Panne"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Réception"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Fin Estimée"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Coût"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("CIN Employé"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Numéro Série"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Matricule Réparation"));

    ui->tableViewReparationsListe->setModel(model);
    ui->lineEditRechercheReparation->clear();

    // Alterner l'ordre de tri pour le prochain clic
    triAscendant = !triAscendant;

    // Mettre à jour le texte du bouton pour indiquer l'ordre de tri
    if (triAscendant) {
        ui->btnReinitialiserReparation->setText("trier par cout ↑");
    } else {
        ui->btnReinitialiserReparation->setText("trier par cout ↓");
    }
}

void MainWindow::on_tableViewReparationsListe_clicked(const QModelIndex &index)
{
    int row = index.row();

    // Remplir les champs avec les données de la ligne sélectionnée
    ui->lineEdit_2->setText(ui->tableViewReparationsListe->model()->index(row, 0).data().toString()); // IDR
    ui->textEditPanne->setText(ui->tableViewReparationsListe->model()->index(row, 1).data().toString()); // DES_PANNE
    ui->dateEditDepot->setDate(ui->tableViewReparationsListe->model()->index(row, 2).data().toDate()); // DATE_REC
    ui->dateEditRetourPrevue->setDate(ui->tableViewReparationsListe->model()->index(row, 3).data().toDate()); // DATE_FIN_EST
    ui->comboBoxStatutReparation->setCurrentText(ui->tableViewReparationsListe->model()->index(row, 4).data().toString()); // STATUT_R
    ui->lineEditCout->setText(ui->tableViewReparationsListe->model()->index(row, 5).data().toString()); // COUT
    ui->lineEdit_3->setText(ui->tableViewReparationsListe->model()->index(row, 6).data().toString()); // CIN_EMP
    ui->lineEdit_4->setText(ui->tableViewReparationsListe->model()->index(row, 7).data().toString()); // NUM_SERIE
    ui->lineEdit->setText(ui->tableViewReparationsListe->model()->index(row, 8).data().toString()); // MAT_REP
}

void MainWindow::on_btnGenererRapport_clicked()
{
    // Implementation for generating reports
    QMessageBox::information(this, "Génération de rapport", "La fonctionnalité de génération de rapport n'est pas implémentée.");
}

void MainWindow::highlightEmptyFields(const QStringList& fields, const QStringList& values)
{
    // Réinitialiser tous les styles d'abord
    QList<QLineEdit*> lineEdits = findChildren<QLineEdit*>();
    for (QLineEdit* lineEdit : lineEdits) {
        lineEdit->setStyleSheet("background-color: white; border: 1px solid #6C757D;");
    }

    QList<QComboBox*> comboBoxes = findChildren<QComboBox*>();
    for (QComboBox* comboBox : comboBoxes) {
        comboBox->setStyleSheet("background-color: white; border: 1px solid #6C757D;");
    }

    QList<QTextEdit*> textEdits = findChildren<QTextEdit*>();
    for (QTextEdit* textEdit : textEdits) {
        textEdit->setStyleSheet("background-color: white; border: 1px solid #6C757D;");
    }

    // Mettre en évidence les champs vides
    for (int i = 0; i < fields.size(); ++i) {
        if (values[i].isEmpty()) {
            // Trouver le widget correspondant au champ
            if (fields[i] == "CIN") {
                ui->lineEditId->setStyleSheet("background-color: #FFE6E6; border: 2px solid #DC3545;");
            } else if (fields[i] == "Nom") {
                ui->lineEditMarque_3->setStyleSheet("background-color: #FFE6E6; border: 2px solid #DC3545;");
            } else if (fields[i] == "Prénom") {
                ui->lineEditMarque_2->setStyleSheet("background-color: #FFE6E6; border: 2px solid #DC3545;");
            } else if (fields[i] == "Téléphone") {
                ui->lineEditTelephone->setStyleSheet("background-color: #FFE6E6; border: 2px solid #DC3545;");
            } else if (fields[i] == "Numéro de série") {
                ui->lineEditNumeroSerie->setStyleSheet("background-color: #FFE6E6; border: 2px solid #DC3545;");
            } else if (fields[i] == "Marque") {
                ui->lineEditMarque->setStyleSheet("background-color: #FFE6E6; border: 2px solid #DC3545;");
            } else if (fields[i] == "Modèle") {
                ui->lineEditModele->setStyleSheet("background-color: #FFE6E6; border: 2px solid #DC3545;");
            } else if (fields[i] == "ID Réparation") {
                ui->lineEdit_2->setStyleSheet("background-color: #FFE6E6; border: 2px solid #DC3545;");
            } else if (fields[i] == "Matricule Réparation") {
                ui->lineEdit->setStyleSheet("background-color: #FFE6E6; border: 2px solid #DC3545;");
            } else if (fields[i] == "Description Panne") {
                ui->textEditPanne->setStyleSheet("background-color: #FFE6E6; border: 2px solid #DC3545;");
            } else if (fields[i] == "CIN Employé") {
                ui->lineEdit_3->setStyleSheet("background-color: #FFE6E6; border: 2px solid #DC3545;");
            } else if (fields[i] == "Numéro Série") {
                ui->lineEdit_4->setStyleSheet("background-color: #FFE6E6; border: 2px solid #DC3545;");
            }
        }
    }
}
void MainWindow::on_btnCalendrier_clicked()
{
    // Création d'une boîte de dialogue de calendrier
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Calendrier des Appareils");
    dialog->setMinimumSize(600, 500);
    dialog->setStyleSheet("QDialog { background-color: #f8f9fa; }");

    // Création d'un layout vertical pour la boîte de dialogue
    QVBoxLayout *layout = new QVBoxLayout(dialog);

    // Création d'un calendrier
    QCalendarWidget *calendar = new QCalendarWidget(dialog);
    calendar->setGridVisible(true);

    calendar->setStyleSheet(
        "QCalendarWidget {"
        "    background-color: white;"
        "    border: 1px solid #dee2e6;"
        "    border-radius: 4px;"
        "}"
        "QCalendarWidget QWidget {"
        "    alternate-background-color: #f8f9fa;"
        "}"
        "QCalendarWidget QToolButton {"
        "    background-color: #35b95f;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 4px;"
        "    padding: 5px;"
        "}"
        "QCalendarWidget QMenu {"
        "    background-color: white;"
        "    border: 1px solid #dee2e6;"
        "}"
        "QCalendarWidget QSpinBox {"
        "    padding: 2px;"
        "}"
        );

    // Création d'une zone de texte pour afficher les détails
    QTextEdit *details = new QTextEdit(dialog);
    details->setReadOnly(true);
    details->setStyleSheet("background-color: white; border: 1px solid #dee2e6; border-radius: 4px; padding: 8px;");

    // Connexion du signal de sélection de date au slot d'affichage des détails
    connect(calendar, &QCalendarWidget::clicked, [=](const QDate &date) {
        QSqlQuery query;

        qDebug() << "Exécution de la requête pour la date:" << date.toString("yyyy-MM-dd");

        // Recherche uniquement pour la date exacte sélectionnée
        query.prepare("SELECT a.NUM_SERIE, a.TYPE, a.MARQUE, a.MODELE, c.NOM, c.PRENOM, a.DATE_ACQ "
                      "FROM APPAREILLES a "
                      "LEFT JOIN CLIENT c ON a.CIN_CLIENT = c.CIN_CLIENT "
                      "WHERE TRUNC(a.DATE_ACQ) = :date "
                      "ORDER BY a.NUM_SERIE ASC");
        query.bindValue(":date", date);

        QString detailsText = QString("<h3>Appareils enregistrés le %1</h3><hr>")
                                  .arg(date.toString("dd/MM/yyyy"));

        if (query.exec()) {
            qDebug() << "Requête exécutée avec succès";
            int count = 0;

            while (query.next()) {
                count++;
                QDate dateAchat = query.value(6).toDate();

                detailsText += QString(
                                   "<p><b>%1 %2</b> (%3)<br>"
                                   "Numéro de série: %4<br>"
                                   "Date d'acquisition: %5<br>"
                                   "Client: %6 %7</p><hr>")
                                   .arg(query.value(2).toString())  // Marque
                                   .arg(query.value(3).toString())  // Modèle
                                   .arg(query.value(1).toString())  // Type
                                   .arg(query.value(0).toInt())     // Numéro de série
                                   .arg(dateAchat.toString("dd/MM/yyyy"))  // Date acquisition
                                   .arg(query.value(4).toString())  // Nom client
                                   .arg(query.value(5).toString()); // Prénom client
            }

            qDebug() << "Nombre d'appareils trouvés:" << count;

            if (count == 0) {
                detailsText += "<p style='color: #6c757d;'>Aucun appareil trouvé pour cette date.</p>";
            }
        } else {
            QString error = query.lastError().text();
            qDebug() << "Erreur lors de l'exécution de la requête:" << error;
            detailsText += QString("<p style='color: #dc3545;'>Erreur lors de la récupération des données : %1</p>").arg(error);
        }

        details->setHtml(detailsText);
    });

    // Ajout des widgets au layout
    layout->addWidget(calendar);

    // Groupe pour les détails
    QGroupBox *detailsGroup = new QGroupBox("Détails des appareils", dialog);
    detailsGroup->setStyleSheet("QGroupBox { font-weight: bold; color: #35b95f; }");
    QVBoxLayout *detailsLayout = new QVBoxLayout(detailsGroup);
    detailsLayout->addWidget(details);

    layout->addWidget(detailsGroup);

    // Ajout d'un bouton de fermeture
    QPushButton *closeButton = new QPushButton("Fermer", dialog);
    closeButton->setStyleSheet("QPushButton { "
                               "background-color: #35b95f; "
                               "color: white; "
                               "border: none; "
                               "padding: 8px 16px; "
                               "border-radius: 4px; "
                               "min-width: 100px; "
                               "}"
                               "QPushButton:hover { "
                               "background-color: #2d9f4f; "
                               "}");

    connect(closeButton, &QPushButton::clicked, dialog, &QDialog::accept);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(closeButton);
    buttonLayout->addStretch();

    layout->addLayout(buttonLayout);

    // Déclenche le clic sur la date actuelle pour afficher les détails immédiatement
    emit calendar->clicked(calendar->selectedDate());

    // Affichage de la boîte de dialogue
    dialog->exec();

    // Nettoyage
    delete dialog;
}
void MainWindow::on_btnAnalyserFidelite_clicked()
{
    int cin;
    if(!validateCIN(ui->lineEditIdClient->text(), cin)) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un client!");
        return;
    }

    Client client;
    client.setCin(cin);

    // Récupérer les données du client pour affichage
    QSqlQuery query;
    query.prepare("SELECT NOM, PRENOM FROM CLIENT WHERE CIN_CLIENT = :cin");
    query.bindValue(":cin", cin);
    if (query.exec() && query.next()) {
        client.setNom(query.value(0).toString());
        client.setPrenom(query.value(1).toString());
    }

    QMap<QString, QVariant> donnees = client.getDonneesFidelite();

    QString message = QString(
                          "📊 ANALYSE DE FIDÉLITÉ CLIENT\n\n"
                          "Client: %1 %2 (CIN: %3)\n\n"
                          "🎯 Score de Fidélité: %4/100\n"
                          "📈 Profil: %5\n"
                          "📅 Prochain retour prédit: %6 jours\n\n"
                          "📋 DÉTAILS COMPORTEMENTAUX:\n"
                          "• Nombre de visites: %7\n"
                          "• Total dépensé: %8 €\n"
                          "• Taux d'annulation: %9%\n"
                          "• Variété appareils: %10\n"
                          "• Dernière visite: %11\n"
                          "• Régularité: %12 jours en moyenne\n\n"
                          "💡 RECOMMANDATIONS:"
                          ).arg(client.getNom())
                          .arg(client.getPrenom())
                          .arg(cin)
                          .arg(donnees["score"].toDouble(), 0, 'f', 1)
                          .arg(donnees["profil"].toString())
                          .arg(donnees["prochain_retour"].toInt())
                          .arg(donnees["nombre_visites"].toInt())
                          .arg(donnees["total_depenses"].toDouble(), 0, 'f', 2)
                          .arg(donnees["taux_annulation"].toDouble(), 0, 'f', 1)
                          .arg(donnees["variete_appareils"].toInt())
                          .arg(donnees["derniere_visite"].toString())
                          .arg(donnees["regularite"].toDouble(), 0, 'f', 1);

    // Ajouter les recommandations selon le profil
    QString profil = donnees["profil"].toString();
    if (profil == "Client à Risque") {
        message += "\n• 🔴 Client à risque - Action de fidélisation urgente";
        message += "\n• 💰 Offrir une promotion spéciale";
        message += "\n• 📞 Contacter pour feedback";
    } else if (profil == "Client Fidèle") {
        message += "\n• 🟢 Client fidèle - Program de fidélité premium";
        message += "\n• 🎁 Offrir des avantages exclusifs";
        message += "\n• 🤝 Demander des témoignages";
    } else {
        message += "\n• 🟡 Client standard - Encourager la fidélisation";
        message += "\n• 📧 Envoyer des offres personnalisées";
    }

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Analyse de Fidélité Client - Smart Repair Hub");
    msgBox.setText(message);
    msgBox.setIcon(QMessageBox::Information);

    QPushButton *btnFermer = msgBox.addButton("Fermer", QMessageBox::AcceptRole);

    msgBox.exec();

}

void MainWindow::on_btnMaintenancePreventive_clicked()
{
    int cin;
    if(!validateCIN(ui->lineEditIdClient->text(), cin)) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un client!");
        return;
    }

    Client client;
    client.setCin(cin);

    // Récupérer les données du client
    QSqlQuery query;
    query.prepare("SELECT NOM, PRENOM FROM CLIENT WHERE CIN_CLIENT = :cin");
    query.bindValue(":cin", cin);
    if (query.exec() && query.next()) {
        client.setNom(query.value(0).toString());
        client.setPrenom(query.value(1).toString());
    }

    QMap<QString, QVariant> analyse = client.analyserAppareilsMaintenance();
    QList<QVariant> recommandations = analyse["recommandations"].toList();

    if (recommandations.isEmpty()) {
        QMessageBox::information(this, "Maintenance Préventive",
                                 "✅ Aucune maintenance préventive recommandée pour le moment.\n\n"
                                 "Tous les appareils du client sont en bon état de maintenance.");
        return;
    }

    QString message = QString(
                          "🔧 MAINTENANCE PRÉVENTIVE RECOMMANDÉE\n\n"
                          "Client: %1 %2 (CIN: %3)\n"
                          "Date d'analyse: %4\n\n"
                          ).arg(client.getNom())
                          .arg(client.getPrenom())
                          .arg(cin)
                          .arg(analyse["date_analyse"].toString());

    double coutTotal = 0.0;
    int hautePriorite = 0;

    for (const QVariant &recoVar : recommandations) {
        QMap<QString, QVariant> reco = recoVar.toMap();
        message += QString("📱 %1\n").arg(reco["appareil"].toString());
        message += QString("   🔧 Action: %1\n").arg(reco["action"].toString());
        message += QString("   🚨 Priorité: %1\n").arg(reco["priorite"].toString());
        message += QString("   💰 Coût estimé: %1 €\n").arg(reco["cout_estime"].toDouble(), 0, 'f', 2);
        message += QString("   📝 Description: %1\n").arg(reco["description"].toString());
        message += QString("   ⏳ Âge: %1 mois\n\n").arg(reco["age_mois"].toInt());

        coutTotal += reco["cout_estime"].toDouble();
        if (reco["priorite"].toString() == "Haute") {
            hautePriorite++;
        }
    }

    message += QString("💰 COÛT TOTAL ESTIMÉ: %1 €\n").arg(coutTotal, 0, 'f', 2);
    message += QString("🚨 ACTIONS HAUTE PRIORITÉ: %1\n\n").arg(hautePriorite);

    if (hautePriorite > 0) {
        message += "⚠️  Attention: Maintenance urgente recommandée!";
    }

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Maintenance Préventive - Smart Repair Hub");
    msgBox.setText(message);
    msgBox.setIcon(hautePriorite > 0 ? QMessageBox::Warning : QMessageBox::Information);

    QPushButton *btnFermer = msgBox.addButton("Fermer", QMessageBox::AcceptRole);

    msgBox.exec();

}


void MainWindow::afficherProfilClient(int cin)
{
    // Cette méthode peut être utilisée pour afficher en permanence le profil dans l'interface
    Client client;
    client.setCin(cin);

    QMap<QString, QVariant> donnees = client.getDonneesFidelite();

    // Mise à jour des labels d'affichage du profil
    ui->labelScoreFidelite->setText(QString("%1/100").arg(donnees["score"].toDouble(), 0, 'f', 1));
    ui->labelProfilClient->setText(donnees["profil"].toString());
    ui->labelProchainRetour->setText(QString("%1 jours").arg(donnees["prochain_retour"].toInt()));

    // Appliquer un style selon le profil
    QString styleSheet;
    if (donnees["profil"].toString() == "Client Fidèle") {
        styleSheet = "color: #28a745; font-weight: bold;";
    } else if (donnees["profil"].toString() == "Client à Risque") {
        styleSheet = "color: #dc3545; font-weight: bold;";
    } else {
        styleSheet = "color: #fd7e14; font-weight: bold;";
    }

    ui->labelProfilClient->setStyleSheet(styleSheet);
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
        "SELECT A.TYPE, A.MARQUE, R.DES_PANNE, "
        "(R.DATE_FIN_EST - R.DATE_REC) as duree "
        "FROM REPARATION R "
        "JOIN APPAREILLES A ON R.NUM_SERIE = A.NUM_SERIE "
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
    QString numSerie = ui->lineEdit_4->text().trimmed();
    QString desPanne = ui->textEditPanne->toPlainText().trimmed();
    QDate dateRec = ui->dateEditDepot->date();

    if (numSerie.isEmpty() || desPanne.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir le numéro de série et la description de la panne.");
        return;
    }

    // Récupérer les informations détaillées de l'appareil
    QSqlQuery qAppareil;
    qAppareil.prepare("SELECT TYPE, MARQUE, MODELE FROM APPAREILLES WHERE NUM_SERIE = :num");
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
    ui->dateEditRetourPrevue->setDate(dateFinPred);

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
 *   EXPORTER FACTURE PDF - FORMAT FACTURE (DISPOSITION VERTICALE)
 ---------------------------------------------------------*/
void MainWindow::on_BTN_EXPORTER_clicked()
{
    QString idReparation = ui->lineEdit_2->text();

    if (idReparation.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un ID de réparation pour générer la facture !");
        return;
    }

    // Récupérer les informations de la réparation
    QSqlQuery qReparation;
    qReparation.prepare(
        "SELECT R.IDR, R.MAT_REP, R.DES_PANNE, R.DATE_REC, R.DATE_FIN_EST, "
        "R.STATUT_R, R.COUT, R.NUM_SERIE, A.TYPE, A.MARQUE, A.MODELE, "
        "C.NOM, C.PRENOM, C.TELEPHONE "
        "FROM REPARATIONS R "
        "JOIN APPAREILLES A ON R.NUM_SERIE = A.NUM_SERIE "
        "JOIN CLIENT C ON A.CIN_CLIENT = C.CIN_CLIENT "
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
    pdf.setPageMargins(QMarginsF(25, 25, 25, 25));
    pdf.setResolution(150);

    QPainter painter(&pdf);

    if (!painter.isActive()) {
        QMessageBox::critical(this, "Erreur", "Impossible de créer le fichier PDF !");
        return;
    }

    // Define colors
    QColor darkBlue(0, 51, 102);     // Dark blue for headers
    QColor green(53, 185, 95);       // Green for accents
    QColor lightGray(240, 240, 240); // Light gray for backgrounds

    // ===== EN-TÊTE FACTURE =====
    painter.setPen(darkBlue);
    painter.setFont(QFont("Arial", 28, QFont::Bold));
    painter.drawText(200, 80, "FACTURE");

    painter.setFont(QFont("Arial", 9));
    painter.drawText(200, 105, "Smart Repair Hub - Service de réparation professionnel");

    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.drawText(200, 130, "Smart Repair Hub");
    painter.drawText(200, 155, "123 Avenue de la République, Tunis");
    painter.drawText(200, 180, "Tél: +216 12 345 678 | Email: contact@repair.tn");

    // Ligne de séparation avec green color
    painter.setPen(green);
    painter.drawLine(50, 200, 550, 200);

    int y = 240;  // Starting position

    // ===== INFORMATIONS CLIENT =====
    painter.setPen(darkBlue);
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(50, y, "🧔 INFORMATIONS CLIENT");
    y += 35;

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(70, y, QString("Nom complet: %1 %2").arg(prenomClient).arg(nomClient));
    y += 25;
    painter.drawText(70, y, QString("Téléphone: %1").arg(telephone));
    y += 50;  // Espace après la section client

    // ===== INFORMATIONS FACTURE =====
    painter.setPen(darkBlue);
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(50, y, "📄 INFORMATIONS FACTURE");
    y += 35;

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(70, y, QString("Numéro de facture: REF-%1").arg(id));
    y += 25;
    painter.drawText(70, y, QString("Date de facturation: %1").arg(QDate::currentDate().toString("dd/MM/yyyy")));
    y += 25;
    if (!matricule.isEmpty()) {
        painter.drawText(70, y, QString("Matricule réparation: %1").arg(matricule));
        y += 25;
    }
    painter.drawText(70, y, QString("Statut: %1").arg(statut));
    y += 40;  // Espace avant la section suivante

    // ===== DÉTAILS DE LA RÉPARATION =====
    painter.setPen(darkBlue);
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(50, y, "🔧 DÉTAILS DE LA RÉPARATION");
    y += 35;

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(70, y, QString("Type d'appareil: %1").arg(typeAppareil));
    y += 25;
    painter.drawText(70, y, QString("Marque: %1").arg(marque));
    y += 25;
    painter.drawText(70, y, QString("Modèle: %1").arg(modele));
    y += 25;
    painter.drawText(70, y, QString("Description de la panne:"));
    y += 20;

    // Description de la panne avec cadre
    painter.setPen(Qt::darkGray);
    painter.drawRect(70, y, 480, 60);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 10));

    // Ajuster le texte pour qu'il tienne dans le cadre
    QString panneText = descriptionPanne;
    if (panneText.length() > 150) {
        panneText = panneText.left(147) + "...";
    }

    // Diviser le texte en lignes si nécessaire
    int textY = y + 15;
    int maxWidth = 470;
    QString currentLine;

    for (const QChar &c : panneText) {
        QFontMetrics metrics(painter.font());
        if (metrics.horizontalAdvance(currentLine + c) < maxWidth) {
            currentLine += c;
        } else {
            painter.drawText(75, textY, currentLine);
            textY += 15;
            currentLine = c;
        }
    }
    if (!currentLine.isEmpty()) {
        painter.drawText(75, textY, currentLine);
    }

    y += 80;  // Espace après la description

    // Ligne de séparation
    painter.setPen(green);
    painter.drawLine(50, y, 550, y);
    y += 35;

    // ===== COÛT ET TOTAL =====
    painter.setPen(darkBlue);
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(50, y, "💰 COÛT ET FACTURATION");
    y += 35;

    // Coût de réparation
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(70, y, "Coût de réparation:");
    painter.setPen(green);
    painter.setFont(QFont("Arial", 14, QFont::Bold));
    painter.drawText(300, y, QString::number(cout, 'f', 3) + " DT");
    y += 30;

    // TVA
    double tva = cout * 0.19;
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(70, y, "TVA (19%):");
    painter.drawText(250, y, QString::number(tva, 'f', 3) + " DT");
    y += 30;

    // Ligne de séparation totale
    painter.setPen(green);
    painter.drawLine(70, y, 350, y);
    y += 40;

    // TOTAL
    double total = cout + tva;
    painter.setPen(darkBlue);
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(70, y, "TOTAL À PAYER:");
    painter.setPen(green);
    painter.setFont(QFont("Arial", 18, QFont::Bold));
    painter.drawText(350, y, QString::number(total, 'f', 3) + " DT");
    y += 60;

    // ===== INFORMATIONS SUPPLEMENTAIRES =====
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 10));
    painter.drawText(50, y, QString("Date de dépôt: %1").arg(dateReception.toString("dd/MM/yyyy")));
    y += 20;
    painter.drawText(50, y, QString("Date de fin estimée: %1").arg(dateFin.toString("dd/MM/yyyy")));
    y += 40;

    // ===== PIED DE PAGE =====
    painter.setPen(green);
    painter.drawLine(50, y, 550, y);
    y += 25;

    painter.setPen(darkBlue);
    painter.setFont(QFont("Arial", 14, QFont::Bold));
    painter.drawText(200, y, "Merci pour votre confiance !");
    y += 35;

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(50, y, "Smart Repair Hub - RC: 123456/A/M/000 - IF: 12345678");
    y += 20;
    painter.drawText(50, y, "Garantie: 3 mois sur les pièces et main d'œuvre");
    y += 20;
    painter.drawText(50, y, "Cet appareil est garanti contre tout défaut de fabrication pendant 90 jours");

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

    if (q.exec("SELECT COUNT(*) FROM REPARATIONS") && q.next()) {
        total = q.value(0).toInt();
    }

    if (q.exec("SELECT COUNT(*) FROM REPARATIONS WHERE STATUT_R = 'En attente'") && q.next()) {
        enAttente = q.value(0).toInt();
    }

    if (q.exec("SELECT COUNT(*) FROM REPARATIONS WHERE STATUT_R = 'En cours'") && q.next()) {
        enCours = q.value(0).toInt();
    }

    if (q.exec("SELECT COUNT(*) FROM REPARATIONS WHERE STATUT_R = 'Terminee'") && q.next()) {
        terminees = q.value(0).toInt();
    }

    if (q.exec("SELECT COUNT(*) FROM REPARATIONS WHERE STATUT_R = 'Annulee'") && q.next()) {
        annulees = q.value(0).toInt();
    }

    if (q.exec("SELECT SUM(COUT) FROM REPARATIONS WHERE STATUT_R = 'Terminee'") && q.next()) {
        coutTotal = q.value(0).toDouble();
    }

    // Afficher les statistiques avec diagramme dans une message box
    afficherStatistiquesAvecDiagramme(enAttente, enCours, terminees, annulees, coutTotal, total);
}

void MainWindow::afficherStatistiquesAvecDiagramme(int enAttente, int enCours, int terminees, int annulees, double coutTotal, int total)
{
    // On utilise labelGraphiquePlaceholder comme conteneur du graphique
    QLayout *oldLayout = ui->labelGraphiquePlaceholder->layout();
    if (oldLayout) {
        QLayoutItem *child;
        while ((child = oldLayout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
        delete oldLayout;
    }

    // Créer le Pie Chart
    QPieSeries *series = new QPieSeries();
    if (enAttente > 0)  series->append("En attente", enAttente);
    if (enCours > 0)    series->append("En cours", enCours);
    if (terminees > 0)  series->append("Terminées", terminees);
    if (annulees > 0)   series->append("Annulées", annulees);

    // Couleurs modernes
    QList<QColor> colors = { QColor("#FF6B6B"), QColor("#4ECDC4"), QColor("#45B7D1"), QColor("#96CEB4") };
    for (int i = 0; i < series->slices().size(); ++i) {
        series->slices().at(i)->setBrush(colors[i % colors.size()]);
        series->slices().at(i)->setLabelVisible();
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des Réparations par Statut");
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(500, 400);

    // Créer un layout pour le label
    QVBoxLayout *layout = new QVBoxLayout(ui->labelGraphiquePlaceholder);
    layout->addWidget(chartView);
    ui->labelGraphiquePlaceholder->setLayout(layout);

    // Optionnel : 2ème graphique (ex: revenus)
    // Tu peux faire pareil avec labelGraphique2Placeholder si tu veux
}

// ==================== TWILIO WHATSAPP ====================
QString MainWindow::formaterNumeroTwilio(const QString &telephone)
{
    QString num = telephone.trimmed();
    qDebug() << "Formatage numéro - Entrée:" << num;

    // Supprimer tous les caractères non numériques sauf le +
    num = num.remove(QRegularExpression("[^0-9+]"));

    qDebug() << "Après nettoyage:" << num;

    // Vérifier si c'est déjà un format international
    if (num.startsWith("+")) {
        // Déjà en format E.164
        qDebug() << "Déjà format E.164:" << num;
        return num;
    }

    // Format pour Twilio: doit être E.164 format (e.g., +21622738308)
    if (num.length() == 8) {
        // Format local tunisien: 22738308 -> +21622738308
        num = "+216" + num;
    }
    else if (num.length() == 9 && num.startsWith("9")) {
        // Format mobile tunisien: 922738308 -> +21622738308
        num = "+216" + num.mid(1);
    }
    else if (num.length() == 10 && num.startsWith("0")) {
        // Format local avec 0: 022738308 -> +21622738308
        num = "+216" + num.mid(1);
    }
    else if (num.length() == 11 && num.startsWith("216")) {
        // Format: 21622738308 -> +21622738308
        num = "+" + num;
    }
    else if (num.startsWith("00216")) {
        // Format international: 0021622738308 -> +21622738308
        num = "+216" + num.mid(5);
    }
    else {
        // Essayer de formater comme numéro tunisien par défaut
        QString numNettoye = num.remove(QRegularExpression("[^0-9]"));
        if (numNettoye.length() == 8) {
            num = "+216" + numNettoye;
        } else {
            // Garder tel quel et laisser Twilio gérer l'erreur
            num = "+" + numNettoye;
        }
    }

    qDebug() << "Format final Twilio:" << num;

    // Validation basique
    if (!num.startsWith("+") || num.length() < 10) {
        qDebug() << "⚠️ Format de numéro potentiellement invalide:" << num;
    }

    return num;
}

void MainWindow::sauvegarderWhatsAppHistorique(const QString &telephone, const QString &message, const QString &clientName, bool success, const QString &reponse)
{
    QStringList possiblePaths = {
        QCoreApplication::applicationDirPath() + "/historique_whatsapp.txt",
        QDir::currentPath() + "/historique_whatsapp.txt",
        QDir::homePath() + "/historique_whatsapp.txt",
        "historique_whatsapp.txt",
        "C:/temp/historique_whatsapp.txt"
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
                stream << "📨 Réponse API: " << reponse << "\n";
            }
            stream << "🔧 Service: Twilio WhatsApp\n";
            stream << "🔑 Account SID: " << TWILIO_ACCOUNT_SID << "\n";
            stream << "💾 Fichier: " << filePath << "\n";
            stream << "============================\n\n";
            file.close();

            saved = true;
            savedPath = filePath;
            qDebug() << "✓ WhatsApp sauvegardé dans:" << filePath;
            break;
        } else {
            qDebug() << "✗ Échec sauvegarde WhatsApp:" << filePath << "- Erreur:" << file.errorString();
        }
    }

    if (!saved) {
        qDebug() << "✗ Impossible de sauvegarder WhatsApp dans aucun emplacement";
    }
}

bool MainWindow::verifierConnexionInternet()
{
    QNetworkAccessManager nam;
    QNetworkRequest request(QUrl("https://www.google.com"));
    QNetworkReply *reply = nam.get(request);

    QEventLoop loop;
    QTimer timer;
    timer.setSingleShot(true);

    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start(10000); // 10 secondes timeout

    loop.exec();

    bool connected = (reply->error() == QNetworkReply::NoError);
    reply->deleteLater();

    qDebug() << "Vérification connexion Internet:" << (connected ? "✓ CONNECTÉ" : "✗ DÉCONNECTÉ");
    return connected;
}

void MainWindow::envoyerWhatsAppTwilio(const QString &telephone, const QString &message, const QString &clientName)
{
    QString numeroPropre = formaterNumeroTwilio(telephone);

    qDebug() << "=== ENVOI WHATSAPP AVEC CURL ===";
    qDebug() << "📞 Destinataire:" << numeroPropre;

    // Préparer la commande curl
    QStringList curlArgs;
    curlArgs << "-X" << "POST"
             << TWILIO_API_URL
             << "--data-urlencode" << ("To=whatsapp:" + numeroPropre)
             << "--data-urlencode" << ("From=whatsapp:" + TWILIO_PHONE_NUMBER)
             << "--data-urlencode" << ("Body=" + message)
             << "-u" << (TWILIO_ACCOUNT_SID + ":" + TWILIO_AUTH_TOKEN).toUtf8()
             << "--silent"
             << "--show-error";

    qDebug() << "Commande curl:" << "curl" << curlArgs.join(" ");

    QProcess process;
    process.start("curl", curlArgs);
    process.waitForFinished(30000); // 30 secondes timeout

    if (process.exitCode() == 0) {
        QString output = process.readAllStandardOutput();
        qDebug() << "✅ Succès - Réponse Twilio:" << output;

        QMessageBox::information(this, "✅ Succès",
                                 "Message WhatsApp envoyé avec succès !\n\n"
                                 "Destinataire: " + clientName + "\n"
                                                    "Téléphone: " + telephone);
    } else {
        QString error = process.readAllStandardError();
        QString output = process.readAllStandardOutput();

        qDebug() << "❌ Erreur curl - Code:" << process.exitCode();
        qDebug() << "Erreur:" << error;
        qDebug() << "Output:" << output;

        QString errorMsg = "❌ Échec de l'envoi WhatsApp\n\n";

        if (error.contains("Could not resolve host")) {
            errorMsg += "Problème de connexion Internet";
        } else if (error.contains("SSL certificate problem")) {
            errorMsg += "Problème de certificat SSL";
        } else if (error.contains("401")) {
            errorMsg += "Erreur d'authentification Twilio\nVérifiez SID/Token";
        } else if (error.contains("400")) {
            errorMsg += "Requête incorrecte\nVérifiez le format du numéro";
        } else {
            errorMsg += "Erreur: " + error;
        }

        QMessageBox::critical(this, "❌ Erreur", errorMsg);
    }
}

void MainWindow::envoyerSMSTwilio(const QString &telephone, const QString &message, const QString &clientName)
{
    QString numeroPropre = formaterNumeroTwilio(telephone);

    qDebug() << "=== ENVOI SMS AVEC CURL ===";
    qDebug() << "📞 Destinataire SMS:" << numeroPropre;

    // Préparer la commande curl pour SMS (regular SMS instead of WhatsApp)
    QStringList curlArgs;
    curlArgs << "-X" << "POST"
             << TWILIO_API_URL
             << "--data-urlencode" << ("To=" + numeroPropre)
             << "--data-urlencode" << ("From=" + TWILIO_PHONE_NUMBER)
             << "--data-urlencode" << ("Body=" + message)
             << "-u" << (TWILIO_ACCOUNT_SID + ":" + TWILIO_AUTH_TOKEN).toUtf8()
             << "--silent"
             << "--show-error";

    qDebug() << "Commande curl SMS:" << "curl" << curlArgs.join(" ");

    QProcess process;
    process.start("curl", curlArgs);
    process.waitForFinished(30000); // 30 secondes timeout

    if (process.exitCode() == 0) {
        QString output = process.readAllStandardOutput();
        qDebug() << "✅ Succès SMS - Réponse Twilio:" << output;

        QMessageBox::information(this, "✅ Succès SMS",
                                 "Message SMS envoyé avec succès !\n\n"
                                 "Destinataire: " + clientName + "\n"
                                                    "Téléphone: " + telephone);

        // Sauvegarder dans l'historique
        sauvegarderWhatsAppHistorique(telephone, "[SMS] " + message, clientName, true, output);
    } else {
        QString error = process.readAllStandardError();
        QString output = process.readAllStandardOutput();

        qDebug() << "❌ Erreur curl SMS - Code:" << process.exitCode();
        qDebug() << "Erreur:" << error;
        qDebug() << "Output:" << output;

        QString errorMsg = "❌ Échec de l'envoi SMS\n\n";

        if (error.contains("Could not resolve host")) {
            errorMsg += "Problème de connexion Internet";
        } else if (error.contains("SSL certificate problem")) {
            errorMsg += "Problème de certificat SSL";
        } else if (error.contains("401")) {
            errorMsg += "Erreur d'authentification Twilio\nVérifiez SID/Token";
        } else if (error.contains("400")) {
            errorMsg += "Requête incorrecte\nVérifiez le format du numéro";
        } else if (error.contains("21212")) {
            errorMsg += "Numéro non valide pour les SMS Twilio";
        } else {
            errorMsg += "Erreur: " + error;
        }

        QMessageBox::critical(this, "❌ Erreur SMS", errorMsg);

        // Sauvegarder l'échec dans l'historique
        sauvegarderWhatsAppHistorique(telephone, "[SMS] " + message, clientName, false, error);
    }
}

void MainWindow::onTwilioSent(QNetworkReply *reply)
{
    QString telephone = reply->property("telephone").toString();
    QString message = reply->property("message").toString();
    QString clientName = reply->property("clientName").toString();

    bool success = false;
    QString reponseApi;
    QString erreurDetaillee;

    // Récupérer le code HTTP
    int httpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    qDebug() << "=== RÉPONSE TWILIO ===";
    qDebug() << "Code HTTP:" << httpCode;
    qDebug() << "Erreur réseau:" << reply->errorString();
    qDebug() << "Code erreur:" << reply->error();
    qDebug() << "Redirection:" << redirectionTarget.toString();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        reponseApi = QString::fromUtf8(response);

        qDebug() << "Réponse Twilio:" << reponseApi;

        if (httpCode == 201 || httpCode == 200) {
            success = true;
            qDebug() << "✅ WhatsApp envoyé avec succès via Twilio";

            QMessageBox::information(this, "✅ Succès",
                                     "Message WhatsApp envoyé avec succès !\n\n"
                                     "Destinataire: " + clientName + "\n"
                                                        "Téléphone: " + telephone + "\n\n"
                                                       "Le client recevra la notification sur WhatsApp.");
        } else {
            qDebug() << "❌ Échec envoi WhatsApp - Code HTTP:" << httpCode;

            // Analyser la réponse d'erreur
            if (httpCode == 400) {
                erreurDetaillee = "❌ Bad Request (400) - Requête incorrecte\n\n"
                                  "Causes possibles:\n"
                                  "• Numéro de téléphone invalide\n"
                                  "• Message trop long\n"
                                  "• Format de numéro incorrect\n"
                                  "• Problème d'authentification\n\n"
                                  "Détails Twilio:\n" + reponseApi;
            } else if (httpCode == 401) {
                erreurDetaillee = "❌ Non autorisé (401)\n\n"
                                  "Vérifiez vos credentials Twilio:\n"
                                  "• Account SID: " + TWILIO_ACCOUNT_SID + "\n"
                                                         "• Auth Token: " + TWILIO_AUTH_TOKEN.mid(0, 8) + "...\n"
                                                                  "• Numéro Twilio: " + TWILIO_PHONE_NUMBER;
            } else if (httpCode == 404) {
                erreurDetaillee = "❌ Ressource non trouvée (404)\n\n"
                                  "URL Twilio incorrecte ou compte invalide";
            } else {
                erreurDetaillee = "❌ Erreur HTTP " + QString::number(httpCode) + "\n\n" + reponseApi;
            }

            QMessageBox::warning(this, "❌ Erreur Twilio", erreurDetaillee);
        }
    } else {
        QString erreurReseau = reply->errorString();
        int erreurCode = reply->error();

        qDebug() << "❌ Erreur réseau:" << erreurCode << "-" << erreurReseau;

        erreurDetaillee = "❌ Erreur réseau: " + erreurReseau +
                          "\nCode: " + QString::number(erreurCode) +
                          "\nHTTP: " + QString::number(httpCode);

        QMessageBox::critical(this, "❌ Erreur Réseau", erreurDetaillee);
    }

    // Sauvegarder dans l'historique
    sauvegarderWhatsAppHistorique(telephone, message, clientName, success,
                                  success ? reponseApi : (erreurDetaillee + "\n" + reponseApi));

    // Libérer la mémoire
    reply->deleteLater();
}

/*---------------------------------------------------------
 *   NOTIFIER CLIENT PAR WHATSAPP TWILIO
 ---------------------------------------------------------*/

void MainWindow::on_BTN_NOTIFIER_clicked()
{
    bool ok;
    QString idStr = QInputDialog::getText(this, "Notifier Client", "ID Réparation :", QLineEdit::Normal, "", &ok);
    if (!ok || idStr.isEmpty()) return;

    int idReparation = idStr.toInt(&ok);
    if (!ok || idReparation <= 0) {
        QMessageBox::warning(this, "Erreur", "ID invalide !");
        return;
    }

    QSqlQuery q;
    q.prepare(
        "SELECT R.STATUT_R, R.DATE_FIN_EST, R.DES_PANNE, R.COUT, "
        "A.TYPE, A.MARQUE, A.MODELE, "
        "C.NOM, C.PRENOM, C.TELEPHONE "
        "FROM SIRINE.REPARATIONS R "
        "JOIN SIRINE.APPAREILLES A ON R.NUM_SERIE = A.NUM_SERIE "
        "JOIN SIRINE.CLIENT C ON A.CIN_CLIENT = C.CIN_CLIENT "
        "WHERE R.IDR = ?"
        );
    q.addBindValue(idReparation);

    if (!q.exec()) {
        QMessageBox::critical(this, "Erreur SQL", q.lastError().text());
        return;
    }

    if (!q.next()) {
        QMessageBox::warning(this, "Introuvable", "Réparation non trouvée !");
        return;
    }

    QString statut = q.value(0).toString().trimmed().toUpper();
    QDate dateFin = q.value(1).toDate();
    QString marque = q.value(5).toString();
    QString modele = q.value(6).toString();
    QString prenom = q.value(8).toString();
    QString nom = q.value(7).toString();
    QString telephone = q.value(9).toString().trimmed();
    double cout = q.value(3).toDouble();

    if (telephone.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Numéro de téléphone manquant !");
        return;
    }

    QString clientName = prenom + " " + nom;
    QString message = "";

    if (statut == "TERMINEE") {
        message = QString("Bonjour %1,\n\nVotre %2 %3 est réparé ! Coût: %4 DT\nPrêt à être récupéré.\nFIXHUB")
                      .arg(prenom, marque, modele, QString::number(cout, 'f', 0));
    } else if (QDate::currentDate() > dateFin && statut != "TERMINEE") {
        message = QString("Bonjour %1,\n\nRetard sur votre %2 %3.\nNous vous recontactons bientôt.\nFIXHUB")
                      .arg(prenom, marque, modele);
    } else {
        message = QString("Bonjour %1,\n\nVotre %2 %3 est %3.\nFin prévue: %4\nFIXHUB")
                      .arg(prenom, marque, modele, dateFin.toString("dd/MM/yyyy"));
    }

    auto reponse = QMessageBox::question(this, "Envoyer Notification",
                                         "Envoyer à:\n" + clientName + "\n" + telephone + "\n\n" + message,
                                         QMessageBox::Yes | QMessageBox::No);

    if (reponse == QMessageBox::Yes) {
        envoyerWhatsAppTwilio(telephone, message, clientName);
        QTimer::singleShot(2000, [this, telephone, message, clientName]() {
            envoyerSMSTwilio(telephone, message.left(160), clientName);
        });
        QMessageBox::information(this, "Envoyé", "Notification envoyée !");
    }
}
//................arduino....................//
void MainWindow::setupArduino()
{
    arduinoManager = new SerialPortManager(this);

    connect(arduinoManager, &SerialPortManager::connected,
            this, &MainWindow::onArduinoConnected);
    connect(arduinoManager, &SerialPortManager::cardDetected,
            this, &MainWindow::onCardDetected);
    connect(arduinoManager, &SerialPortManager::doorOpened,
            this, &MainWindow::onDoorOpened);
    connect(arduinoManager, &SerialPortManager::doorClosed,
            this, &MainWindow::onDoorClosed);
    connect(arduinoManager, &SerialPortManager::error,
            this, &MainWindow::onArduinoError);

    // Essayer de se connecter automatiquement
    QTimer::singleShot(2000, this, [this]() {
        if (arduinoManager->connectToArduino()) {
            qDebug() << "Arduino connecté automatiquement";
        }
    });
}

void MainWindow::onArduinoConnected(bool connected)
{
    if (connected) {
        ui->statusbar->showMessage("✅ Arduino connecté", 5000);
        if (ui->labelArduinoStatus) {
            ui->labelArduinoStatus->setText("🟢 Arduino connecté");
            ui->labelArduinoStatus->setStyleSheet("color: green; font-weight: bold;");
        }
    } else {
        ui->statusbar->showMessage("🔴 Arduino déconnecté", 5000);
        if (ui->labelArduinoStatus) {
            ui->labelArduinoStatus->setText("🔴 Arduino déconnecté");
            ui->labelArduinoStatus->setStyleSheet("color: red;");
        }
    }
}

void MainWindow::onCardDetected(const QString &uid)
{
    qDebug() << "Carte détectée:" << uid;
    logAccess("Carte RFID détectée", uid);

    // Mettre à jour l'interface
    if (ui->labelLastUID) {
        ui->labelLastUID->setText("Dernière carte: " + uid);
    }

    // Vérifier l'accès
    checkEmployeeAccess(uid);
}

void MainWindow::checkEmployeeAccess(const QString &uid)
{
    bool ok;
    int uidDecimal = uid.toInt(&ok, 16);

    QSqlQuery query;
    bool accessGranted = false;  // ← Variable corrigée
    QString nom, prenom;

    if (ok) {
        query.prepare("SELECT NOM, PRENOM FROM SIRINE.EMPLOYER WHERE CIN_EMPLOYER = :cin");
        query.bindValue(":cin", uidDecimal);
    } else {
        query.prepare("SELECT NOM, PRENOM FROM SIRINE.EMPLOYER WHERE UID_CARTE = :uid");
        query.bindValue(":uid", uid);
    }

    if (query.exec() && query.next()) {
        nom = query.value(0).toString();
        prenom = query.value(1).toString();
        accessGranted = true;  // ← Accès autorisé
    }

    if (accessGranted) {
        // Ouvre la porte via le bon Arduino
        if (arduinoRFID && arduinoRFID->isConnected()) {
            arduinoRFID->sendCommand("<O>");
        }

        QMessageBox::information(this, "Accès autorisé",
                                 QString("Bonjour %1 %2 !\nPorte ouverte").arg(prenom, nom));

        logAccess("Accès autorisé: " + prenom + " " + nom, uid);
    } else {
        QMessageBox::warning(this, "Accès refusé", "Badge inconnu !");
        logAccess("Accès refusé", uid);
    }
}
void MainWindow::onDoorOpened()
{
    logAccess("Porte ouverte");
    ui->statusbar->showMessage("🚪 Porte ouverte", 3000);
}

void MainWindow::onDoorClosed()
{
    logAccess("Porte fermée");
    ui->statusbar->showMessage("🚪 Porte fermée", 3000);
}

void MainWindow::onArduinoError(const QString &error)
{
    ui->statusbar->showMessage("❌ Erreur Arduino: " + error, 5000);
    qDebug() << "Erreur Arduino:" << error;
}

void MainWindow::on_btnConnectArduino_clicked()
{
    if (arduinoManager->isConnected()) {
        arduinoManager->disconnectArduino();
        ui->btnConnectArduino->setText("🔌 Connecter Arduino");
    } else {
        if (arduinoManager->connectToArduino()) {
            ui->btnConnectArduino->setText("🔓 Déconnecter Arduino");
        }
    }
}

void MainWindow::on_btnOpenDoor_clicked()
{
    if (arduinoManager->isConnected()) {
        arduinoManager->sendCommand("<O>");
        logAccess("Porte ouverte manuellement");
    }
}

void MainWindow::on_btnCloseDoor_clicked()
{
    if (arduinoManager->isConnected()) {
        arduinoManager->sendCommand("<C>");
        logAccess("Porte fermée manuellement");
    }
}

void MainWindow::logAccess(const QString &message, const QString &uid)
{
    QString timestamp = QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss");
    QString logEntry = QString("[%1] %2").arg(timestamp, message);

    if (!uid.isEmpty()) {
        logEntry += QString(" (UID: %1)").arg(uid);
    }

    // Ajouter au journal si vous avez un QTextEdit
    if (ui->textEditRFIDLogs) {
        ui->textEditRFIDLogs->append(logEntry);
    }

    qDebug() << logEntry;
}
//arduino sirine//
void MainWindow::onReparationRequested(const QString &idRepStr)
{
    bool ok;
    int idRep = idRepStr.toInt(&ok);
    if (!ok || idRep <= 0) {
        sendReparationInfoToArduino("Invalide", "ID incorrect", "Erreur");
        return;
    }

    QSqlQuery query;
    query.prepare(
        "SELECT r.STATUT_R, r.MAT_REP, c.NOM || ' ' || SUBSTR(c.PRENOM, 1, 1) || '.' AS CLIENT_NOM "
        "FROM SIRINE.REPARATIONS r "
        "JOIN SIRINE.APPAREILLES a ON r.NUM_SERIE = a.NUM_SERIE "
        "JOIN SIRINE.CLIENT c ON a.CIN_CLIENT = c.CIN_CLIENT "
        "WHERE r.IDR = :id"
        );
    query.bindValue(":id", idRep);

    QString statut = "Non trouvée";
    QString materiel = "Inconnu";
    QString client = "Inconnu";

    if (query.exec() && query.next()) {
        statut = query.value(0).toString().trimmed();
        materiel = query.value(1).toString().trimmed();
        client = query.value(2).toString().trimmed();

        // Normalisation du statut
        if (statut.contains("Termin", Qt::CaseInsensitive)) statut = "Terminée";
        else if (statut.contains("cours", Qt::CaseInsensitive)) statut = "En cours";
        else if (statut.contains("attente", Qt::CaseInsensitive)) statut = "En attente";
    }

    sendReparationInfoToArduino(statut, client, materiel);
}

void MainWindow::sendReparationInfoToArduino(const QString &statut, const QString &client, const QString &materiel)
{
    if (arduinoLCD && arduinoLCD->isConnected()) {
        QString msg = QString("<S:%1|C:%2|M:%3>")
        .arg(statut.left(12), client.left(20), materiel.left(20));
        arduinoLCD->sendCommand(msg);
    }
}
void MainWindow::setupArduinos()
{
    // Détection automatique des deux Arduino
    QString portLCD = "";
    QString portRFID = "";

    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
        QString name = info.portName();
        QString desc = info.description();
        qDebug() << "Port trouvé:" << name << desc;

        if (desc.contains("Arduino", Qt::CaseInsensitive) || name.contains("ACM") || name.contains("USB")) {
            if (portLCD.isEmpty()) {
                portLCD = name;
            } else if (portRFID.isEmpty()) {
                portRFID = name;
            }
        }
    }

    // Création des deux appareils
    if (!portLCD.isEmpty()) {
        arduinoLCD = new ArduinoDevice(portLCD, this);
        arduinoLCD->connect();

        connect(arduinoLCD, &ArduinoDevice::reparationRequested,
                this, &MainWindow::onReparationRequested);
        connect(arduinoLCD, &ArduinoDevice::connected, this, [=](bool c){
            ui->statusbar->showMessage(c ? "LCD Arduino connecté" : "LCD déconnecté", 3000);
        });
    }

    if (!portRFID.isEmpty() && portRFID != portLCD) {
        arduinoRFID = new ArduinoDevice(portRFID, this);
        arduinoRFID->connect();

        connect(arduinoRFID, &ArduinoDevice::uidReceived,
                this, &MainWindow::onCardDetected);
        connect(arduinoRFID, &ArduinoDevice::connected, this, [=](bool c){
            ui->statusbar->showMessage(c ? "RFID Arduino connecté" : "RFID déconnecté", 3000);
        });
    }
}

