#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupDatabase();
    chargerDonnees();

    // Connecter les signaux pour la validation en temps réel
    connect(ui->lineEditId, &QLineEdit::textChanged, this, &MainWindow::validerCIN);
    connect(ui->lineEditMarque_3, &QLineEdit::textChanged, this, &MainWindow::validerNom);
    connect(ui->lineEditMarque, &QLineEdit::textChanged, this, &MainWindow::validerPrenom);
    connect(ui->lineEditModele, &QLineEdit::textChanged, this, &MainWindow::validerTelephone);
    connect(ui->lineEditNumeroSerie, &QLineEdit::textChanged, this, &MainWindow::validerEmail);
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

void MainWindow::setupDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("employes.db");

    if (!db.open()) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir la base de données: " + db.lastError().text());
        return;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS employes ("
               "cin TEXT PRIMARY KEY, "
               "nom TEXT NOT NULL, "
               "prenom TEXT NOT NULL, "
               "num_tel TEXT NOT NULL, "
               "email TEXT NOT NULL)");

    model = new QSqlTableModel(this, db);
    model->setTable("employes");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->setHeaderData(0, Qt::Horizontal, "CIN");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prénom");
    model->setHeaderData(3, Qt::Horizontal, "Num Tel");
    model->setHeaderData(4, Qt::Horizontal, "Email");

    model->select();

    ui->tableViewAppareils->setModel(model);
    ui->tableViewAppareils->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewAppareils->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->lineEditId->setEnabled(true);
}

void MainWindow::chargerDonnees()
{
    model->select();
    ui->tableViewAppareils->resizeColumnsToContents();
}

void MainWindow::viderChamps()
{
    ui->lineEditId->clear();
    ui->lineEditMarque_3->clear();
    ui->lineEditMarque->clear();
    ui->lineEditModele->clear();
    ui->lineEditNumeroSerie->clear();

    ui->lineEditId->setReadOnly(false);

    // Réinitialiser les styles
    ui->lineEditId->setStyleSheet("");
    ui->lineEditMarque_3->setStyleSheet("");
    ui->lineEditMarque->setStyleSheet("");
    ui->lineEditModele->setStyleSheet("");
    ui->lineEditNumeroSerie->setStyleSheet("");
}

// Validation en temps réel pour le CIN
void MainWindow::validerCIN()
{
    QString cin = ui->lineEditId->text();
    QRegularExpression regex("^[0-9]{8}$");

    if (cin.isEmpty()) {
        ui->lineEditId->setStyleSheet("");
        QToolTip::hideText();
    } else if (!regex.match(cin).hasMatch()) {
        ui->lineEditId->setStyleSheet("border: 2px solid red;");
        QToolTip::showText(ui->lineEditId->mapToGlobal(QPoint(0, -50)),
                           "❌ CIN invalide: 8 chiffres requis (ex: 12345678)",
                           ui->lineEditId);
    } else {
        ui->lineEditId->setStyleSheet("border: 2px solid green;");
        QToolTip::hideText();
    }
}

// Validation en temps réel pour le Nom
void MainWindow::validerNom()
{
    QString nom = ui->lineEditMarque_3->text();
    QRegularExpression regex("^[a-zA-ZÀ-ÿ\\s]+$");

    if (nom.isEmpty()) {
        ui->lineEditMarque_3->setStyleSheet("");
        QToolTip::hideText();
    } else if (!regex.match(nom).hasMatch()) {
        ui->lineEditMarque_3->setStyleSheet("border: 2px solid red;");
        QToolTip::showText(ui->lineEditMarque_3->mapToGlobal(QPoint(0, -50)),
                           "❌ Nom invalide: lettres uniquement",
                           ui->lineEditMarque_3);
    } else {
        ui->lineEditMarque_3->setStyleSheet("border: 2px solid green;");
        QToolTip::hideText();
    }
}

