/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNouveau;
    QAction *actionOuvrir;
    QAction *actionSauvegarder;
    QAction *actionQuitter;
    QAction *actionCopier;
    QAction *actionColler;
    QAction *actionAnnuler;
    QAction *actionA_propos;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayoutHeader;
    QLabel *labelLogo;
    QLabel *labelTitle;
    QTabWidget *tabWidget;
    QWidget *tabClients;
    QHBoxLayout *horizontalLayoutClients;
    QGroupBox *groupBoxFormulaireClients;
    QFormLayout *formLayoutClients;
    QLabel *labelIdClient;
    QLineEdit *lineEditIdClient;
    QLabel *labelNom;
    QLineEdit *lineEditNom;
    QLabel *labelPrenom;
    QLineEdit *lineEditPrenom;
    QLabel *labelEmail;
    QLineEdit *lineEditEmail;
    QLabel *labelTelephone;
    QLineEdit *lineEditTelephone;
    QLabel *labelAdresse;
    QLineEdit *lineEditAdresse;
    QLabel *labelDateInscription;
    QDateEdit *dateEditInscription;
    QGroupBox *groupBoxMetiersInnovants;
    QVBoxLayout *verticalLayoutMetiersInnovants;
    QHBoxLayout *horizontalLayoutMetiersButtons;
    QPushButton *btnAnalyserFidelite;
    QPushButton *btnMaintenancePreventive;
    QHBoxLayout *horizontalLayoutActions;
    QPushButton *btnGenererRapportFidelite;
    QPushButton *btnEnvoyerSMS;
    QHBoxLayout *horizontalLayoutProfil;
    QLabel *labelProfilTitre;
    QLabel *labelProfilClient;
    QSpacerItem *horizontalSpacerProfil;
    QLabel *labelScoreTitre;
    QLabel *labelScoreFidelite;
    QHBoxLayout *horizontalLayoutButtonsClients;
    QPushButton *btnAjouterClient;
    QPushButton *btnModifierClient;
    QPushButton *btnSupprimerClient;
    QGroupBox *groupBoxListeClients;
    QVBoxLayout *verticalLayoutListeClients;
    QHBoxLayout *horizontalLayoutRechercheClients;
    QLabel *labelRechercheClient;
    QComboBox *comboBoxCritereClient;
    QLineEdit *lineEditRechercheClient;
    QPushButton *btnRechercherClient;
    QPushButton *btnReinitialiserClient;
    QTableView *tableViewClients;
    QHBoxLayout *horizontalLayoutExportClients;
    QLabel *labelTotalClients;
    QLabel *labelProchainRetourTitre;
    QLabel *labelProchainRetour;
    QSpacerItem *horizontalSpacerClient;
    QPushButton *btnExporterPDFClient;
    QPushButton *btnExporterExcelClient;
    QMenuBar *menubar;
    QMenu *menuFichier;
    QMenu *menuEdition;
    QMenu *menuAide;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1407, 972);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-color: #2c3147;\n"
"    font-family: 'Roboto Regular';\n"
"}\n"
"QGroupBox {\n"
"    font-weight: bold;\n"
"    font-family: 'Montserrat Bold';\n"
"    color: #007BFF;\n"
"    border: 2px solid #007BFF;\n"
"    border-radius: 8px;\n"
"    margin-top: 10px;\n"
"    padding-top: 10px;\n"
"    background-color: white;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 5px 0 5px;\n"
"}\n"
"QPushButton {\n"
"    background-color: #007BFF;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 15px;\n"
"    border-radius: 4px;\n"
"    font-family: 'Montserrat Bold';\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #0056b3;\n"
"}\n"
"QPushButton:disabled {\n"
"    background-color: #6C757D;\n"
"}\n"
"QPushButton.warning {\n"
"    background-color: #FD7E14;\n"
"}\n"
"QPushButton.warning:hover {\n"
"    background-color: #e56a00;\n"
"}\n"
"QPushButton.success {\n"
"    background-color: #28A745;\n"
"}\n"
"QPushButton.s"
                        "uccess:hover {\n"
