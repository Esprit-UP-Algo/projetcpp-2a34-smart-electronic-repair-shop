#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QInputDialog>
#include <QRegularExpression>
#include <QIntValidator>
#include <QDoubleValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupValidators();

    refreshEmployeTable();
    refreshClientTable();
    refreshAppareilTable();
    refreshReparationTable();
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

    // Employés
    ui->lineEditId->setValidator(cinValidator);
    ui->lineEditModele_2->setValidator(new QIntValidator(10000000, 99999999, this));

    // Clients
    ui->lineEditIdClient->setValidator(cinValidator);
    ui->lineEditTelephone->setValidator(new QIntValidator(10000000, 99999999, this));

    // Appareils
    ui->lineEditNumeroSerie->setValidator(numSerieValidator);

    // Réparations
    ui->lineEditCout->setValidator(coutValidator);
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
    // CORRECTION : Utiliser toDouble directement
    bool ok;
    QString cleanedStr = coutStr;
    cout = cleanedStr.toDouble(&ok);
    return ok && cout >= 0;
}

bool MainWindow::validateMatApp(const QString& matStr, int& matApp)
{
    bool ok;
    matApp = matStr.toInt(&ok);
    return ok && matApp > 0;
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
    ui->comboBoxAppareilReparation->setModel(rep.getAppareilsDisponibles());
    ui->comboBoxAppareilReparation->setModelColumn(0);
}

// ==================== MÉTHODES DE NETTOYAGE ====================

void MainWindow::clearEmployeFields()
{
    ui->lineEditId->clear();
    ui->lineEditMarque_3->clear();
    ui->lineEditMarque_2->clear();
    ui->lineEditModele_2->clear();
    ui->lineEditNumeroSerie_2->clear();
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
    ui->lineEditId->clear(); // Utiliser lineEditId pour les réparations aussi
    ui->comboBoxAppareilReparation->setCurrentIndex(0);
    ui->textEditPanne->clear();
    ui->lineEditCout->clear();
    ui->dateEditDepot->setDate(QDate::currentDate());
    ui->dateEditRetourPrevue->setDate(QDate::currentDate());
    ui->comboBoxStatutReparation->setCurrentIndex(0);
}

// ==================== GESTION DES EMPLOYÉS ====================

