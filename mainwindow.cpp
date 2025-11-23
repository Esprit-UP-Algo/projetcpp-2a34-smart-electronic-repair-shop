#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qrcode.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include "employe.h"
#include <QTextDocument>
#include <QTextStream>
#include <QFileDialog>
#include <QDir>
#include <QtPrintSupport/QPrinter>
#include <QSqlError>
#include <QDebug>
#include <QLineEdit>
#include <QInputDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QDateTime>

#include "mailingservice.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_mailingService(nullptr)
    , m_lastPdfPath("")
{
    ui->setupUi(this);
    ui->tableViewAppareils_4->setModel(emp.afficher());
    setupValidators();
    setupRechercheField();

    m_mailingService = new MailingService(this);
    setupMailingService();

    connect(ui->btnAjouter_5, &QPushButton::clicked, this, &MainWindow::on_btnAjouter_5_clicked);
    connect(ui->btnAjouter_6, &QPushButton::clicked, this, &MainWindow::on_btnAjouter_6_clicked);
    connect(ui->btnSendRealEmail, &QPushButton::clicked, this, &MainWindow::on_btnSendRealEmail_clicked);
    connect(ui->btnSendPdfEmail, &QPushButton::clicked, this, &MainWindow::on_btnSendPdfEmail_clicked);
    connect(m_mailingService, &MailingService::emailSent, this, &MainWindow::onEmailSent);

    ui->aaaz_2->setPlaceholderText("Sujet de l'email...");
    ui->aaaz_3->setPlaceholderText("Message de l'email...");
}

void MainWindow::setupMailingService()
{
    if (!m_mailingService) return;

    QString accountSid = "AC803507060566000080eC7c336ce64k4";
    QString authToken = "ac530584992624a0c228546070kaae8";
    QString fromEmail = "rh@votre-entreprise.com";

    m_mailingService->setTwilioCredentials(accountSid, authToken, fromEmail);
}

void MainWindow::setupRechercheField()
{
    QLineEdit *rechercheField = ui->centralwidget->findChild<QLineEdit*>("aaaz");
    if (rechercheField) {
        rechercheField->setPlaceholderText("Entrez le nom de l'employé...");
    }
}

void MainWindow::setupValidators()
{
    QRegularExpressionValidator *cinValidator = new QRegularExpressionValidator(QRegularExpression("^\\d{8}$"), this);
    ui->id->setValidator(cinValidator);

    QRegularExpressionValidator *phoneValidator = new QRegularExpressionValidator(QRegularExpression("^\\d{8}$"), this);
    ui->tlf->setValidator(phoneValidator);

    QRegularExpressionValidator *emailValidator = new QRegularExpressionValidator(QRegularExpression("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"), this);
    ui->email->setValidator(emailValidator);

    QRegularExpressionValidator *nameValidator = new QRegularExpressionValidator(QRegularExpression("^[a-zA-ZÀ-ÿ\\s\\-']+$"), this);
    ui->nom->setValidator(nameValidator);
    ui->prenom->setValidator(nameValidator);
}

QString MainWindow::getRechercheText()
{
    QLineEdit *field = ui->centralwidget->findChild<QLineEdit*>("aaaz");
    if (field) {
        return field->text().trimmed();
    }
    return "";
}