"    background-color: #218838;\n"
"}\n"
"QLineEdit, QComboBox, QDateEdit, QTextEdit {\n"
"    padding: 6px;\n"
"    border: 1px solid #6C757D;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"}\n"
"QTableView {\n"
"    border: 1px solid #6C757D;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    gridline-color: #e0e0e0;\n"
"    selection-background-color: #007BFF;\n"
"}\n"
"QTableView::item:selected {\n"
"    background-color: #007BFF;\n"
"    color: white;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: #007BFF;\n"
"    color: white;\n"
"    padding: 8px;\n"
"    border: none;\n"
"    font-family: 'Montserrat Bold';\n"
"}\n"
"QTabWidget::pane {\n"
"    border: 1px solid #6C757D;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"}\n"
"QTabBar::tab {\n"
"    background-color: #e9ecef;\n"
"    color: #6C757D;\n"
"    padding: 8px 15px;\n"
"    margin-right: 2px;\n"
"    border-top-left-radius: 4px;\n"
"    border-top-right-radius: 4px"
                        ";\n"
"}\n"
"QTabBar::tab:selected {\n"
"    background-color: #007BFF;\n"
"    color: white;\n"
"}\n"
"QLabel {\n"
"    font-family: 'Roboto Regular';\n"
"    color: #343a40;\n"
"}\n"
"QLabel.title {\n"
"    font-family: 'Montserrat Bold';\n"
"    font-size: 16px;\n"
"    color: #007BFF;\n"
"}\n"
"QFrame#frameTotalClients, QFrame#frameReparationsAttente, QFrame#frameReparationsCours {\n"
"    background-color: #2c3147;\n"
"    border: 2px solid #35b95f;\n"
"    border-radius: 8px;\n"
"}"));
        actionNouveau = new QAction(MainWindow);
        actionNouveau->setObjectName("actionNouveau");
        actionOuvrir = new QAction(MainWindow);
        actionOuvrir->setObjectName("actionOuvrir");
        actionSauvegarder = new QAction(MainWindow);
        actionSauvegarder->setObjectName("actionSauvegarder");
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName("actionQuitter");
        actionCopier = new QAction(MainWindow);
        actionCopier->setObjectName("actionCopier");
        actionColler = new QAction(MainWindow);
        actionColler->setObjectName("actionColler");
        actionAnnuler = new QAction(MainWindow);
        actionAnnuler->setObjectName("actionAnnuler");
        actionA_propos = new QAction(MainWindow);
        actionA_propos->setObjectName("actionA_propos");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayoutHeader = new QHBoxLayout();
        horizontalLayoutHeader->setObjectName("horizontalLayoutHeader");
        labelLogo = new QLabel(centralwidget);
        labelLogo->setObjectName("labelLogo");
        labelLogo->setMinimumSize(QSize(120, 80));
        labelLogo->setMaximumSize(QSize(120, 80));
        labelLogo->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"background-color: rgb(44, 49, 71);\n"
