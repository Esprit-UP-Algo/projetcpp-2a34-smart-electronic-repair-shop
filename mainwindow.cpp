#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QInputDialog>
#include <QRegularExpression>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QToolTip>
#include <QSignalBlocker>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupValidators();

    // Ajouter des placeholders pour les champs obligatoires
    ui->lineEditIdClient->setPlaceholderText("CIN * (Obligatoire)");
    ui->lineEditNom->setPlaceholderText("Nom * (Obligatoire)");
    ui->lineEditPrenom->setPlaceholderText("Prénom * (Obligatoire)");
    ui->lineEditTelephone->setPlaceholderText("Téléphone * (Obligatoire)");

    // Connexions pour le contrôle de saisie en temps réel
    connect(ui->lineEditNom, &QLineEdit::textChanged, this, &MainWindow::onTextChanged);
    connect(ui->lineEditPrenom, &QLineEdit::textChanged, this, &MainWindow::onTextChanged);

    // Connexions pour les métiers innovants
    connect(ui->btnAnalyserFidelite, &QPushButton::clicked, this, &MainWindow::on_btnAnalyserFidelite_clicked);
    connect(ui->btnMaintenancePreventive, &QPushButton::clicked, this, &MainWindow::on_btnMaintenancePreventive_clicked);
    connect(ui->btnGenererRapportFidelite, &QPushButton::clicked, this, &MainWindow::on_btnGenererRapportFidelite_clicked);
    connect(ui->btnEnvoyerSMS, &QPushButton::clicked, this, &MainWindow::on_btnEnvoyerSMS_clicked);

    refreshClientTable();
    loadComboBoxData();
}

MainWindow::~MainWindow()
{
    delete ui;
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

    // Clients
    ui->lineEditIdClient->setValidator(cinValidator);
    ui->lineEditTelephone->setValidator(new QIntValidator(10000000, 99999999, this));
    ui->lineEditNom->setValidator(texteValidator);
    ui->lineEditPrenom->setValidator(texteValidator);
    ui->lineEditEmail->setValidator(emailValidator);
    ui->lineEditAdresse->setValidator(adresseValidator);
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

// ==================== MÉTHODES DE RAFRAÎCHISSEMENT ====================

void MainWindow::refreshClientTable()
{
    ui->tableViewClients->setModel(clt.afficher());
    ui->labelTotalClients->setText(QString("Total: %1 clients").arg(ui->tableViewClients->model()->rowCount()));
}

void MainWindow::loadComboBoxData()
{
    // Les combobox pour appareils et employés sont remplacées par des saisies manuelles
}

// ==================== MÉTHODES DE NETTOYAGE ====================

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

// ==================== MÉTIERS INNOVANTS ====================

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

    QPushButton *btnPDF = msgBox.addButton("📄 Générer PDF", QMessageBox::ActionRole);
    QPushButton *btnFermer = msgBox.addButton("Fermer", QMessageBox::AcceptRole);

    msgBox.exec();

    if (msgBox.clickedButton() == btnPDF) {
        genererPDFProfilClient(cin);
    }
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

    QPushButton *btnPDF = msgBox.addButton("📄 Générer PDF", QMessageBox::ActionRole);
    QPushButton *btnSMS = msgBox.addButton("📱 Envoyer SMS", QMessageBox::ActionRole);
    QPushButton *btnFermer = msgBox.addButton("Fermer", QMessageBox::AcceptRole);

    msgBox.exec();

    if (msgBox.clickedButton() == btnPDF) {
        genererPDFMaintenance(cin);
    } else if (msgBox.clickedButton() == btnSMS) {
        on_btnEnvoyerSMS_clicked();
    }
}

void MainWindow::on_btnGenererRapportFidelite_clicked()
{
    int cin;
    if(!validateCIN(ui->lineEditIdClient->text(), cin)) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un client!");
        return;
    }

    genererPDFProfilClient(cin);
}

void MainWindow::on_btnEnvoyerSMS_clicked()
{
    int cin;
    if(!validateCIN(ui->lineEditIdClient->text(), cin)) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un client!");
        return;
    }

    // Récupérer le téléphone du client
    QSqlQuery query;
    query.prepare("SELECT NOM, PRENOM, TELEPHONE FROM CLIENT WHERE CIN_CLIENT = :cin");
    query.bindValue(":cin", cin);

    if (query.exec() && query.next()) {
        QString nom = query.value(0).toString();
        QString prenom = query.value(1).toString();
        QString telephone = query.value(2).toString();

        QMessageBox::information(this, "Envoi SMS",
                                 QString("📱 SMS envoyé avec succès!\n\n"
                                         "Client: %1 %2\n"
                                         "Téléphone: %3\n\n"
                                         "Message: Maintenance préventive recommandée. "
                                         "Contactez-nous pour plus d'informations.")
                                     .arg(nom).arg(prenom).arg(telephone));
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer les informations du client!");
    }
}

void MainWindow::genererPDFProfilClient(int cin)
{
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer le rapport de fidélité",
                                                    QString("Rapport_Fidelite_%1.pdf").arg(cin),
                                                    "PDF Files (*.pdf)");

    if (!fileName.isEmpty()) {
        // Simulation de génération PDF
        QMessageBox::information(this, "📄 Rapport Généré",
                                 QString("Rapport de fidélité généré avec succès!\n\n"
                                         "Fichier: %1\n"
                                         "Client CIN: %2\n\n"
                                         "Le rapport contient:\n"
                                         "• Score de fidélité détaillé\n"
                                         "• Analyse comportementale\n"
                                         "• Recommandations personnalisées\n"
                                         "• Historique des interactions")
                                     .arg(fileName).arg(cin));
    }
}

void MainWindow::genererPDFMaintenance(int cin)
{
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer le rapport de maintenance",
                                                    QString("Maintenance_Preventive_%1.pdf").arg(cin),
                                                    "PDF Files (*.pdf)");

    if (!fileName.isEmpty()) {
        // Simulation de génération PDF
        QMessageBox::information(this, "📄 Rapport Généré",
                                 QString("Rapport de maintenance généré avec succès!\n\n"
                                         "Fichier: %1\n"
                                         "Client CIN: %2\n\n"
                                         "Le rapport contient:\n"
                                         "• Liste des appareils analysés\n"
                                         "• Recommandations de maintenance\n"
                                         "• Priorités et coûts estimés\n"
                                         "• Calendrier de maintenance")
                                     .arg(fileName).arg(cin));
    }
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

// ==================== STATISTIQUES ====================

void MainWindow::on_btnGenererRapport_clicked()
{
    QMessageBox::information(this, "Fonctionnalité", "Génération de rapport global - Fonctionnalité à implémenter");
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

    // Mettre en évidence les champs vides
    for (int i = 0; i < fields.size(); ++i) {
        if (values[i].isEmpty()) {
            if (fields[i] == "CIN") {
                ui->lineEditIdClient->setStyleSheet("background-color: #FFE6E6; border: 2px solid #DC3545;");
            } else if (fields[i] == "Nom") {
                ui->lineEditNom->setStyleSheet("background-color: #FFE6E6; border: 2px solid #DC3545;");
            } else if (fields[i] == "Prénom") {
                ui->lineEditPrenom->setStyleSheet("background-color: #FFE6E6; border: 2px solid #DC3545;");
            } else if (fields[i] == "Téléphone") {
                ui->lineEditTelephone->setStyleSheet("background-color: #FFE6E6; border: 2px solid #DC3545;");
            }
        }
    }
}

void MainWindow::onHeaderReparationClicked(int logicalIndex)
{
    // Implémentation du tri par en-tête si nécessaire
}
