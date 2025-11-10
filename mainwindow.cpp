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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupValidators();

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
    // Tri par numéro série comme indiqué dans l'interface "trier par numero serie"
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT NUM_SERIE, TYPE, MARQUE, MODELE, DATE_ACQ, ETAT, CIN_CLIENT FROM APPAREILLES ORDER BY NUM_SERIE");

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

// ==================== STATISTIQUES ====================

void MainWindow::on_btnGenererRapport_clicked()
{
    QMessageBox::information(this, "Fonctionnalité", "Génération de rapport - Fonctionnalité à implémenter");
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
