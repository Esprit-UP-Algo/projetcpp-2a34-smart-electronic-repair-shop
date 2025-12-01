#include "mainwindow.h"
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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupValidators();
    setupAdvancedFeatures();


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