void MainWindow::setRechercheFocus()
{
    QLineEdit *field = ui->centralwidget->findChild<QLineEdit*>("aaaz");
    if (field) {
        field->setFocus();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    if (m_mailingService) {
        delete m_mailingService;
    }
}

bool MainWindow::validateFields()
{
    if (ui->id->text().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Le CIN est obligatoire.");
        ui->id->setFocus();
        return false;
    }

    if (ui->id->text().length() != 8) {
        QMessageBox::warning(this, "Validation", "Le CIN doit contenir exactement 8 chiffres.");
        ui->id->setFocus();
        return false;
    }

    if (ui->nom->text().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Le nom est obligatoire.");
        ui->nom->setFocus();
        return false;
    }

    QRegularExpression nameRegex("^[a-zA-ZÀ-ÿ\\s\\-']+$");
    if (!nameRegex.match(ui->nom->text()).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le nom ne doit contenir que des lettres.");
        ui->nom->setFocus();
        return false;
    }

    if (ui->prenom->text().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Le prénom est obligatoire.");
        ui->prenom->setFocus();
        return false;
    }

    if (!nameRegex.match(ui->prenom->text()).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le prénom ne doit contenir que des lettres.");
        ui->prenom->setFocus();
        return false;
    }

    if (ui->tlf->text().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Le téléphone est obligatoire.");
        ui->tlf->setFocus();
        return false;
    }

    if (ui->tlf->text().length() != 8) {
        QMessageBox::warning(this, "Validation", "Le téléphone doit contenir exactement 8 chiffres.");
        ui->tlf->setFocus();
        return false;
    }

    if (ui->email->text().isEmpty()) {
        QMessageBox::warning(this, "Validation", "L'email est obligatoire.");
        ui->email->setFocus();
        return false;
    }

    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    if (!emailRegex.match(ui->email->text()).hasMatch()) {
        QMessageBox::warning(this, "Validation", "L'email doit être de la forme: exemple@domaine.com");
        ui->email->setFocus();
        return false;
    }


    return true;
}

void MainWindow::on_btnAjouter_4_clicked()
{
    if (!validateFields()) return;

    int cin = ui->id->text().toInt();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString tel = ui->tlf->text();
    QString email = ui->email->text();
    QString presence = ui->presence->text();

    Employe e(cin, nom, prenom, tel, email, presence);
    bool test = e.ajouter();

    if(test) {
        ui->tableViewAppareils_4->setModel(emp.afficher());
        QMessageBox::information(this, "Ajout", "Ajout effectué avec succès.");
        ui->id->clear();
        ui->nom->clear();
        ui->prenom->clear();
        ui->tlf->clear();
        ui->email->clear();
        ui->presence->clear();
    } else {
        QMessageBox::critical(this, "Ajout", "Échec d'ajout !");
    }
}

void MainWindow::on_btnModifier_4_clicked()
{
    if (!validateFields()) return;

    int cin = ui->id->text().toInt();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString tel = ui->tlf->text();
    QString email = ui->email->text();
    QString presence = ui->presence->text();

    Employe e(cin, nom, prenom, tel, email, presence);
    bool test = e.modifier(cin);

    if (test) {
        ui->tableViewAppareils_4->setModel(emp.afficher());
        QMessageBox::information(this, "Modifier", "Modification réussie.");
    } else {
        QMessageBox::critical(this, "Modifier", "Échec de modification !");
    }
}

void MainWindow::on_btnSupprimer_4_clicked()
{
    if (ui->id->text().isEmpty()) {
        QMessageBox::warning(this, "Suppression", "Veuillez sélectionner un employé à supprimer.");
        return;
    }

    int i;
    QModelIndex index = ui->tableViewAppareils_4->currentIndex();
    i = index.row();
    QModelIndex in = index.sibling(i, 0);
    QString cinStr = ui->tableViewAppareils_4->model()->data(in).toString();
    int cin = cinStr.toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer cet employé ?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No) return;

    bool test = emp.supprimer(cin);

    if (test) {
        ui->tableViewAppareils_4->setModel(emp.afficher());
        QMessageBox::information(this, "Suppression", "Supprimé avec succès.");
        ui->id->clear();
        ui->nom->clear();
        ui->prenom->clear();
        ui->tlf->clear();
        ui->email->clear();
        ui->presence->clear();
    } else {
        QMessageBox::critical(this, "Suppression", "Échec de suppression !");
    }
}