"border: none;"));
        labelLogo->setPixmap(QPixmap(QString::fromUtf8("../logo.png")));
        labelLogo->setScaledContents(true);
        labelLogo->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayoutHeader->addWidget(labelLogo);

        labelTitle = new QLabel(centralwidget);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setStyleSheet(QString::fromUtf8("font: 700 40pt \"Bahnschrift\";\n"
"color: #35b95f;\n"
"margin: 0px;\n"
"background-color: #2c3147;"));
        labelTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayoutHeader->addWidget(labelTitle);


        verticalLayout->addLayout(horizontalLayoutHeader);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setStyleSheet(QString::fromUtf8("QTabWidget::pane {\n"
"    border: 2px solid #2c3147;\n"
"    border-radius: 8px;\n"
"    background-color: #2c3147;\n"
"}\n"
"QTabBar::tab {\n"
"    background-color: #e9ecef;\n"
"    color: #6C757D;\n"
"    padding: 10px 20px;\n"
"    margin-right: 2px;\n"
"    border-top-left-radius: 6px;\n"
"    border-top-right-radius: 6px;\n"
"    font-family: 'Montserrat Bold';\n"
"}\n"
"QTabBar::tab:selected {\n"
"    background-color: #35b95f;\n"
"    color: white;\n"
"}\n"
"QTabBar::tab:hover {\n"
"    background-color: #d0d0d0;\n"
"}"));
        tabClients = new QWidget();
        tabClients->setObjectName("tabClients");
        horizontalLayoutClients = new QHBoxLayout(tabClients);
        horizontalLayoutClients->setObjectName("horizontalLayoutClients");
        groupBoxFormulaireClients = new QGroupBox(tabClients);
        groupBoxFormulaireClients->setObjectName("groupBoxFormulaireClients");
        groupBoxFormulaireClients->setMinimumSize(QSize(400, 0));
        groupBoxFormulaireClients->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Bahnschrift\";\n"
"color: rgb(53, 185, 95);\n"
"border-color: rgb(53, 185, 95);\n"
"background-color: #2c3147;"));
        formLayoutClients = new QFormLayout(groupBoxFormulaireClients);
        formLayoutClients->setObjectName("formLayoutClients");
        labelIdClient = new QLabel(groupBoxFormulaireClients);
        labelIdClient->setObjectName("labelIdClient");
        labelIdClient->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutClients->setWidget(0, QFormLayout::LabelRole, labelIdClient);

        lineEditIdClient = new QLineEdit(groupBoxFormulaireClients);
        lineEditIdClient->setObjectName("lineEditIdClient");
        lineEditIdClient->setEnabled(true);
        lineEditIdClient->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-color: rgb(0, 0, 0);\n"
"color: black;"));

        formLayoutClients->setWidget(0, QFormLayout::FieldRole, lineEditIdClient);

        labelNom = new QLabel(groupBoxFormulaireClients);
        labelNom->setObjectName("labelNom");
        labelNom->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutClients->setWidget(1, QFormLayout::LabelRole, labelNom);

        lineEditNom = new QLineEdit(groupBoxFormulaireClients);
        lineEditNom->setObjectName("lineEditNom");
        lineEditNom->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayoutClients->setWidget(1, QFormLayout::FieldRole, lineEditNom);

        labelPrenom = new QLabel(groupBoxFormulaireClients);
        labelPrenom->setObjectName("labelPrenom");
        labelPrenom->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutClients->setWidget(2, QFormLayout::LabelRole, labelPrenom);

        lineEditPrenom = new QLineEdit(groupBoxFormulaireClients);
        lineEditPrenom->setObjectName("lineEditPrenom");
        lineEditPrenom->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayoutClients->setWidget(2, QFormLayout::FieldRole, lineEditPrenom);

        labelEmail = new QLabel(groupBoxFormulaireClients);
        labelEmail->setObjectName("labelEmail");
        labelEmail->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutClients->setWidget(3, QFormLayout::LabelRole, labelEmail);

        lineEditEmail = new QLineEdit(groupBoxFormulaireClients);
        lineEditEmail->setObjectName("lineEditEmail");
        lineEditEmail->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayoutClients->setWidget(3, QFormLayout::FieldRole, lineEditEmail);

        labelTelephone = new QLabel(groupBoxFormulaireClients);
        labelTelephone->setObjectName("labelTelephone");
        labelTelephone->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutClients->setWidget(4, QFormLayout::LabelRole, labelTelephone);

        lineEditTelephone = new QLineEdit(groupBoxFormulaireClients);
        lineEditTelephone->setObjectName("lineEditTelephone");
        lineEditTelephone->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayoutClients->setWidget(4, QFormLayout::FieldRole, lineEditTelephone);

        labelAdresse = new QLabel(groupBoxFormulaireClients);
        labelAdresse->setObjectName("labelAdresse");
        labelAdresse->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutClients->setWidget(5, QFormLayout::LabelRole, labelAdresse);

        lineEditAdresse = new QLineEdit(groupBoxFormulaireClients);
        lineEditAdresse->setObjectName("lineEditAdresse");
        lineEditAdresse->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayoutClients->setWidget(5, QFormLayout::FieldRole, lineEditAdresse);

        labelDateInscription = new QLabel(groupBoxFormulaireClients);
        labelDateInscription->setObjectName("labelDateInscription");
        labelDateInscription->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutClients->setWidget(6, QFormLayout::LabelRole, labelDateInscription);

        dateEditInscription = new QDateEdit(groupBoxFormulaireClients);
        dateEditInscription->setObjectName("dateEditInscription");
        dateEditInscription->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);font: 9pt \"Segoe UI\";\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));
        dateEditInscription->setCalendarPopup(true);

        formLayoutClients->setWidget(6, QFormLayout::FieldRole, dateEditInscription);

        groupBoxMetiersInnovants = new QGroupBox(groupBoxFormulaireClients);
        groupBoxMetiersInnovants->setObjectName("groupBoxMetiersInnovants");
        groupBoxMetiersInnovants->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Bahnschrift\";\n"