// Validation en temps réel pour le Prénom
void MainWindow::validerPrenom()
{
    QString prenom = ui->lineEditMarque->text();
    QRegularExpression regex("^[a-zA-ZÀ-ÿ\\s]+$");

    if (prenom.isEmpty()) {
        ui->lineEditMarque->setStyleSheet("");
        QToolTip::hideText();
    } else if (!regex.match(prenom).hasMatch()) {
        ui->lineEditMarque->setStyleSheet("border: 2px solid red;");
        QToolTip::showText(ui->lineEditMarque->mapToGlobal(QPoint(0, -50)),
                           "❌ Prénom invalide: lettres uniquement",
                           ui->lineEditMarque);
    } else {
        ui->lineEditMarque->setStyleSheet("border: 2px solid green;");
        QToolTip::hideText();
    }
}

// Validation en temps réel pour le Téléphone
void MainWindow::validerTelephone()
{
    QString tel = ui->lineEditModele->text();
    QRegularExpression regex("^[0-9]{8}$");

    if (tel.isEmpty()) {
        ui->lineEditModele->setStyleSheet("");
        QToolTip::hideText();
    } else if (!regex.match(tel).hasMatch()) {
        ui->lineEditModele->setStyleSheet("border: 2px solid red;");
        QToolTip::showText(ui->lineEditModele->mapToGlobal(QPoint(0, -50)),
                           "❌ Téléphone invalide: 8 chiffres requis (ex: 98765432)",
                           ui->lineEditModele);
    } else {
        ui->lineEditModele->setStyleSheet("border: 2px solid green;");
        QToolTip::hideText();
    }
}

// Validation en temps réel pour l'Email
void MainWindow::validerEmail()
{
    QString email = ui->lineEditNumeroSerie->text();
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");

    if (email.isEmpty()) {
        ui->lineEditNumeroSerie->setStyleSheet("");
        QToolTip::hideText();
    } else if (!email.contains("@")) {
        ui->lineEditNumeroSerie->setStyleSheet("border: 2px solid red;");
        QToolTip::showText(ui->lineEditNumeroSerie->mapToGlobal(QPoint(0, -50)),
                           "❌ Email invalide: @ requis",
                           ui->lineEditNumeroSerie);
    } else if (!regex.match(email).hasMatch()) {
        ui->lineEditNumeroSerie->setStyleSheet("border: 2px solid red;");
        QToolTip::showText(ui->lineEditNumeroSerie->mapToGlobal(QPoint(0, -50)),
                           "❌ Format email invalide (ex: nom@domaine.com)",
                           ui->lineEditNumeroSerie);
    } else {
        ui->lineEditNumeroSerie->setStyleSheet("border: 2px solid green;");
        QToolTip::hideText();
    }
}

bool MainWindow::validerDonnees(QString cin, QString nom, QString prenom, QString numTel, QString email)
{
    if (cin.isEmpty() || nom.isEmpty() || prenom.isEmpty() || numTel.isEmpty() || email.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Veuillez remplir tous les champs!");
        return false;
    }

    // Validation CIN : uniquement des chiffres (8 chiffres)
    QRegularExpression regexCin("^[0-9]{8}$");
    if (!regexCin.match(cin).hasMatch()) {
        QMessageBox::warning(this, "Erreur CIN",
                             "❌ Le CIN doit contenir exactement 8 chiffres!\n"
                             "Exemple: 12345678");
        return false;
    }

    // Validation Nom : uniquement des lettres
    QRegularExpression regexNom("^[a-zA-ZÀ-ÿ\\s]+$");
    if (!regexNom.match(nom).hasMatch()) {
        QMessageBox::warning(this, "Erreur Nom",
                             "❌ Le nom ne doit contenir que des lettres!\n"
                             "Les chiffres et caractères spéciaux ne sont pas autorisés.");
        return false;
    }

    // Validation Prénom : uniquement des lettres
    if (!regexNom.match(prenom).hasMatch()) {
        QMessageBox::warning(this, "Erreur Prénom",
                             "❌ Le prénom ne doit contenir que des lettres!\n"
                             "Les chiffres et caractères spéciaux ne sont pas autorisés.");
        return false;
    }

    // Validation Téléphone : uniquement des chiffres (8 chiffres)
    QRegularExpression regexTel("^[0-9]{8}$");
    if (!regexTel.match(numTel).hasMatch()) {
        QMessageBox::warning(this, "Erreur Téléphone",
                             "❌ Le numéro de téléphone doit contenir exactement 8 chiffres!\n"
                             "Exemple: 98765432");
        return false;
    }

    // Validation Email : format complet
    QRegularExpression regexEmail("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    if (!regexEmail.match(email).hasMatch()) {
        QMessageBox::warning(this, "Erreur Email",
                             "❌ Format d'email invalide!\n"
                             "Exemple: nom@domaine.com");
        return false;
    }

    return true;
}