void MainWindow::on_btnAjouter_clicked()
{
    int cin;
    if(!validateCIN(ui->lineEditId->text(), cin)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le CIN doit être un nombre positif entre 1 et 99,999,999!");
        return;
    }

    QString nom = ui->lineEditMarque_3->text();
    QString prenom = ui->lineEditMarque_2->text();
    QString telephone = ui->lineEditModele_2->text();
    QString email = ui->lineEditNumeroSerie_2->text();

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
    clearEmployeFields();
    refreshEmployeTable();
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

// ==================== GESTION DES CLIENTS ====================

void MainWindow::on_btnAjouterClient_clicked()
{
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

    // Validation des champs obligatoires
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
    ui->lineEditRechercheClient->clear();
    refreshClientTable();
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
    // Validation du numéro de série
    int numSerie;
    if(!validateNumSerie(ui->lineEditNumeroSerie->text(), numSerie)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le numéro de série doit être un nombre positif!");
        return;
    }

    QString type = ui->comboBoxType->currentText();
    QString marque = ui->lineEditMarque->text();
    QString modele = ui->lineEditModele->text();
    QDate dateAchat = ui->dateEditAchat->date();

    // Validation des champs obligatoires
    if(marque.isEmpty()) {
        QMessageBox::warning(this, "Champ requis", "La marque est obligatoire!");
        return;
    }

    if(modele.isEmpty()) {
        QMessageBox::warning(this, "Champ requis", "Le modèle est obligatoire!");
        return;
    }

    // DEMANDER LE CIN DU CLIENT
    bool ok;
    int cinClient = QInputDialog::getInt(this, "Sélection du client",
                                         "Veuillez saisir le CIN du client propriétaire:",
                                         0, 1, 99999999, 1, &ok);

    if (!ok) {
        return;
    }

    // Vérifier que le client existe
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

    // Validation des champs obligatoires
    if(marque.isEmpty()) {
        QMessageBox::warning(this, "Champ requis", "La marque est obligatoire!");
        return;
    }

    if(modele.isEmpty()) {
        QMessageBox::warning(this, "Champ requis", "Le modèle est obligatoire!");
        return;
    }

    // DEMANDER LE CIN DU CLIENT
    bool ok;
    int cinClient = QInputDialog::getInt(this, "Sélection du client",
                                         "Veuillez saisir le CIN du client propriétaire:",
                                         0, 1, 99999999, 1, &ok);

    if (!ok) {
        return;
    }

    // Vérifier que le client existe
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

void MainWindow::on_btnRechercherAppareil_clicked()
{
    QString valeur = ui->lineEditNumeroSerie->text();

    if(valeur.isEmpty()) {
        QMessageBox::warning(this, "Champ requis", "Veuillez saisir un numéro de série!");
        return;
    }

    ui->tableViewAppareils->setModel(app.rechercher(valeur));
}

void MainWindow::on_btnReinitialiserAppareil_clicked()
{
    clearAppareilFields();
    refreshAppareilTable();
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

// ==================== GESTION DES RÉPARATIONS ====================

void MainWindow::on_btnAjouterReparation_clicked()
{
    int matApp;
    if(!validateMatApp(ui->lineEditId->text(), matApp)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le matricule doit être un nombre positif!");
        return;
    }

    if(ui->comboBoxAppareilReparation->currentText().isEmpty()) {
        QMessageBox::warning(this, "Champ requis", "Veuillez sélectionner un appareil!");
        return;
    }

    int numSerie = ui->comboBoxAppareilReparation->currentText().toInt();
    QString descriptionPanne = ui->textEditPanne->toPlainText();
    QDate dateDepot = ui->dateEditDepot->date();
    QDate dateRetourPrevue = ui->dateEditRetourPrevue->date();
    QString statut = ui->comboBoxStatutReparation->currentText();

    double cout;
    if(!validateCout(ui->lineEditCout->text(), cout)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le coût doit être un nombre positif!");
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

    bool ok;
    int cinEmploye = QInputDialog::getInt(this, "Sélection de l'employé",
                                          "Veuillez saisir le CIN de l'employé responsable:",
                                          0, 1, 99999999, 1, &ok);

    if (!ok) {
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYER WHERE CIN_EMPLOYER = :cinEmploye");
    query.bindValue(":cinEmploye", cinEmploye);
    query.exec();
    query.next();
    int count = query.value(0).toInt();

    if(count == 0) {
        QMessageBox::warning(this, "Employé introuvable",
                             "L'employé avec CIN " + QString::number(cinEmploye) + " n'existe pas!");
        return;
    }

    Reparations r(matApp, descriptionPanne, dateDepot, dateRetourPrevue, statut, cout, cinEmploye, numSerie);
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
    int matApp;
    if(!validateMatApp(ui->lineEditId->text(), matApp)) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez sélectionner une réparation à modifier!");
        return;
    }

    if(ui->comboBoxAppareilReparation->currentText().isEmpty()) {
        QMessageBox::warning(this, "Champ requis", "Veuillez sélectionner un appareil!");
        return;
    }

    int numSerie = ui->comboBoxAppareilReparation->currentText().toInt();
    QString descriptionPanne = ui->textEditPanne->toPlainText();
    QDate dateDepot = ui->dateEditDepot->date();
    QDate dateRetourPrevue = ui->dateEditRetourPrevue->date();
    QString statut = ui->comboBoxStatutReparation->currentText();

    double cout;
    if(!validateCout(ui->lineEditCout->text(), cout)) {
        QMessageBox::warning(this, "Erreur de saisie", "Le coût doit être un nombre positif!");
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

    bool ok;
    int cinEmploye = QInputDialog::getInt(this, "Sélection de l'employé",
                                          "Veuillez saisir le CIN de l'employé responsable:",
                                          0, 1, 99999999, 1, &ok);

    if (!ok) {
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYER WHERE CIN_EMPLOYER = :cinEmploye");
    query.bindValue(":cinEmploye", cinEmploye);
    query.exec();
    query.next();
    int count = query.value(0).toInt();

    if(count == 0) {
        QMessageBox::warning(this, "Employé introuvable",
                             "L'employé avec CIN " + QString::number(cinEmploye) + " n'existe pas!");
        return;
    }

    Reparations r(matApp, descriptionPanne, dateDepot, dateRetourPrevue, statut, cout, cinEmploye, numSerie);
    bool test = r.modifier(matApp);

    if(test) {
        QMessageBox::information(this, "Succès", "Réparation modifiée avec succès!");
        refreshReparationTable();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification de la réparation!");
    }
}

void MainWindow::on_btnSupprimerReparation_clicked()
{
    int matApp;
    if(!validateMatApp(ui->lineEditId->text(), matApp)) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez sélectionner une réparation à supprimer!");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer cette réparation?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        bool test = rep.supprimer(matApp);

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
    ui->lineEditRechercheReparation->clear();
    refreshReparationTable();
}

void MainWindow::on_tableViewReparationsListe_clicked(const QModelIndex &index)
{
    int row = index.row();

    ui->lineEditId->setText(ui->tableViewReparationsListe->model()->index(row, 0).data().toString());
    ui->comboBoxAppareilReparation->setCurrentText(ui->tableViewReparationsListe->model()->index(row, 7).data().toString());
    ui->textEditPanne->setText(ui->tableViewReparationsListe->model()->index(row, 1).data().toString());
    ui->dateEditDepot->setDate(ui->tableViewReparationsListe->model()->index(row, 2).data().toDate());
    ui->dateEditRetourPrevue->setDate(ui->tableViewReparationsListe->model()->index(row, 3).data().toDate());
    ui->comboBoxStatutReparation->setCurrentText(ui->tableViewReparationsListe->model()->index(row, 4).data().toString());
    ui->lineEditCout->setText(ui->tableViewReparationsListe->model()->index(row, 5).data().toString());
}

// ==================== STATISTIQUES ====================

void MainWindow::on_btnGenererRapport_clicked()
{
    QMessageBox::information(this, "Fonctionnalité", "Génération de rapport - Fonctionnalité à implémenter");
}