"color: #17A2B8;\n"
"border-color: #17A2B8;\n"
"background-color: #2c3147;\n"
"margin-top: 10px;"));
        verticalLayoutMetiersInnovants = new QVBoxLayout(groupBoxMetiersInnovants);
        verticalLayoutMetiersInnovants->setObjectName("verticalLayoutMetiersInnovants");
        horizontalLayoutMetiersButtons = new QHBoxLayout();
        horizontalLayoutMetiersButtons->setObjectName("horizontalLayoutMetiersButtons");
        btnAnalyserFidelite = new QPushButton(groupBoxMetiersInnovants);
        btnAnalyserFidelite->setObjectName("btnAnalyserFidelite");
        btnAnalyserFidelite->setStyleSheet(QString::fromUtf8("background-color: #17A2B8;\n"
"font: 900 10pt \"Swis721 BlkCn BT\";\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 6px;\n"
"padding: 8px 12px;"));

        horizontalLayoutMetiersButtons->addWidget(btnAnalyserFidelite);

        btnMaintenancePreventive = new QPushButton(groupBoxMetiersInnovants);
        btnMaintenancePreventive->setObjectName("btnMaintenancePreventive");
        btnMaintenancePreventive->setStyleSheet(QString::fromUtf8("background-color: #6F42C1;\n"
"font: 900 10pt \"Swis721 BlkCn BT\";\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 6px;\n"
"padding: 8px 12px;"));

        horizontalLayoutMetiersButtons->addWidget(btnMaintenancePreventive);


        verticalLayoutMetiersInnovants->addLayout(horizontalLayoutMetiersButtons);

        horizontalLayoutActions = new QHBoxLayout();
        horizontalLayoutActions->setObjectName("horizontalLayoutActions");
        btnGenererRapportFidelite = new QPushButton(groupBoxMetiersInnovants);
        btnGenererRapportFidelite->setObjectName("btnGenererRapportFidelite");
        btnGenererRapportFidelite->setStyleSheet(QString::fromUtf8("background-color: #28A745;\n"
"font: 900 9pt \"Swis721 BlkCn BT\";\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 5px;\n"
"padding: 6px 10px;"));

        horizontalLayoutActions->addWidget(btnGenererRapportFidelite);

        btnEnvoyerSMS = new QPushButton(groupBoxMetiersInnovants);
        btnEnvoyerSMS->setObjectName("btnEnvoyerSMS");
        btnEnvoyerSMS->setStyleSheet(QString::fromUtf8("background-color: #FD7E14;\n"
"font: 900 9pt \"Swis721 BlkCn BT\";\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 5px;\n"
"padding: 6px 10px;"));

        horizontalLayoutActions->addWidget(btnEnvoyerSMS);


        verticalLayoutMetiersInnovants->addLayout(horizontalLayoutActions);

        horizontalLayoutProfil = new QHBoxLayout();
        horizontalLayoutProfil->setObjectName("horizontalLayoutProfil");
        labelProfilTitre = new QLabel(groupBoxMetiersInnovants);
        labelProfilTitre->setObjectName("labelProfilTitre");
        labelProfilTitre->setStyleSheet(QString::fromUtf8("font: 12pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayoutProfil->addWidget(labelProfilTitre);

        labelProfilClient = new QLabel(groupBoxMetiersInnovants);
        labelProfilClient->setObjectName("labelProfilClient");
        labelProfilClient->setStyleSheet(QString::fromUtf8("font: 12pt \"Bauhaus 93\";\n"
"color: #FD7E14;\n"
"font-weight: bold;"));

        horizontalLayoutProfil->addWidget(labelProfilClient);

        horizontalSpacerProfil = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutProfil->addItem(horizontalSpacerProfil);

        labelScoreTitre = new QLabel(groupBoxMetiersInnovants);
        labelScoreTitre->setObjectName("labelScoreTitre");
        labelScoreTitre->setStyleSheet(QString::fromUtf8("font: 12pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayoutProfil->addWidget(labelScoreTitre);

        labelScoreFidelite = new QLabel(groupBoxMetiersInnovants);
        labelScoreFidelite->setObjectName("labelScoreFidelite");
        labelScoreFidelite->setStyleSheet(QString::fromUtf8("font: 12pt \"Bauhaus 93\";\n"
"color: #17A2B8;\n"
"font-weight: bold;"));

        horizontalLayoutProfil->addWidget(labelScoreFidelite);


        verticalLayoutMetiersInnovants->addLayout(horizontalLayoutProfil);


        formLayoutClients->setWidget(7, QFormLayout::SpanningRole, groupBoxMetiersInnovants);

        horizontalLayoutButtonsClients = new QHBoxLayout();
        horizontalLayoutButtonsClients->setObjectName("horizontalLayoutButtonsClients");
        btnAjouterClient = new QPushButton(groupBoxFormulaireClients);
        btnAjouterClient->setObjectName("btnAjouterClient");
        btnAjouterClient->setStyleSheet(QString::fromUtf8("background-color: #28A745;\n"
"font: 900 12pt \"Swis721 BlkCn BT\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayoutButtonsClients->addWidget(btnAjouterClient);

        btnModifierClient = new QPushButton(groupBoxFormulaireClients);
        btnModifierClient->setObjectName("btnModifierClient");
        btnModifierClient->setStyleSheet(QString::fromUtf8("background-color: #007BFF;\n"
"color: rgb(255, 255, 255);\n"
"font: 900 12pt \"Swis721 BlkCn BT\";"));

        horizontalLayoutButtonsClients->addWidget(btnModifierClient);

        btnSupprimerClient = new QPushButton(groupBoxFormulaireClients);
        btnSupprimerClient->setObjectName("btnSupprimerClient");
        btnSupprimerClient->setStyleSheet(QString::fromUtf8("background-color: #DC3545;\n"
"font: 900 12pt \"Swis721 BlkCn BT\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayoutButtonsClients->addWidget(btnSupprimerClient);


        formLayoutClients->setLayout(8, QFormLayout::SpanningRole, horizontalLayoutButtonsClients);


        horizontalLayoutClients->addWidget(groupBoxFormulaireClients);

        groupBoxListeClients = new QGroupBox(tabClients);
        groupBoxListeClients->setObjectName("groupBoxListeClients");
        groupBoxListeClients->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Bahnschrift\";\n"
"color: rgb(53, 185, 95);\n"
"border-color: #35b95f;\n"
"background-color: #2c3147;"));
        verticalLayoutListeClients = new QVBoxLayout(groupBoxListeClients);
        verticalLayoutListeClients->setObjectName("verticalLayoutListeClients");
        horizontalLayoutRechercheClients = new QHBoxLayout();
        horizontalLayoutRechercheClients->setObjectName("horizontalLayoutRechercheClients");
        labelRechercheClient = new QLabel(groupBoxListeClients);
        labelRechercheClient->setObjectName("labelRechercheClient");
        labelRechercheClient->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayoutRechercheClients->addWidget(labelRechercheClient);

        comboBoxCritereClient = new QComboBox(groupBoxListeClients);
        comboBoxCritereClient->addItem(QString());
        comboBoxCritereClient->addItem(QString());
        comboBoxCritereClient->addItem(QString());
        comboBoxCritereClient->addItem(QString());
        comboBoxCritereClient->setObjectName("comboBoxCritereClient");
        comboBoxCritereClient->setStyleSheet(QString::fromUtf8("font: 9pt \"Segoe UI\";\n"
"background-color: rgb(255, 255, 255);\n"
"color: black;"));

        horizontalLayoutRechercheClients->addWidget(comboBoxCritereClient);

        lineEditRechercheClient = new QLineEdit(groupBoxListeClients);
        lineEditRechercheClient->setObjectName("lineEditRechercheClient");
        lineEditRechercheClient->setStyleSheet(QString::fromUtf8("font: 9pt \"Segoe UI\";\n"
"background-color: rgb(255, 255, 255);\n"
"color: black;"));

        horizontalLayoutRechercheClients->addWidget(lineEditRechercheClient);

        btnRechercherClient = new QPushButton(groupBoxListeClients);
        btnRechercherClient->setObjectName("btnRechercherClient");
        btnRechercherClient->setStyleSheet(QString::fromUtf8("font: 900 12pt \"Swis721 BlkCn BT\";\n"
"background-color: #007BFF;\n"
"color: white;"));

        horizontalLayoutRechercheClients->addWidget(btnRechercherClient);

        btnReinitialiserClient = new QPushButton(groupBoxListeClients);
        btnReinitialiserClient->setObjectName("btnReinitialiserClient");
        btnReinitialiserClient->setStyleSheet(QString::fromUtf8("background-color: #6C757D;\n"
"color: rgb(255, 255, 255);\n"
"font: 900 12pt \"Swis721 BlkCn BT\";"));

        horizontalLayoutRechercheClients->addWidget(btnReinitialiserClient);


        verticalLayoutListeClients->addLayout(horizontalLayoutRechercheClients);

        tableViewClients = new QTableView(groupBoxListeClients);
        tableViewClients->setObjectName("tableViewClients");
        tableViewClients->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tableViewClients->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tableViewClients->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        tableViewClients->setSortingEnabled(true);

        verticalLayoutListeClients->addWidget(tableViewClients);

        horizontalLayoutExportClients = new QHBoxLayout();
        horizontalLayoutExportClients->setObjectName("horizontalLayoutExportClients");
        labelTotalClients = new QLabel(groupBoxListeClients);
        labelTotalClients->setObjectName("labelTotalClients");
        labelTotalClients->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayoutExportClients->addWidget(labelTotalClients);

        labelProchainRetourTitre = new QLabel(groupBoxListeClients);
        labelProchainRetourTitre->setObjectName("labelProchainRetourTitre");
        labelProchainRetourTitre->setStyleSheet(QString::fromUtf8("font: 12pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayoutExportClients->addWidget(labelProchainRetourTitre);

        labelProchainRetour = new QLabel(groupBoxListeClients);
        labelProchainRetour->setObjectName("labelProchainRetour");
        labelProchainRetour->setStyleSheet(QString::fromUtf8("font: 12pt \"Bauhaus 93\";\n"
"color: #17A2B8;\n"
"font-weight: bold;"));

        horizontalLayoutExportClients->addWidget(labelProchainRetour);

        horizontalSpacerClient = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutExportClients->addItem(horizontalSpacerClient);

        btnExporterPDFClient = new QPushButton(groupBoxListeClients);
        btnExporterPDFClient->setObjectName("btnExporterPDFClient");
        btnExporterPDFClient->setStyleSheet(QString::fromUtf8("background-color: #DC3545;\n"
"color: rgb(255, 255, 255);\n"
"font: 900 12pt \"Swis721 BlkCn BT\";"));

        horizontalLayoutExportClients->addWidget(btnExporterPDFClient);

        btnExporterExcelClient = new QPushButton(groupBoxListeClients);
        btnExporterExcelClient->setObjectName("btnExporterExcelClient");
        btnExporterExcelClient->setStyleSheet(QString::fromUtf8("background-color: #28A745;\n"
"color: rgb(255, 255, 255);\n"
"font: 900 12pt \"Swis721 BlkCn BT\";"));

        horizontalLayoutExportClients->addWidget(btnExporterExcelClient);


        verticalLayoutListeClients->addLayout(horizontalLayoutExportClients);


        horizontalLayoutClients->addWidget(groupBoxListeClients);

        tabWidget->addTab(tabClients, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1407, 21));
        menuFichier = new QMenu(menubar);
        menuFichier->setObjectName("menuFichier");
        menuEdition = new QMenu(menubar);
        menuEdition->setObjectName("menuEdition");
        menuAide = new QMenu(menubar);
        menuAide->setObjectName("menuAide");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFichier->menuAction());
        menubar->addAction(menuEdition->menuAction());
        menubar->addAction(menuAide->menuAction());
        menuFichier->addAction(actionNouveau);
        menuFichier->addAction(actionOuvrir);
        menuFichier->addAction(actionSauvegarder);
        menuFichier->addSeparator();
        menuFichier->addAction(actionQuitter);
        menuEdition->addAction(actionCopier);
        menuEdition->addAction(actionColler);
        menuEdition->addAction(actionAnnuler);
        menuAide->addAction(actionA_propos);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Smart Repair Hub - Gestion Compl\303\250te", nullptr));
        actionNouveau->setText(QCoreApplication::translate("MainWindow", "Nouveau", nullptr));
        actionOuvrir->setText(QCoreApplication::translate("MainWindow", "Ouvrir", nullptr));
        actionSauvegarder->setText(QCoreApplication::translate("MainWindow", "Sauvegarder", nullptr));
        actionQuitter->setText(QCoreApplication::translate("MainWindow", "Quitter", nullptr));
        actionCopier->setText(QCoreApplication::translate("MainWindow", "Copier", nullptr));
        actionColler->setText(QCoreApplication::translate("MainWindow", "Coller", nullptr));
        actionAnnuler->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        actionA_propos->setText(QCoreApplication::translate("MainWindow", "\303\200 propos", nullptr));
        labelLogo->setText(QString());
        labelTitle->setText(QCoreApplication::translate("MainWindow", "FIXHUB", nullptr));
        groupBoxFormulaireClients->setTitle(QCoreApplication::translate("MainWindow", "Formulaire Client", nullptr));
        labelIdClient->setText(QCoreApplication::translate("MainWindow", "CIN CLIENT:", nullptr));
        labelNom->setText(QCoreApplication::translate("MainWindow", "Nom :", nullptr));
        labelPrenom->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom :", nullptr));
        labelEmail->setText(QCoreApplication::translate("MainWindow", "Email :", nullptr));
        labelTelephone->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone:", nullptr));
        labelAdresse->setText(QCoreApplication::translate("MainWindow", "Adresse:", nullptr));
        labelDateInscription->setText(QCoreApplication::translate("MainWindow", "Date Naissance:", nullptr));
        groupBoxMetiersInnovants->setTitle(QCoreApplication::translate("MainWindow", "\360\237\216\257 M\303\251tiers Innovants", nullptr));
        btnAnalyserFidelite->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212 Analyse Fid\303\251lit\303\251", nullptr));
#if QT_CONFIG(tooltip)
        btnAnalyserFidelite->setToolTip(QCoreApplication::translate("MainWindow", "Analyser le score de fid\303\251lit\303\251 et pr\303\251dire le prochain retour", nullptr));
#endif // QT_CONFIG(tooltip)
        btnMaintenancePreventive->setText(QCoreApplication::translate("MainWindow", "\360\237\224\247 Maintenance", nullptr));
#if QT_CONFIG(tooltip)
        btnMaintenancePreventive->setToolTip(QCoreApplication::translate("MainWindow", "Analyser les appareils et recommander des maintenances pr\303\251ventives", nullptr));
#endif // QT_CONFIG(tooltip)
        btnGenererRapportFidelite->setText(QCoreApplication::translate("MainWindow", "\360\237\223\204 PDF Fid\303\251lit\303\251", nullptr));
#if QT_CONFIG(tooltip)
        btnGenererRapportFidelite->setToolTip(QCoreApplication::translate("MainWindow", "G\303\251n\303\251rer un rapport PDF d\303\251taill\303\251 de fid\303\251lit\303\251", nullptr));
#endif // QT_CONFIG(tooltip)
        btnEnvoyerSMS->setText(QCoreApplication::translate("MainWindow", "\360\237\223\261 SMS Client", nullptr));
#if QT_CONFIG(tooltip)
        btnEnvoyerSMS->setToolTip(QCoreApplication::translate("MainWindow", "Envoyer un SMS au client pour maintenance", nullptr));
#endif // QT_CONFIG(tooltip)
        labelProfilTitre->setText(QCoreApplication::translate("MainWindow", "Profil:", nullptr));
        labelProfilClient->setText(QCoreApplication::translate("MainWindow", "Non analys\303\251", nullptr));
        labelScoreTitre->setText(QCoreApplication::translate("MainWindow", "Score:", nullptr));
        labelScoreFidelite->setText(QCoreApplication::translate("MainWindow", "0/100", nullptr));
        btnAjouterClient->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnModifierClient->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        btnSupprimerClient->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        groupBoxListeClients->setTitle(QCoreApplication::translate("MainWindow", "Liste des Clients", nullptr));
        labelRechercheClient->setText(QCoreApplication::translate("MainWindow", "Rechercher par:", nullptr));
        comboBoxCritereClient->setItemText(0, QCoreApplication::translate("MainWindow", "Nom", nullptr));
        comboBoxCritereClient->setItemText(1, QCoreApplication::translate("MainWindow", "Email", nullptr));
        comboBoxCritereClient->setItemText(2, QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone", nullptr));
        comboBoxCritereClient->setItemText(3, QCoreApplication::translate("MainWindow", "Ville", nullptr));

        lineEditRechercheClient->setPlaceholderText(QCoreApplication::translate("MainWindow", "Terme de recherche...", nullptr));
        btnRechercherClient->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        btnReinitialiserClient->setText(QCoreApplication::translate("MainWindow", "trier par nom", nullptr));
        labelTotalClients->setText(QCoreApplication::translate("MainWindow", "Total: 0 clients", nullptr));
        labelProchainRetourTitre->setText(QCoreApplication::translate("MainWindow", "Prochain retour:", nullptr));
        labelProchainRetour->setText(QCoreApplication::translate("MainWindow", "Non pr\303\251dit", nullptr));
        btnExporterPDFClient->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        btnExporterExcelClient->setText(QCoreApplication::translate("MainWindow", "Exporter Excel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabClients), QCoreApplication::translate("MainWindow", "Gestion Clients", nullptr));
        menuFichier->setTitle(QCoreApplication::translate("MainWindow", "Fichier", nullptr));
        menuEdition->setTitle(QCoreApplication::translate("MainWindow", "\303\211dition", nullptr));
        menuAide->setTitle(QCoreApplication::translate("MainWindow", "Aide", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