void MainWindow::on_btnAjouter_clicked()
{
    QString cin = ui->lineEditId->text();
    QString nom = ui->lineEditMarque_3->text();
    QString prenom = ui->lineEditMarque->text();
    QString numTel = ui->lineEditModele->text();
    QString email = ui->lineEditNumeroSerie->text();

    if (!validerDonnees(cin, nom, prenom, numTel, email)) {
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO employes (cin, nom, prenom, num_tel, email) "
                  "VALUES (:cin, :nom, :prenom, :numTel, :email)");
    query.bindValue(":cin", cin);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":numTel", numTel);
    query.bindValue(":email", email);

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "✅ Employé ajouté avec succès!");
        chargerDonnees();
        viderChamps();
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur: " + query.lastError().text());
    }
}

void MainWindow::on_btnModifier_clicked()
{
    QString cin = ui->lineEditId->text();

    if (cin.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un employé à modifier!");
        return;
    }

    QString nom = ui->lineEditMarque_3->text();
    QString prenom = ui->lineEditMarque->text();
    QString numTel = ui->lineEditModele->text();
    QString email = ui->lineEditNumeroSerie->text();

    if (!validerDonnees(cin, nom, prenom, numTel, email)) {
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE employes SET nom=:nom, prenom=:prenom, "
                  "num_tel=:numTel, email=:email WHERE cin=:cin");
    query.bindValue(":cin", cin);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":numTel", numTel);
    query.bindValue(":email", email);

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "✅ Employé modifié avec succès!");
        chargerDonnees();
        viderChamps();
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur: " + query.lastError().text());
    }
}

void MainWindow::on_btnSupprimer_clicked()
{
    QString cin = ui->lineEditId->text();

    if (cin.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un employé à supprimer!");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer cet employé?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("DELETE FROM employes WHERE cin=:cin");
        query.bindValue(":cin", cin);

        if (query.exec()) {
            QMessageBox::information(this, "Succès", "✅ Employé supprimé avec succès!");
            chargerDonnees();
            viderChamps();
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur: " + query.lastError().text());
        }
    }
}

void MainWindow::on_btnRafraichir_clicked()
{
    chargerDonnees();
    viderChamps();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int row = index.row();

    ui->lineEditId->setText(model->data(model->index(row, 0)).toString());
    ui->lineEditMarque_3->setText(model->data(model->index(row, 1)).toString());
    ui->lineEditMarque->setText(model->data(model->index(row, 2)).toString());
    ui->lineEditModele->setText(model->data(model->index(row, 3)).toString());
    ui->lineEditNumeroSerie->setText(model->data(model->index(row, 4)).toString());

    ui->lineEditId->setReadOnly(true);
}

void MainWindow::on_tableViewAppareils_clicked(const QModelIndex &index)
{
    int row = index.row();

    ui->lineEditId->setText(model->data(model->index(row, 0)).toString());
    ui->lineEditMarque_3->setText(model->data(model->index(row, 1)).toString());
    ui->lineEditMarque->setText(model->data(model->index(row, 2)).toString());
    ui->lineEditModele->setText(model->data(model->index(row, 3)).toString());
    ui->lineEditNumeroSerie->setText(model->data(model->index(row, 4)).toString());

    ui->lineEditId->setReadOnly(true);
}