void MainWindow::on_tableViewAppareils_4_clicked(const QModelIndex &index)
{
    if (!index.isValid()) return;
    QString qrCodeData;

    int row = index.row();
    QString cin = ui->tableViewAppareils_4->model()->data(index.sibling(row, 0)).toString();

    QSqlQuery qry;
    qry.prepare("SELECT CINEM, NOM, PRENOM, TELEPHONE, EMAIL, PRESENCE FROM EMPLOYE WHERE CINEM = :cin");
    qry.bindValue(":cin", cin);

    if (qry.exec() && qry.next()) {
        ui->id->setText(qry.value("CINEM").toString());
        ui->nom->setText(qry.value("NOM").toString());
        ui->prenom->setText(qry.value("PRENOM").toString());
        ui->email->setText(qry.value("EMAIL").toString());
        ui->tlf->setText(qry.value("TELEPHONE").toString());
        ui->presence->setText(qry.value("PRESENCE").toString());

        qrCodeData =
            "CIN=" + qry.value("CINEM").toString() + "\n"
                                                     "NOM=" + qry.value("NOM").toString() + "\n"
                                            "PRENOM=" + qry.value("PRENOM").toString() + "\n"
                                               "EMAIL=" + qry.value("EMAIL").toString() + "\n"
                                              "TEL=" + qry.value("TELEPHONE").toString() + "\n"
                                                  "PRESENCE=" + qry.value("PRESENCE").toString();


    }


    //QR CODE
    using namespace qrcodegen;
    // Create the QR Code object
    QrCode qr = QrCode::encodeText( qrCodeData.toUtf8().data(), QrCode::Ecc::MEDIUM );
    // Obtenir la taille du QR Code
    qint32 sz = qr.getSize();
    // Créer une image avec la taille du QR Code
    QImage im(sz,sz, QImage::Format_RGB32);

    QRgb black = qRgb(  0,  0,  0);
    QRgb white = qRgb(255,255,255);
    for (int y = 0; y < sz; y++)
        for (int x = 0; x < sz; x++)
            im.setPixel(x,y,qr.getModule(x, y) ? black : white );
    // Afficher l'image du QR Code dans un QLabel
    ui->qrCodeLabel->setPixmap( QPixmap::fromImage(im.scaled(150,150,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
}

void MainWindow::on_btnReinitialiser_4_clicked()
{
    ui->tableViewAppareils_4->setModel(emp.trier("NOM"));
    QMessageBox::information(this, "Tri", "Tri par nom effectué avec succès.");
}

void MainWindow::on_btnRechercher_4_clicked()
{
    QString nomRecherche = getRechercheText();

    if (nomRecherche.isEmpty()) {
        QMessageBox::warning(this, "Recherche", "Veuillez entrer un nom à rechercher.");
        setRechercheFocus();
        return;
    }

    QRegularExpression nameRegex("^[a-zA-ZÀ-ÿ\\s\\-']+$");
    if (!nameRegex.match(nomRecherche).hasMatch()) {
        QMessageBox::warning(this, "Recherche", "Le nom recherché ne doit contenir que des lettres.");
        setRechercheFocus();
        return;
    }

    ui->tableViewAppareils_4->setModel(emp.rechercherEmploye(nomRecherche));

    QSqlQueryModel *model = emp.rechercherEmploye(nomRecherche);
    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Recherche", "Aucun employé trouvé avec le nom: '" + nomRecherche + "'");
    } else {
        QMessageBox::information(this, "Recherche",
                                 QString("%1 employé(s) trouvé(s) avec le nom: '%2'")
                                     .arg(model->rowCount())
                                     .arg(nomRecherche));
    }
}

QString MainWindow::generatePdf()
{
    QString fileName = QDir::tempPath() + "/liste_employes_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".pdf";

    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableViewAppareils_4->model()->rowCount();
    const int columnCount = ui->tableViewAppareils_4->model()->columnCount();

    out << "<html>\n"
        << "<head>\n"
        << "<meta charset='utf-8'>\n"
        << QString("<title>%1</title>\n").arg("Liste des Employés")
        << "<style>"
        << "body { font-family: Arial, sans-serif; }"
        << "h1 { color: #2c3147; text-align: center; }"
        << "table { width: 100%; border-collapse: collapse; margin: 20px 0; }"
        << "th { background-color: #4CAF50; color: white; padding: 12px; text-align: left; }"
        << "td { padding: 10px; border: 1px solid #ddd; }"
        << "tr:nth-child(even) { background-color: #f2f2f2; }"
        << "</style>"
        << "</head>\n"
        << "<body>\n"
        << "<h1>Liste des Employés</h1>\n"
        << "<p><strong>Date de génération:</strong> " << QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss") << "</p>\n"
        << "<p><strong>Nombre d'employés:</strong> " << rowCount << "</p>\n"
        << "<table border='1' cellspacing='0' cellpadding='5'>\n";

    out << "<thead><tr>";
    for (int column = 0; column < columnCount; ++column) {
        if (!ui->tableViewAppareils_4->isColumnHidden(column)) {
            out << QString("<th>%1</th>").arg(ui->tableViewAppareils_4->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
    out << "</tr></thead>\n<tbody>";

    for (int row = 0; row < rowCount; ++row) {
        out << "<tr>";
        for (int column = 0; column < columnCount; ++column) {
            if (!ui->tableViewAppareils_4->isColumnHidden(column)) {
                QString data = ui->tableViewAppareils_4->model()->data(ui->tableViewAppareils_4->model()->index(row, column)).toString().simplified();
                out << QString("<td>%1</td>").arg(data.isEmpty() ? "&nbsp;" : data);
            }
        }
        out << "</tr>\n";
    }

    out << "</tbody></table>\n"
        << "</body>\n"
        << "</html>\n";

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.print(&printer);

    m_lastPdfPath = fileName;
    return fileName;
}

void MainWindow::on_btnExporterPDF_4_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Choisir le nom du fichier PDF",
                                                    QDir::homePath() + "/liste_employes.pdf",
                                                    "Fichiers PDF (*.pdf)");

    if (fileName.isEmpty()) return;

    if (QFileInfo(fileName).suffix().isEmpty()) fileName.append(".pdf");

    QString pdfPath = generatePdf();

    // Copier le PDF généré vers l'emplacement choisi par l'utilisateur
    QFile::copy(pdfPath, fileName);

    QMessageBox::information(this, "Export PDF", "PDF exporté avec succès !\n" + fileName);
}

void MainWindow::on_btnGenererStats_4_clicked()
{
    Employe e;
    e.afficherDiagramme_Emp_Stat();
}

void MainWindow::on_btnAjouter_5_clicked()
{
    if (ui->email->text().isEmpty()) {
        QMessageBox::warning(this, "Envoi d'email", "Veuillez sélectionner un employé avec un email valide.");
        return;
    }

    QString sujet = ui->aaaz_2->text().trimmed();
    QString message = ui->aaaz_3->text().trimmed();
    QString emailDestinataire = ui->email->text();

    if (sujet.isEmpty() || message.isEmpty()) {
        QMessageBox::warning(this, "Envoi d'email", "Veuillez remplir le sujet et le message.");
        return;
    }

    if (!m_mailingService) {
        QMessageBox::critical(this, "Erreur", "Service d'email non initialisé.");
        return;
    }

    bool success = m_mailingService->sendCustomEmail(emailDestinataire, sujet, message);

    if (success) {
        QMessageBox::information(this, "Email", "Email en cours d'envoi à " + ui->nom->text());
        ui->aaaz_2->clear();
        ui->aaaz_3->clear();
    } else {
        QMessageBox::warning(this, "Email", "Erreur lors de la préparation de l'envoi.");
    }
}

void MainWindow::on_btnAjouter_6_clicked()
{
    showConfigurationDialog();
}

void MainWindow::showConfigurationDialog()
{
    bool ok;
    QString accountSid = QInputDialog::getText(this, "Configuration Twilio",
                                               "Account SID:",
                                               QLineEdit::Normal,
                                               "AC803507060566000080eC7c336ce64k4", &ok);

    if (ok && !accountSid.isEmpty()) {
        QString authToken = QInputDialog::getText(this, "Configuration Twilio",
                                                  "Auth Token:",
                                                  QLineEdit::Password,
                                                  "ac530584992624a0c228546070kaae8", &ok);

        if (ok && !authToken.isEmpty()) {
            QString fromEmail = QInputDialog::getText(this, "Configuration Twilio",
                                                      "Email d'envoi:",
                                                      QLineEdit::Normal,
                                                      "rh@votre-entreprise.com", &ok);

            if (ok && !fromEmail.isEmpty()) {
                if (m_mailingService) {
                    m_mailingService->setTwilioCredentials(accountSid, authToken, fromEmail);
                    QMessageBox::information(this, "Configuration", "Configuration Twilio mise à jour avec succès!");
                }
            }
        }
    }
}

void MainWindow::on_btnSendRealEmail_clicked()
{
    if (ui->email->text().isEmpty()) {
        QMessageBox::warning(this, "Envoi d'email", "Veuillez sélectionner un employé avec un email valide.");
        return;
    }

    QString toEmail = ui->email->text();
    QString sujet = ui->aaaz_2->text().trimmed();
    QString message = ui->aaaz_3->text().trimmed();

    if (sujet.isEmpty() || message.isEmpty()) {
        QMessageBox::warning(this, "Envoi d'email", "Veuillez remplir le sujet et le message.");
        return;
    }

    // Créer un lien Gmail pré-rempli
    QString gmailUrl = QString("https://mail.google.com/mail/?view=cm&fs=1&to=%1&su=%2&body=%3")
                           .arg(toEmail)
                           .arg(QUrl::toPercentEncoding(sujet))
                           .arg(QUrl::toPercentEncoding(message));

    // Ouvrir Gmail dans le navigateur
    QDesktopServices::openUrl(QUrl(gmailUrl));

    QMessageBox::information(this, "Email",
                             "Gmail s'ouvre dans votre navigateur avec l'email pré-rempli.\n\n"
                             "Destinataire: " + toEmail + "\n" +
                                 "Sujet: " + sujet + "\n" +
                                 "Message: " + message);
}

void MainWindow::on_btnSendPdfEmail_clicked()
{
    bool ok;
    QString toEmail = QInputDialog::getText(this, "Envoyer PDF par Email",
                                            "Email du destinataire:",
                                            QLineEdit::Normal,
                                            "", &ok);

    if (!ok || toEmail.isEmpty()) return;

    // Vérifier le format de l'email
    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    if (!emailRegex.match(toEmail).hasMatch()) {
        QMessageBox::warning(this, "Email invalide", "Veuillez entrer une adresse email valide.");
        return;
    }

    QString sujet = "Liste des Employés - " + QDateTime::currentDateTime().toString("dd/MM/yyyy");
    QString message = "Bonjour,\n\nVeuillez trouver ci-joint la liste des employés au format PDF.\n\nCordialement,\nService RH";

    // Générer le PDF
    QString pdfPath = generatePdf();

    if (!m_mailingService) {
        QMessageBox::critical(this, "Erreur", "Service d'email non initialisé.");
        return;
    }

    bool success = m_mailingService->sendPdfByEmail(toEmail, sujet, message, pdfPath);

    if (success) {
        QMessageBox::information(this, "Email PDF", "PDF en cours d'envoi à " + toEmail);
    } else {
        QMessageBox::warning(this, "Email PDF", "Erreur lors de l'envoi du PDF.");
    }
}

void MainWindow::onEmailSent(bool success, const QString& message)
{
    if (success) {
        QMessageBox::information(this, "Email", message);
    } else {
        QMessageBox::critical(this, "Erreur Email", message);
    }
}
