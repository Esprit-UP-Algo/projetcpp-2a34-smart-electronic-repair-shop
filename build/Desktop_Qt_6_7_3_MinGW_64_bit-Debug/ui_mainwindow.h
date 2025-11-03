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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
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
#include <QtWidgets/QTextEdit>
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
    QWidget *tabDashboard;
    QVBoxLayout *verticalLayoutDashboard;
    QHBoxLayout *horizontalLayoutStats;
    QFrame *frameTotalClients;
    QVBoxLayout *verticalLayoutClients;
    QLabel *labelClientTitle;
    QLabel *labelClientCount;
    QLabel *labelClientSub;
    QFrame *frameReparationsAttente;
    QVBoxLayout *verticalLayoutAttente;
    QLabel *labelAttenteTitle;
    QLabel *labelAttenteCount;
    QLabel *labelCAAbbr;
    QFrame *frameReparationsCours;
    QVBoxLayout *verticalLayoutCours;
    QLabel *labelCoursTitle;
    QLabel *labelCoursCount;
    QLabel *labelCoursSub;
    QGroupBox *groupBoxReparations;
    QVBoxLayout *verticalLayoutReparations;
    QTableView *tableViewReparations;
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
    QLabel *labelVille;
    QLineEdit *lineEditVille;
    QLabel *labelDateInscription;
    QDateEdit *dateEditInscription;
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
    QSpacerItem *horizontalSpacerClient;
    QPushButton *btnExporterPDFClient;
    QPushButton *btnExporterExcelClient;
    QWidget *tab_3;
    QLabel *label_5;
    QTabWidget *tabWidget_2;
    QWidget *tabGestion;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBoxFormulaire;
    QFormLayout *formLayout;
    QLabel *labelId;
    QLineEdit *lineEditId;
    QLabel *labelType_2;
    QLabel *labelMarque_2;
    QLineEdit *lineEditMarque_2;
    QLabel *labelModele_2;
    QLineEdit *lineEditModele_2;
    QLabel *labelNumeroSerie_2;
    QLineEdit *lineEditNumeroSerie_2;
    QHBoxLayout *horizontalLayoutButtons;
    QPushButton *btnAjouter;
    QPushButton *btnModifier;
    QPushButton *btnSupprimer;
    QHBoxLayout *horizontalLayoutQR;
    QLineEdit *lineEditMarque_3;
    QGroupBox *groupBoxListe;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayoutRecherche;
    QLabel *labelRecherche;
    QComboBox *comboBoxCritere;
    QPushButton *btnRechercher;
    QPushButton *btnReinitialiser;
    QTableView *tableViewAppareils_2;
    QHBoxLayout *horizontalLayoutExport;
    QPushButton *btnExporterPDF;
    QWidget *tabStatistiques_2;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBoxStats;
    QHBoxLayout *horizontalLayout_2;
    QFrame *frameGraphique;
    QVBoxLayout *verticalLayout_4;
    QWidget *widgetGraphique;
    QLabel *labelGraphTitle;
    QFrame *frameDetails;
    QVBoxLayout *verticalLayout_5;
    QLabel *labelDetailsTitle;
    QTextEdit *textEditStats;
    QPushButton *btnGenererStats;
    QWidget *tabAppareils;
    QHBoxLayout *horizontalLayoutAppareils;
    QGroupBox *groupBoxFormulaireAppareils;
    QFormLayout *formLayoutAppareils;
    QLabel *labelIdAppareil;
    QLineEdit *lineEditIdAppareil;
    QLabel *labelType;
    QComboBox *comboBoxType;
    QLabel *labelMarque;
    QLineEdit *lineEditMarque;
    QLabel *labelModele;
    QLineEdit *lineEditModele;
    QLabel *labelNumeroSerie;
    QLineEdit *lineEditNumeroSerie;
    QLabel *labelDateAchat;
    QDateEdit *dateEditAchat;
    QHBoxLayout *horizontalLayoutButtonsAppareils;
    QPushButton *btnAjouterAppareil;
    QPushButton *btnModifierAppareil;
    QPushButton *btnSupprimerAppareil;
    QGroupBox *groupBoxListeAppareils;
    QVBoxLayout *verticalLayoutListeAppareils;
    QHBoxLayout *horizontalLayoutRechercheAppareils;
    QLabel *labelRechercheAppareil;
    QComboBox *comboBoxCritereAppareil;
    QPushButton *btnRechercherAppareil;
    QPushButton *btnReinitialiserAppareil;
    QTableView *tableViewAppareils;
    QHBoxLayout *horizontalLayoutExportAppareils;
    QLabel *labelTotalAppareils;
    QSpacerItem *horizontalSpacerAppareil;
    QPushButton *btnExporterPDFAppareil;
    QPushButton *btnExporterExcelAppareil;
    QWidget *tabReparations;
    QHBoxLayout *horizontalLayoutReparations;
    QGroupBox *groupBoxFormulaireReparations;
    QFormLayout *formLayoutReparations;
    QLabel *labelIdReparation;
    QLineEdit *lineEditIdReparation;
    QLabel *labelAppareilReparation;
    QComboBox *comboBoxAppareilReparation;
    QLabel *labelDateDepot;
    QDateEdit *dateEditDepot;
    QLabel *labelDateRetourPrevue;
    QDateEdit *dateEditRetourPrevue;
    QLabel *labelPanne;
    QTextEdit *textEditPanne;
    QLabel *labelStatutReparation;
    QComboBox *comboBoxStatutReparation;
    QLabel *labelCout;
    QLineEdit *lineEditCout;
    QHBoxLayout *horizontalLayoutButtonsReparations;
    QPushButton *btnAjouterReparation;
    QPushButton *btnModifierReparation;
    QPushButton *btnSupprimerReparation;
    QGroupBox *groupBoxListeReparations;
    QVBoxLayout *verticalLayoutListeReparations;
    QHBoxLayout *horizontalLayoutRechercheReparations;
    QLabel *labelRechercheReparation;
    QComboBox *comboBoxCritereReparation;
    QLineEdit *lineEditRechercheReparation;
    QPushButton *btnRechercherReparation;
    QPushButton *btnReinitialiserReparation;
    QTableView *tableViewReparationsListe;
    QHBoxLayout *horizontalLayoutExportReparations;
    QLabel *labelTotalReparations;
    QSpacerItem *horizontalSpacerReparation;
    QPushButton *btnExporterPDFReparation;
    QPushButton *btnExporterExcelReparation;
    QWidget *tabStatistiques;
    QVBoxLayout *verticalLayoutStatistiques;
    QHBoxLayout *horizontalLayoutStatsTop;
    QGroupBox *groupBoxStatsGenerales;
    QGridLayout *gridLayoutStats;
    QLabel *labelStatsClients;
    QLabel *labelStatsClientsValue;
    QLabel *labelStatsAppareils;
    QLabel *labelStatsAppareilsValue;
    QLabel *labelStatsReparations;
    QLabel *labelStatsReparationsValue;
    QLabel *labelStatsCA;
    QLabel *labelStatsCAValue;
    QGroupBox *groupBoxFiltres;
    QFormLayout *formLayoutFiltres;
    QLabel *labelPeriode;
    QComboBox *comboBoxPeriode;
    QLabel *labelDateDebut;
    QDateEdit *dateEditDebut;
    QLabel *labelDateFin;
    QDateEdit *dateEditFin;
    QPushButton *btnGenererRapport;
    QGroupBox *groupBoxGraphiques;
    QHBoxLayout *horizontalLayoutGraphiques;
    QLabel *labelGraphiquePlaceholder;
    QLabel *labelGraphique2Placeholder;
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
        labelLogo->setPixmap(QPixmap(QString::fromUtf8("../../Downloads/logo.png")));
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
        tabDashboard = new QWidget();
        tabDashboard->setObjectName("tabDashboard");
        verticalLayoutDashboard = new QVBoxLayout(tabDashboard);
        verticalLayoutDashboard->setObjectName("verticalLayoutDashboard");
        horizontalLayoutStats = new QHBoxLayout();
        horizontalLayoutStats->setObjectName("horizontalLayoutStats");
        frameTotalClients = new QFrame(tabDashboard);
        frameTotalClients->setObjectName("frameTotalClients");
        frameTotalClients->setMinimumSize(QSize(200, 120));
        verticalLayoutClients = new QVBoxLayout(frameTotalClients);
        verticalLayoutClients->setObjectName("verticalLayoutClients");
        labelClientTitle = new QLabel(frameTotalClients);
        labelClientTitle->setObjectName("labelClientTitle");
        labelClientTitle->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Montserrat Bold\";\n"
"color: #35b95f;\n"
"margin: 5px;"));
        labelClientTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayoutClients->addWidget(labelClientTitle);

        labelClientCount = new QLabel(frameTotalClients);
        labelClientCount->setObjectName("labelClientCount");
        labelClientCount->setStyleSheet(QString::fromUtf8("font: 700 24pt \"Montserrat Bold\";\n"
"color: #ffffff;\n"
"margin: 5px;"));
        labelClientCount->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayoutClients->addWidget(labelClientCount);

        labelClientSub = new QLabel(frameTotalClients);
        labelClientSub->setObjectName("labelClientSub");
        labelClientSub->setStyleSheet(QString::fromUtf8("font: 10pt \"Roboto Regular\";\n"
"color: #6C757D;\n"
"margin: 5px;"));
        labelClientSub->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayoutClients->addWidget(labelClientSub);


        horizontalLayoutStats->addWidget(frameTotalClients);

        frameReparationsAttente = new QFrame(tabDashboard);
        frameReparationsAttente->setObjectName("frameReparationsAttente");
        frameReparationsAttente->setMinimumSize(QSize(200, 120));
        verticalLayoutAttente = new QVBoxLayout(frameReparationsAttente);
        verticalLayoutAttente->setObjectName("verticalLayoutAttente");
        labelAttenteTitle = new QLabel(frameReparationsAttente);
        labelAttenteTitle->setObjectName("labelAttenteTitle");
        labelAttenteTitle->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Montserrat Bold\";\n"
"color: #35b95f;\n"
"margin: 5px;"));
        labelAttenteTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayoutAttente->addWidget(labelAttenteTitle);

        labelAttenteCount = new QLabel(frameReparationsAttente);
        labelAttenteCount->setObjectName("labelAttenteCount");
        labelAttenteCount->setStyleSheet(QString::fromUtf8("font: 700 24pt \"Montserrat Bold\";\n"
"color: #ffffff;\n"
"margin: 5px;"));
        labelAttenteCount->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayoutAttente->addWidget(labelAttenteCount);

        labelCAAbbr = new QLabel(frameReparationsAttente);
        labelCAAbbr->setObjectName("labelCAAbbr");
        labelCAAbbr->setStyleSheet(QString::fromUtf8("font: 10pt \"Roboto Regular\";\n"
"color: #6C757D;\n"
"margin: 5px;"));
        labelCAAbbr->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayoutAttente->addWidget(labelCAAbbr);


        horizontalLayoutStats->addWidget(frameReparationsAttente);

        frameReparationsCours = new QFrame(tabDashboard);
        frameReparationsCours->setObjectName("frameReparationsCours");
        frameReparationsCours->setMinimumSize(QSize(200, 120));
        verticalLayoutCours = new QVBoxLayout(frameReparationsCours);
        verticalLayoutCours->setObjectName("verticalLayoutCours");
        labelCoursTitle = new QLabel(frameReparationsCours);
        labelCoursTitle->setObjectName("labelCoursTitle");
        labelCoursTitle->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Montserrat Bold\";\n"
"color: #35b95f;\n"
"margin: 5px;"));
        labelCoursTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayoutCours->addWidget(labelCoursTitle);

        labelCoursCount = new QLabel(frameReparationsCours);
        labelCoursCount->setObjectName("labelCoursCount");
        labelCoursCount->setStyleSheet(QString::fromUtf8("font: 700 24pt \"Montserrat Bold\";\n"
"color: #ffffff;\n"
"margin: 5px;"));
        labelCoursCount->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayoutCours->addWidget(labelCoursCount);

        labelCoursSub = new QLabel(frameReparationsCours);
        labelCoursSub->setObjectName("labelCoursSub");
        labelCoursSub->setStyleSheet(QString::fromUtf8("font: 10pt \"Roboto Regular\";\n"
"color: #6C757D;\n"
"margin: 5px;"));
        labelCoursSub->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayoutCours->addWidget(labelCoursSub);


        horizontalLayoutStats->addWidget(frameReparationsCours);


        verticalLayoutDashboard->addLayout(horizontalLayoutStats);

        groupBoxReparations = new QGroupBox(tabDashboard);
        groupBoxReparations->setObjectName("groupBoxReparations");
        groupBoxReparations->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Bahnschrift\";\n"
"color: rgb(53, 185, 95);\n"
"border-color: rgb(53, 185, 95);\n"
"background-color: #2c3147;"));
        verticalLayoutReparations = new QVBoxLayout(groupBoxReparations);
        verticalLayoutReparations->setObjectName("verticalLayoutReparations");
        tableViewReparations = new QTableView(groupBoxReparations);
        tableViewReparations->setObjectName("tableViewReparations");
        tableViewReparations->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tableViewReparations->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tableViewReparations->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        tableViewReparations->setSortingEnabled(true);

        verticalLayoutReparations->addWidget(tableViewReparations);


        verticalLayoutDashboard->addWidget(groupBoxReparations);

        tabWidget->addTab(tabDashboard, QString());
        tabClients = new QWidget();
        tabClients->setObjectName("tabClients");
        horizontalLayoutClients = new QHBoxLayout(tabClients);
        horizontalLayoutClients->setObjectName("horizontalLayoutClients");
        groupBoxFormulaireClients = new QGroupBox(tabClients);
        groupBoxFormulaireClients->setObjectName("groupBoxFormulaireClients");
        groupBoxFormulaireClients->setMinimumSize(QSize(350, 0));
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
        lineEditIdClient->setEnabled(false);
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

        labelVille = new QLabel(groupBoxFormulaireClients);
        labelVille->setObjectName("labelVille");
        labelVille->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutClients->setWidget(6, QFormLayout::LabelRole, labelVille);

        lineEditVille = new QLineEdit(groupBoxFormulaireClients);
        lineEditVille->setObjectName("lineEditVille");
        lineEditVille->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayoutClients->setWidget(6, QFormLayout::FieldRole, lineEditVille);

        labelDateInscription = new QLabel(groupBoxFormulaireClients);
        labelDateInscription->setObjectName("labelDateInscription");
        labelDateInscription->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutClients->setWidget(7, QFormLayout::LabelRole, labelDateInscription);

        dateEditInscription = new QDateEdit(groupBoxFormulaireClients);
        dateEditInscription->setObjectName("dateEditInscription");
        dateEditInscription->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);font: 9pt \"Segoe UI\";\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));
        dateEditInscription->setCalendarPopup(true);

        formLayoutClients->setWidget(7, QFormLayout::FieldRole, dateEditInscription);

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
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        label_5 = new QLabel(tab_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 300, 101, 16));
        tabWidget_2 = new QTabWidget(tab_3);
        tabWidget_2->setObjectName("tabWidget_2");
        tabWidget_2->setGeometry(QRect(10, 38, 1321, 731));
        tabWidget_2->setStyleSheet(QString::fromUtf8("QTabWidget::pane {\n"
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
        tabGestion = new QWidget();
        tabGestion->setObjectName("tabGestion");
        tabGestion->setStyleSheet(QString::fromUtf8("background-color: rgb(44, 49, 71);"));
        horizontalLayout = new QHBoxLayout(tabGestion);
        horizontalLayout->setObjectName("horizontalLayout");
        groupBoxFormulaire = new QGroupBox(tabGestion);
        groupBoxFormulaire->setObjectName("groupBoxFormulaire");
        groupBoxFormulaire->setMinimumSize(QSize(350, 0));
        groupBoxFormulaire->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Bahnschrift\";\n"
"color: rgb(53, 185, 95);\n"
"border-color: rgb(53, 185, 95);\n"
"background-color: #2c3147;"));
        formLayout = new QFormLayout(groupBoxFormulaire);
        formLayout->setObjectName("formLayout");
        labelId = new QLabel(groupBoxFormulaire);
        labelId->setObjectName("labelId");
        labelId->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelId);

        lineEditId = new QLineEdit(groupBoxFormulaire);
        lineEditId->setObjectName("lineEditId");
        lineEditId->setEnabled(false);
        lineEditId->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-color: rgb(0, 0, 0);\n"
"color: black;"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditId);

        labelType_2 = new QLabel(groupBoxFormulaire);
        labelType_2->setObjectName("labelType_2");
        labelType_2->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelType_2);

        labelMarque_2 = new QLabel(groupBoxFormulaire);
        labelMarque_2->setObjectName("labelMarque_2");
        labelMarque_2->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelMarque_2);

        lineEditMarque_2 = new QLineEdit(groupBoxFormulaire);
        lineEditMarque_2->setObjectName("lineEditMarque_2");
        lineEditMarque_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditMarque_2);

        labelModele_2 = new QLabel(groupBoxFormulaire);
        labelModele_2->setObjectName("labelModele_2");
        labelModele_2->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayout->setWidget(3, QFormLayout::LabelRole, labelModele_2);

        lineEditModele_2 = new QLineEdit(groupBoxFormulaire);
        lineEditModele_2->setObjectName("lineEditModele_2");
        lineEditModele_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEditModele_2);

        labelNumeroSerie_2 = new QLabel(groupBoxFormulaire);
        labelNumeroSerie_2->setObjectName("labelNumeroSerie_2");
        labelNumeroSerie_2->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayout->setWidget(4, QFormLayout::LabelRole, labelNumeroSerie_2);

        lineEditNumeroSerie_2 = new QLineEdit(groupBoxFormulaire);
        lineEditNumeroSerie_2->setObjectName("lineEditNumeroSerie_2");
        lineEditNumeroSerie_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayout->setWidget(4, QFormLayout::FieldRole, lineEditNumeroSerie_2);

        horizontalLayoutButtons = new QHBoxLayout();
        horizontalLayoutButtons->setObjectName("horizontalLayoutButtons");
        btnAjouter = new QPushButton(groupBoxFormulaire);
        btnAjouter->setObjectName("btnAjouter");
        btnAjouter->setStyleSheet(QString::fromUtf8("background-color: #28A745;\n"
"font: 900 12pt \"Swis721 BlkCn BT\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayoutButtons->addWidget(btnAjouter);

        btnModifier = new QPushButton(groupBoxFormulaire);
        btnModifier->setObjectName("btnModifier");
        btnModifier->setStyleSheet(QString::fromUtf8("background-color: #007BFF;\n"
"color: rgb(255, 255, 255);\n"
"font: 900 12pt \"Swis721 BlkCn BT\";"));

        horizontalLayoutButtons->addWidget(btnModifier);

        btnSupprimer = new QPushButton(groupBoxFormulaire);
        btnSupprimer->setObjectName("btnSupprimer");
        btnSupprimer->setStyleSheet(QString::fromUtf8("background-color: #DC3545;\n"
"font: 900 12pt \"Swis721 BlkCn BT\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayoutButtons->addWidget(btnSupprimer);


        formLayout->setLayout(5, QFormLayout::SpanningRole, horizontalLayoutButtons);

        horizontalLayoutQR = new QHBoxLayout();
        horizontalLayoutQR->setObjectName("horizontalLayoutQR");

        formLayout->setLayout(6, QFormLayout::SpanningRole, horizontalLayoutQR);

        lineEditMarque_3 = new QLineEdit(groupBoxFormulaire);
        lineEditMarque_3->setObjectName("lineEditMarque_3");
        lineEditMarque_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditMarque_3);


        horizontalLayout->addWidget(groupBoxFormulaire);

        groupBoxListe = new QGroupBox(tabGestion);
        groupBoxListe->setObjectName("groupBoxListe");
        groupBoxListe->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Bahnschrift\";\n"
"color: rgb(53, 185, 95);\n"
"border-color: #35b95f;\n"
"background-color: #2c3147;"));
        verticalLayout_2 = new QVBoxLayout(groupBoxListe);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayoutRecherche = new QHBoxLayout();
        horizontalLayoutRecherche->setObjectName("horizontalLayoutRecherche");
        labelRecherche = new QLabel(groupBoxListe);
        labelRecherche->setObjectName("labelRecherche");
        labelRecherche->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayoutRecherche->addWidget(labelRecherche);

        comboBoxCritere = new QComboBox(groupBoxListe);
        comboBoxCritere->addItem(QString());
        comboBoxCritere->setObjectName("comboBoxCritere");
        comboBoxCritere->setStyleSheet(QString::fromUtf8("font: 9pt \"Segoe UI\";\n"
"background-color: rgb(255, 255, 255);\n"
"color: black;"));

        horizontalLayoutRecherche->addWidget(comboBoxCritere);

        btnRechercher = new QPushButton(groupBoxListe);
        btnRechercher->setObjectName("btnRechercher");
        btnRechercher->setStyleSheet(QString::fromUtf8("font: 900 12pt \"Swis721 BlkCn BT\";\n"
"background-color: #007BFF;\n"
"color: white;"));

        horizontalLayoutRecherche->addWidget(btnRechercher);

        btnReinitialiser = new QPushButton(groupBoxListe);
        btnReinitialiser->setObjectName("btnReinitialiser");
        btnReinitialiser->setStyleSheet(QString::fromUtf8("background-color: #6C757D;\n"
"color: rgb(255, 255, 255);\n"
"font: 900 12pt \"Swis721 BlkCn BT\";"));

        horizontalLayoutRecherche->addWidget(btnReinitialiser);


        verticalLayout_2->addLayout(horizontalLayoutRecherche);

        tableViewAppareils_2 = new QTableView(groupBoxListe);
        tableViewAppareils_2->setObjectName("tableViewAppareils_2");
        tableViewAppareils_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tableViewAppareils_2->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tableViewAppareils_2->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        tableViewAppareils_2->setSortingEnabled(true);

        verticalLayout_2->addWidget(tableViewAppareils_2);

        horizontalLayoutExport = new QHBoxLayout();
        horizontalLayoutExport->setObjectName("horizontalLayoutExport");
        btnExporterPDF = new QPushButton(groupBoxListe);
        btnExporterPDF->setObjectName("btnExporterPDF");
        btnExporterPDF->setStyleSheet(QString::fromUtf8("background-color: #DC3545;\n"
"color: rgb(255, 255, 255);\n"
"font: 900 12pt \"Swis721 BlkCn BT\";"));

        horizontalLayoutExport->addWidget(btnExporterPDF);


        verticalLayout_2->addLayout(horizontalLayoutExport);


        horizontalLayout->addWidget(groupBoxListe);

        tabWidget_2->addTab(tabGestion, QString());
        tabStatistiques_2 = new QWidget();
        tabStatistiques_2->setObjectName("tabStatistiques_2");
        tabStatistiques_2->setStyleSheet(QString::fromUtf8("background-color: rgb(44, 49, 71);"));
        verticalLayout_3 = new QVBoxLayout(tabStatistiques_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        groupBoxStats = new QGroupBox(tabStatistiques_2);
        groupBoxStats->setObjectName("groupBoxStats");
        groupBoxStats->setStyleSheet(QString::fromUtf8("border-color: rgb(53, 185, 95);\n"
"color: rgb(53, 185, 95);\n"
"font: 700 16pt \"Bahnschrift\";\n"
""));
        horizontalLayout_2 = new QHBoxLayout(groupBoxStats);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        frameGraphique = new QFrame(groupBoxStats);
        frameGraphique->setObjectName("frameGraphique");
        frameGraphique->setFrameShape(QFrame::Shape::StyledPanel);
        frameGraphique->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_4 = new QVBoxLayout(frameGraphique);
        verticalLayout_4->setObjectName("verticalLayout_4");
        widgetGraphique = new QWidget(frameGraphique);
        widgetGraphique->setObjectName("widgetGraphique");
        widgetGraphique->setMinimumSize(QSize(400, 300));
        widgetGraphique->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border: 1px solid #6C757D;\n"
"border-radius: 4px;"));

        verticalLayout_4->addWidget(widgetGraphique);

        labelGraphTitle = new QLabel(frameGraphique);
        labelGraphTitle->setObjectName("labelGraphTitle");
        labelGraphTitle->setStyleSheet(QString::fromUtf8("font-family: 'Montserrat Bold';\n"
"font-size: 16px;\n"
"color: #007BFF;\n"
"margin: 10px;"));
        labelGraphTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(labelGraphTitle);


        horizontalLayout_2->addWidget(frameGraphique);

        frameDetails = new QFrame(groupBoxStats);
        frameDetails->setObjectName("frameDetails");
        frameDetails->setFrameShape(QFrame::Shape::StyledPanel);
        frameDetails->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_5 = new QVBoxLayout(frameDetails);
        verticalLayout_5->setObjectName("verticalLayout_5");
        labelDetailsTitle = new QLabel(frameDetails);
        labelDetailsTitle->setObjectName("labelDetailsTitle");
        labelDetailsTitle->setStyleSheet(QString::fromUtf8("font-family: 'Montserrat Bold';\n"
"font-size: 16px;\n"
"color: #007BFF;\n"
"margin: 10px;"));
        labelDetailsTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(labelDetailsTitle);

        textEditStats = new QTextEdit(frameDetails);
        textEditStats->setObjectName("textEditStats");
        textEditStats->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border: 1px solid #6C757D;\n"
"border-radius: 4px;\n"
"padding: 10px;"));

        verticalLayout_5->addWidget(textEditStats);

        btnGenererStats = new QPushButton(frameDetails);
        btnGenererStats->setObjectName("btnGenererStats");

        verticalLayout_5->addWidget(btnGenererStats);


        horizontalLayout_2->addWidget(frameDetails);


        verticalLayout_3->addWidget(groupBoxStats);

        tabWidget_2->addTab(tabStatistiques_2, QString());
        tabWidget->addTab(tab_3, QString());
        tabAppareils = new QWidget();
        tabAppareils->setObjectName("tabAppareils");
        horizontalLayoutAppareils = new QHBoxLayout(tabAppareils);
        horizontalLayoutAppareils->setObjectName("horizontalLayoutAppareils");
        groupBoxFormulaireAppareils = new QGroupBox(tabAppareils);
        groupBoxFormulaireAppareils->setObjectName("groupBoxFormulaireAppareils");
        groupBoxFormulaireAppareils->setMinimumSize(QSize(350, 0));
        groupBoxFormulaireAppareils->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Bahnschrift\";\n"
"color: rgb(53, 185, 95);\n"
"border-color: rgb(53, 185, 95);\n"
"background-color: #2c3147;"));
        formLayoutAppareils = new QFormLayout(groupBoxFormulaireAppareils);
        formLayoutAppareils->setObjectName("formLayoutAppareils");
        labelIdAppareil = new QLabel(groupBoxFormulaireAppareils);
        labelIdAppareil->setObjectName("labelIdAppareil");
        labelIdAppareil->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutAppareils->setWidget(0, QFormLayout::LabelRole, labelIdAppareil);

        lineEditIdAppareil = new QLineEdit(groupBoxFormulaireAppareils);
        lineEditIdAppareil->setObjectName("lineEditIdAppareil");
        lineEditIdAppareil->setEnabled(false);
        lineEditIdAppareil->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-color: rgb(0, 0, 0);\n"
"color: black;"));

        formLayoutAppareils->setWidget(0, QFormLayout::FieldRole, lineEditIdAppareil);

        labelType = new QLabel(groupBoxFormulaireAppareils);
        labelType->setObjectName("labelType");
        labelType->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutAppareils->setWidget(1, QFormLayout::LabelRole, labelType);

        comboBoxType = new QComboBox(groupBoxFormulaireAppareils);
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        comboBoxType->setObjectName("comboBoxType");
        comboBoxType->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);\n"
"font: 10pt \"Segoe UI\";\n"
""));

        formLayoutAppareils->setWidget(1, QFormLayout::FieldRole, comboBoxType);

        labelMarque = new QLabel(groupBoxFormulaireAppareils);
        labelMarque->setObjectName("labelMarque");
        labelMarque->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutAppareils->setWidget(2, QFormLayout::LabelRole, labelMarque);

        lineEditMarque = new QLineEdit(groupBoxFormulaireAppareils);
        lineEditMarque->setObjectName("lineEditMarque");
        lineEditMarque->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayoutAppareils->setWidget(2, QFormLayout::FieldRole, lineEditMarque);

        labelModele = new QLabel(groupBoxFormulaireAppareils);
        labelModele->setObjectName("labelModele");
        labelModele->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutAppareils->setWidget(3, QFormLayout::LabelRole, labelModele);

        lineEditModele = new QLineEdit(groupBoxFormulaireAppareils);
        lineEditModele->setObjectName("lineEditModele");
        lineEditModele->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayoutAppareils->setWidget(3, QFormLayout::FieldRole, lineEditModele);

        labelNumeroSerie = new QLabel(groupBoxFormulaireAppareils);
        labelNumeroSerie->setObjectName("labelNumeroSerie");
        labelNumeroSerie->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutAppareils->setWidget(4, QFormLayout::LabelRole, labelNumeroSerie);

        lineEditNumeroSerie = new QLineEdit(groupBoxFormulaireAppareils);
        lineEditNumeroSerie->setObjectName("lineEditNumeroSerie");
        lineEditNumeroSerie->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayoutAppareils->setWidget(4, QFormLayout::FieldRole, lineEditNumeroSerie);

        labelDateAchat = new QLabel(groupBoxFormulaireAppareils);
        labelDateAchat->setObjectName("labelDateAchat");
        labelDateAchat->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutAppareils->setWidget(5, QFormLayout::LabelRole, labelDateAchat);

        dateEditAchat = new QDateEdit(groupBoxFormulaireAppareils);
        dateEditAchat->setObjectName("dateEditAchat");
        dateEditAchat->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);font: 9pt \"Segoe UI\";\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));
        dateEditAchat->setCalendarPopup(true);

        formLayoutAppareils->setWidget(5, QFormLayout::FieldRole, dateEditAchat);

        horizontalLayoutButtonsAppareils = new QHBoxLayout();
        horizontalLayoutButtonsAppareils->setObjectName("horizontalLayoutButtonsAppareils");
        btnAjouterAppareil = new QPushButton(groupBoxFormulaireAppareils);
        btnAjouterAppareil->setObjectName("btnAjouterAppareil");
        btnAjouterAppareil->setStyleSheet(QString::fromUtf8("background-color: #28A745;\n"
"font: 900 12pt \"Swis721 BlkCn BT\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayoutButtonsAppareils->addWidget(btnAjouterAppareil);

        btnModifierAppareil = new QPushButton(groupBoxFormulaireAppareils);
        btnModifierAppareil->setObjectName("btnModifierAppareil");
        btnModifierAppareil->setStyleSheet(QString::fromUtf8("background-color: #007BFF;\n"
"color: rgb(255, 255, 255);\n"
"font: 900 12pt \"Swis721 BlkCn BT\";"));

        horizontalLayoutButtonsAppareils->addWidget(btnModifierAppareil);

        btnSupprimerAppareil = new QPushButton(groupBoxFormulaireAppareils);
        btnSupprimerAppareil->setObjectName("btnSupprimerAppareil");
        btnSupprimerAppareil->setStyleSheet(QString::fromUtf8("background-color: #DC3545;\n"
"font: 900 12pt \"Swis721 BlkCn BT\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayoutButtonsAppareils->addWidget(btnSupprimerAppareil);


        formLayoutAppareils->setLayout(6, QFormLayout::SpanningRole, horizontalLayoutButtonsAppareils);


        horizontalLayoutAppareils->addWidget(groupBoxFormulaireAppareils);

        groupBoxListeAppareils = new QGroupBox(tabAppareils);
        groupBoxListeAppareils->setObjectName("groupBoxListeAppareils");
        groupBoxListeAppareils->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Bahnschrift\";\n"
"color: rgb(53, 185, 95);\n"
"border-color: #35b95f;\n"
"background-color: #2c3147;"));
        verticalLayoutListeAppareils = new QVBoxLayout(groupBoxListeAppareils);
        verticalLayoutListeAppareils->setObjectName("verticalLayoutListeAppareils");
        horizontalLayoutRechercheAppareils = new QHBoxLayout();
        horizontalLayoutRechercheAppareils->setObjectName("horizontalLayoutRechercheAppareils");
        labelRechercheAppareil = new QLabel(groupBoxListeAppareils);
        labelRechercheAppareil->setObjectName("labelRechercheAppareil");
        labelRechercheAppareil->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayoutRechercheAppareils->addWidget(labelRechercheAppareil);

        comboBoxCritereAppareil = new QComboBox(groupBoxListeAppareils);
        comboBoxCritereAppareil->addItem(QString());
        comboBoxCritereAppareil->setObjectName("comboBoxCritereAppareil");
        comboBoxCritereAppareil->setStyleSheet(QString::fromUtf8("font: 9pt \"Segoe UI\";\n"
"background-color: rgb(255, 255, 255);\n"
"color: black;"));

        horizontalLayoutRechercheAppareils->addWidget(comboBoxCritereAppareil);

        btnRechercherAppareil = new QPushButton(groupBoxListeAppareils);
        btnRechercherAppareil->setObjectName("btnRechercherAppareil");
        btnRechercherAppareil->setStyleSheet(QString::fromUtf8("font: 900 12pt \"Swis721 BlkCn BT\";\n"
"background-color: #007BFF;\n"
"color: white;"));

        horizontalLayoutRechercheAppareils->addWidget(btnRechercherAppareil);

        btnReinitialiserAppareil = new QPushButton(groupBoxListeAppareils);
        btnReinitialiserAppareil->setObjectName("btnReinitialiserAppareil");
        btnReinitialiserAppareil->setStyleSheet(QString::fromUtf8("background-color: #6C757D;\n"
"color: rgb(255, 255, 255);\n"
"font: 900 12pt \"Swis721 BlkCn BT\";"));

        horizontalLayoutRechercheAppareils->addWidget(btnReinitialiserAppareil);


        verticalLayoutListeAppareils->addLayout(horizontalLayoutRechercheAppareils);

        tableViewAppareils = new QTableView(groupBoxListeAppareils);
        tableViewAppareils->setObjectName("tableViewAppareils");
        tableViewAppareils->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tableViewAppareils->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tableViewAppareils->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        tableViewAppareils->setSortingEnabled(true);

        verticalLayoutListeAppareils->addWidget(tableViewAppareils);

        horizontalLayoutExportAppareils = new QHBoxLayout();
        horizontalLayoutExportAppareils->setObjectName("horizontalLayoutExportAppareils");
        labelTotalAppareils = new QLabel(groupBoxListeAppareils);
        labelTotalAppareils->setObjectName("labelTotalAppareils");
        labelTotalAppareils->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayoutExportAppareils->addWidget(labelTotalAppareils);

        horizontalSpacerAppareil = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutExportAppareils->addItem(horizontalSpacerAppareil);

        btnExporterPDFAppareil = new QPushButton(groupBoxListeAppareils);
        btnExporterPDFAppareil->setObjectName("btnExporterPDFAppareil");
        btnExporterPDFAppareil->setStyleSheet(QString::fromUtf8("background-color: #DC3545;\n"
"color: rgb(255, 255, 255);\n"
"font: 900 12pt \"Swis721 BlkCn BT\";"));

        horizontalLayoutExportAppareils->addWidget(btnExporterPDFAppareil);

        btnExporterExcelAppareil = new QPushButton(groupBoxListeAppareils);
        btnExporterExcelAppareil->setObjectName("btnExporterExcelAppareil");
        btnExporterExcelAppareil->setStyleSheet(QString::fromUtf8("background-color: #28A745;\n"
"color: rgb(255, 255, 255);\n"
"font: 900 12pt \"Swis721 BlkCn BT\";"));

        horizontalLayoutExportAppareils->addWidget(btnExporterExcelAppareil);


        verticalLayoutListeAppareils->addLayout(horizontalLayoutExportAppareils);


        horizontalLayoutAppareils->addWidget(groupBoxListeAppareils);

        tabWidget->addTab(tabAppareils, QString());
        tabReparations = new QWidget();
        tabReparations->setObjectName("tabReparations");
        horizontalLayoutReparations = new QHBoxLayout(tabReparations);
        horizontalLayoutReparations->setObjectName("horizontalLayoutReparations");
        groupBoxFormulaireReparations = new QGroupBox(tabReparations);
        groupBoxFormulaireReparations->setObjectName("groupBoxFormulaireReparations");
        groupBoxFormulaireReparations->setMinimumSize(QSize(350, 0));
        groupBoxFormulaireReparations->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Bahnschrift\";\n"
"color: rgb(53, 185, 95);\n"
"border-color: rgb(53, 185, 95);\n"
"background-color: #2c3147;"));
        formLayoutReparations = new QFormLayout(groupBoxFormulaireReparations);
        formLayoutReparations->setObjectName("formLayoutReparations");
        labelIdReparation = new QLabel(groupBoxFormulaireReparations);
        labelIdReparation->setObjectName("labelIdReparation");
        labelIdReparation->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutReparations->setWidget(0, QFormLayout::LabelRole, labelIdReparation);

        lineEditIdReparation = new QLineEdit(groupBoxFormulaireReparations);
        lineEditIdReparation->setObjectName("lineEditIdReparation");
        lineEditIdReparation->setEnabled(false);
        lineEditIdReparation->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-color: rgb(0, 0, 0);\n"
"color: black;"));

        formLayoutReparations->setWidget(0, QFormLayout::FieldRole, lineEditIdReparation);

        labelAppareilReparation = new QLabel(groupBoxFormulaireReparations);
        labelAppareilReparation->setObjectName("labelAppareilReparation");
        labelAppareilReparation->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutReparations->setWidget(1, QFormLayout::LabelRole, labelAppareilReparation);

        comboBoxAppareilReparation = new QComboBox(groupBoxFormulaireReparations);
        comboBoxAppareilReparation->setObjectName("comboBoxAppareilReparation");
        comboBoxAppareilReparation->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayoutReparations->setWidget(1, QFormLayout::FieldRole, comboBoxAppareilReparation);

        labelDateDepot = new QLabel(groupBoxFormulaireReparations);
        labelDateDepot->setObjectName("labelDateDepot");
        labelDateDepot->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutReparations->setWidget(2, QFormLayout::LabelRole, labelDateDepot);

        dateEditDepot = new QDateEdit(groupBoxFormulaireReparations);
        dateEditDepot->setObjectName("dateEditDepot");
        dateEditDepot->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);font: 9pt \"Segoe UI\";\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));
        dateEditDepot->setCalendarPopup(true);

        formLayoutReparations->setWidget(2, QFormLayout::FieldRole, dateEditDepot);

        labelDateRetourPrevue = new QLabel(groupBoxFormulaireReparations);
        labelDateRetourPrevue->setObjectName("labelDateRetourPrevue");
        labelDateRetourPrevue->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutReparations->setWidget(3, QFormLayout::LabelRole, labelDateRetourPrevue);

        dateEditRetourPrevue = new QDateEdit(groupBoxFormulaireReparations);
        dateEditRetourPrevue->setObjectName("dateEditRetourPrevue");
        dateEditRetourPrevue->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);font: 9pt \"Segoe UI\";\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));
        dateEditRetourPrevue->setCalendarPopup(true);

        formLayoutReparations->setWidget(3, QFormLayout::FieldRole, dateEditRetourPrevue);

        labelPanne = new QLabel(groupBoxFormulaireReparations);
        labelPanne->setObjectName("labelPanne");
        labelPanne->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutReparations->setWidget(4, QFormLayout::LabelRole, labelPanne);

        textEditPanne = new QTextEdit(groupBoxFormulaireReparations);
        textEditPanne->setObjectName("textEditPanne");
        textEditPanne->setMaximumSize(QSize(16777215, 80));
        textEditPanne->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayoutReparations->setWidget(4, QFormLayout::FieldRole, textEditPanne);

        labelStatutReparation = new QLabel(groupBoxFormulaireReparations);
        labelStatutReparation->setObjectName("labelStatutReparation");
        labelStatutReparation->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutReparations->setWidget(5, QFormLayout::LabelRole, labelStatutReparation);

        comboBoxStatutReparation = new QComboBox(groupBoxFormulaireReparations);
        comboBoxStatutReparation->addItem(QString());
        comboBoxStatutReparation->addItem(QString());
        comboBoxStatutReparation->addItem(QString());
        comboBoxStatutReparation->addItem(QString());
        comboBoxStatutReparation->setObjectName("comboBoxStatutReparation");
        comboBoxStatutReparation->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"font: 10pt \"Segoe UI\";\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayoutReparations->setWidget(5, QFormLayout::FieldRole, comboBoxStatutReparation);

        labelCout = new QLabel(groupBoxFormulaireReparations);
        labelCout->setObjectName("labelCout");
        labelCout->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutReparations->setWidget(6, QFormLayout::LabelRole, labelCout);

        lineEditCout = new QLineEdit(groupBoxFormulaireReparations);
        lineEditCout->setObjectName("lineEditCout");
        lineEditCout->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayoutReparations->setWidget(6, QFormLayout::FieldRole, lineEditCout);

        horizontalLayoutButtonsReparations = new QHBoxLayout();
        horizontalLayoutButtonsReparations->setObjectName("horizontalLayoutButtonsReparations");
        btnAjouterReparation = new QPushButton(groupBoxFormulaireReparations);
        btnAjouterReparation->setObjectName("btnAjouterReparation");
        btnAjouterReparation->setStyleSheet(QString::fromUtf8("background-color: #28A745;\n"
"font: 900 12pt \"Swis721 BlkCn BT\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayoutButtonsReparations->addWidget(btnAjouterReparation);

        btnModifierReparation = new QPushButton(groupBoxFormulaireReparations);
        btnModifierReparation->setObjectName("btnModifierReparation");
        btnModifierReparation->setStyleSheet(QString::fromUtf8("background-color: #007BFF;\n"
"color: rgb(255, 255, 255);\n"
"font: 900 12pt \"Swis721 BlkCn BT\";"));

        horizontalLayoutButtonsReparations->addWidget(btnModifierReparation);

        btnSupprimerReparation = new QPushButton(groupBoxFormulaireReparations);
        btnSupprimerReparation->setObjectName("btnSupprimerReparation");
        btnSupprimerReparation->setStyleSheet(QString::fromUtf8("background-color: #DC3545;\n"
"font: 900 12pt \"Swis721 BlkCn BT\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayoutButtonsReparations->addWidget(btnSupprimerReparation);


        formLayoutReparations->setLayout(7, QFormLayout::SpanningRole, horizontalLayoutButtonsReparations);


        horizontalLayoutReparations->addWidget(groupBoxFormulaireReparations);

        groupBoxListeReparations = new QGroupBox(tabReparations);
        groupBoxListeReparations->setObjectName("groupBoxListeReparations");
        groupBoxListeReparations->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Bahnschrift\";\n"
"color: rgb(53, 185, 95);\n"
"border-color: #35b95f;\n"
"background-color: #2c3147;"));
        verticalLayoutListeReparations = new QVBoxLayout(groupBoxListeReparations);
        verticalLayoutListeReparations->setObjectName("verticalLayoutListeReparations");
        horizontalLayoutRechercheReparations = new QHBoxLayout();
        horizontalLayoutRechercheReparations->setObjectName("horizontalLayoutRechercheReparations");
        labelRechercheReparation = new QLabel(groupBoxListeReparations);
        labelRechercheReparation->setObjectName("labelRechercheReparation");
        labelRechercheReparation->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayoutRechercheReparations->addWidget(labelRechercheReparation);

        comboBoxCritereReparation = new QComboBox(groupBoxListeReparations);
        comboBoxCritereReparation->addItem(QString());
        comboBoxCritereReparation->addItem(QString());
        comboBoxCritereReparation->addItem(QString());
        comboBoxCritereReparation->setObjectName("comboBoxCritereReparation");
        comboBoxCritereReparation->setStyleSheet(QString::fromUtf8("font: 9pt \"Segoe UI\";\n"
"background-color: rgb(255, 255, 255);\n"
"color: black;"));

        horizontalLayoutRechercheReparations->addWidget(comboBoxCritereReparation);

        lineEditRechercheReparation = new QLineEdit(groupBoxListeReparations);
        lineEditRechercheReparation->setObjectName("lineEditRechercheReparation");
        lineEditRechercheReparation->setStyleSheet(QString::fromUtf8("font: 9pt \"Segoe UI\";\n"
"background-color: rgb(255, 255, 255);\n"
"color: black;"));

        horizontalLayoutRechercheReparations->addWidget(lineEditRechercheReparation);

        btnRechercherReparation = new QPushButton(groupBoxListeReparations);
        btnRechercherReparation->setObjectName("btnRechercherReparation");
        btnRechercherReparation->setStyleSheet(QString::fromUtf8("font: 900 12pt \"Swis721 BlkCn BT\";\n"
"background-color: #007BFF;\n"
"color: white;"));

        horizontalLayoutRechercheReparations->addWidget(btnRechercherReparation);

        btnReinitialiserReparation = new QPushButton(groupBoxListeReparations);
        btnReinitialiserReparation->setObjectName("btnReinitialiserReparation");
        btnReinitialiserReparation->setStyleSheet(QString::fromUtf8("background-color: #6C757D;\n"
"color: rgb(255, 255, 255);\n"
"font: 900 12pt \"Swis721 BlkCn BT\";"));

        horizontalLayoutRechercheReparations->addWidget(btnReinitialiserReparation);


        verticalLayoutListeReparations->addLayout(horizontalLayoutRechercheReparations);

        tableViewReparationsListe = new QTableView(groupBoxListeReparations);
        tableViewReparationsListe->setObjectName("tableViewReparationsListe");
        tableViewReparationsListe->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tableViewReparationsListe->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tableViewReparationsListe->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        tableViewReparationsListe->setSortingEnabled(true);

        verticalLayoutListeReparations->addWidget(tableViewReparationsListe);

        horizontalLayoutExportReparations = new QHBoxLayout();
        horizontalLayoutExportReparations->setObjectName("horizontalLayoutExportReparations");
        labelTotalReparations = new QLabel(groupBoxListeReparations);
        labelTotalReparations->setObjectName("labelTotalReparations");
        labelTotalReparations->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayoutExportReparations->addWidget(labelTotalReparations);

        horizontalSpacerReparation = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutExportReparations->addItem(horizontalSpacerReparation);

        btnExporterPDFReparation = new QPushButton(groupBoxListeReparations);
        btnExporterPDFReparation->setObjectName("btnExporterPDFReparation");
        btnExporterPDFReparation->setStyleSheet(QString::fromUtf8("background-color: #DC3545;\n"
"color: rgb(255, 255, 255);\n"
"font: 900 12pt \"Swis721 BlkCn BT\";"));

        horizontalLayoutExportReparations->addWidget(btnExporterPDFReparation);

        btnExporterExcelReparation = new QPushButton(groupBoxListeReparations);
        btnExporterExcelReparation->setObjectName("btnExporterExcelReparation");
        btnExporterExcelReparation->setStyleSheet(QString::fromUtf8("background-color: #28A745;\n"
"color: rgb(255, 255, 255);\n"
"font: 900 12pt \"Swis721 BlkCn BT\";"));

        horizontalLayoutExportReparations->addWidget(btnExporterExcelReparation);


        verticalLayoutListeReparations->addLayout(horizontalLayoutExportReparations);


        horizontalLayoutReparations->addWidget(groupBoxListeReparations);

        tabWidget->addTab(tabReparations, QString());
        tabStatistiques = new QWidget();
        tabStatistiques->setObjectName("tabStatistiques");
        verticalLayoutStatistiques = new QVBoxLayout(tabStatistiques);
        verticalLayoutStatistiques->setObjectName("verticalLayoutStatistiques");
        horizontalLayoutStatsTop = new QHBoxLayout();
        horizontalLayoutStatsTop->setObjectName("horizontalLayoutStatsTop");
        groupBoxStatsGenerales = new QGroupBox(tabStatistiques);
        groupBoxStatsGenerales->setObjectName("groupBoxStatsGenerales");
        groupBoxStatsGenerales->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Bahnschrift\";\n"
"color: rgb(53, 185, 95);\n"
"border-color: rgb(53, 185, 95);\n"
"background-color: #2c3147;"));
        gridLayoutStats = new QGridLayout(groupBoxStatsGenerales);
        gridLayoutStats->setObjectName("gridLayoutStats");
        labelStatsClients = new QLabel(groupBoxStatsGenerales);
        labelStatsClients->setObjectName("labelStatsClients");
        labelStatsClients->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        gridLayoutStats->addWidget(labelStatsClients, 0, 0, 1, 1);

        labelStatsClientsValue = new QLabel(groupBoxStatsGenerales);
        labelStatsClientsValue->setObjectName("labelStatsClientsValue");
        labelStatsClientsValue->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        gridLayoutStats->addWidget(labelStatsClientsValue, 0, 1, 1, 1);

        labelStatsAppareils = new QLabel(groupBoxStatsGenerales);
        labelStatsAppareils->setObjectName("labelStatsAppareils");
        labelStatsAppareils->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        gridLayoutStats->addWidget(labelStatsAppareils, 1, 0, 1, 1);

        labelStatsAppareilsValue = new QLabel(groupBoxStatsGenerales);
        labelStatsAppareilsValue->setObjectName("labelStatsAppareilsValue");
        labelStatsAppareilsValue->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        gridLayoutStats->addWidget(labelStatsAppareilsValue, 1, 1, 1, 1);

        labelStatsReparations = new QLabel(groupBoxStatsGenerales);
        labelStatsReparations->setObjectName("labelStatsReparations");
        labelStatsReparations->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        gridLayoutStats->addWidget(labelStatsReparations, 2, 0, 1, 1);

        labelStatsReparationsValue = new QLabel(groupBoxStatsGenerales);
        labelStatsReparationsValue->setObjectName("labelStatsReparationsValue");
        labelStatsReparationsValue->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        gridLayoutStats->addWidget(labelStatsReparationsValue, 2, 1, 1, 1);

        labelStatsCA = new QLabel(groupBoxStatsGenerales);
        labelStatsCA->setObjectName("labelStatsCA");
        labelStatsCA->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        gridLayoutStats->addWidget(labelStatsCA, 3, 0, 1, 1);

        labelStatsCAValue = new QLabel(groupBoxStatsGenerales);
        labelStatsCAValue->setObjectName("labelStatsCAValue");
        labelStatsCAValue->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        gridLayoutStats->addWidget(labelStatsCAValue, 3, 1, 1, 1);


        horizontalLayoutStatsTop->addWidget(groupBoxStatsGenerales);

        groupBoxFiltres = new QGroupBox(tabStatistiques);
        groupBoxFiltres->setObjectName("groupBoxFiltres");
        groupBoxFiltres->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Bahnschrift\";\n"
"color: rgb(53, 185, 95);\n"
"border-color: rgb(53, 185, 95);\n"
"background-color: #2c3147;"));
        formLayoutFiltres = new QFormLayout(groupBoxFiltres);
        formLayoutFiltres->setObjectName("formLayoutFiltres");
        labelPeriode = new QLabel(groupBoxFiltres);
        labelPeriode->setObjectName("labelPeriode");
        labelPeriode->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutFiltres->setWidget(0, QFormLayout::LabelRole, labelPeriode);

        comboBoxPeriode = new QComboBox(groupBoxFiltres);
        comboBoxPeriode->addItem(QString());
        comboBoxPeriode->addItem(QString());
        comboBoxPeriode->addItem(QString());
        comboBoxPeriode->addItem(QString());
        comboBoxPeriode->setObjectName("comboBoxPeriode");
        comboBoxPeriode->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);\n"
"font: 10pt \"Segoe UI\";\n"
""));

        formLayoutFiltres->setWidget(0, QFormLayout::FieldRole, comboBoxPeriode);

        labelDateDebut = new QLabel(groupBoxFiltres);
        labelDateDebut->setObjectName("labelDateDebut");
        labelDateDebut->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutFiltres->setWidget(1, QFormLayout::LabelRole, labelDateDebut);

        dateEditDebut = new QDateEdit(groupBoxFiltres);
        dateEditDebut->setObjectName("dateEditDebut");
        dateEditDebut->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);font: 9pt \"Segoe UI\";\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));
        dateEditDebut->setCalendarPopup(true);

        formLayoutFiltres->setWidget(1, QFormLayout::FieldRole, dateEditDebut);

        labelDateFin = new QLabel(groupBoxFiltres);
        labelDateFin->setObjectName("labelDateFin");
        labelDateFin->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayoutFiltres->setWidget(2, QFormLayout::LabelRole, labelDateFin);

        dateEditFin = new QDateEdit(groupBoxFiltres);
        dateEditFin->setObjectName("dateEditFin");
        dateEditFin->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);font: 9pt \"Segoe UI\";\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));
        dateEditFin->setCalendarPopup(true);

        formLayoutFiltres->setWidget(2, QFormLayout::FieldRole, dateEditFin);

        btnGenererRapport = new QPushButton(groupBoxFiltres);
        btnGenererRapport->setObjectName("btnGenererRapport");
        btnGenererRapport->setStyleSheet(QString::fromUtf8("background-color: #007BFF;\n"
"color: rgb(255, 255, 255);\n"
"font: 900 12pt \"Swis721 BlkCn BT\";"));

        formLayoutFiltres->setWidget(3, QFormLayout::SpanningRole, btnGenererRapport);


        horizontalLayoutStatsTop->addWidget(groupBoxFiltres);


        verticalLayoutStatistiques->addLayout(horizontalLayoutStatsTop);

        groupBoxGraphiques = new QGroupBox(tabStatistiques);
        groupBoxGraphiques->setObjectName("groupBoxGraphiques");
        groupBoxGraphiques->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Bahnschrift\";\n"
"color: rgb(53, 185, 95);\n"
"border-color: #35b95f;\n"
"background-color: #2c3147;"));
        horizontalLayoutGraphiques = new QHBoxLayout(groupBoxGraphiques);
        horizontalLayoutGraphiques->setObjectName("horizontalLayoutGraphiques");
        labelGraphiquePlaceholder = new QLabel(groupBoxGraphiques);
        labelGraphiquePlaceholder->setObjectName("labelGraphiquePlaceholder");
        labelGraphiquePlaceholder->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border: 2px solid #35b95f;\n"
"border-radius: 8px;"));
        labelGraphiquePlaceholder->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayoutGraphiques->addWidget(labelGraphiquePlaceholder);

        labelGraphique2Placeholder = new QLabel(groupBoxGraphiques);
        labelGraphique2Placeholder->setObjectName("labelGraphique2Placeholder");
        labelGraphique2Placeholder->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border: 2px solid #35b95f;\n"
"border-radius: 8px;"));
        labelGraphique2Placeholder->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayoutGraphiques->addWidget(labelGraphique2Placeholder);


        verticalLayoutStatistiques->addWidget(groupBoxGraphiques);

        tabWidget->addTab(tabStatistiques, QString());

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

        tabWidget->setCurrentIndex(3);
        tabWidget_2->setCurrentIndex(0);


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
        labelClientTitle->setText(QCoreApplication::translate("MainWindow", "Total Clients", nullptr));
        labelClientCount->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        labelClientSub->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        labelAttenteTitle->setText(QCoreApplication::translate("MainWindow", "R\303\251parations en attente", nullptr));
        labelAttenteCount->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        labelCAAbbr->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        labelCoursTitle->setText(QCoreApplication::translate("MainWindow", "R\303\251parations en cours", nullptr));
        labelCoursCount->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        labelCoursSub->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        groupBoxReparations->setTitle(QCoreApplication::translate("MainWindow", "R\303\251parations en cours", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabDashboard), QCoreApplication::translate("MainWindow", "Tableau de Bord", nullptr));
        groupBoxFormulaireClients->setTitle(QCoreApplication::translate("MainWindow", "Formulaire Client", nullptr));
        labelIdClient->setText(QCoreApplication::translate("MainWindow", "ID:", nullptr));
        labelNom->setText(QCoreApplication::translate("MainWindow", "Nom :", nullptr));
        labelPrenom->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom :", nullptr));
        labelEmail->setText(QCoreApplication::translate("MainWindow", "Email :", nullptr));
        labelTelephone->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone:", nullptr));
        labelAdresse->setText(QCoreApplication::translate("MainWindow", "Adresse:", nullptr));
        labelVille->setText(QCoreApplication::translate("MainWindow", "Ville:", nullptr));
        labelDateInscription->setText(QCoreApplication::translate("MainWindow", "Date Inscription:", nullptr));
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
        btnReinitialiserClient->setText(QCoreApplication::translate("MainWindow", "R\303\251initialiser", nullptr));
        labelTotalClients->setText(QCoreApplication::translate("MainWindow", "Total: 0 clients", nullptr));
        btnExporterPDFClient->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        btnExporterExcelClient->setText(QCoreApplication::translate("MainWindow", "Exporter Excel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabClients), QCoreApplication::translate("MainWindow", "Gestion Clients", nullptr));
        label_5->setText(QString());
        groupBoxFormulaire->setTitle(QCoreApplication::translate("MainWindow", "Formulaire Appareil", nullptr));
        labelId->setText(QCoreApplication::translate("MainWindow", "cin", nullptr));
        labelType_2->setText(QCoreApplication::translate("MainWindow", "nom", nullptr));
        labelMarque_2->setText(QCoreApplication::translate("MainWindow", "prenom", nullptr));
        labelModele_2->setText(QCoreApplication::translate("MainWindow", "num de tel", nullptr));
        labelNumeroSerie_2->setText(QCoreApplication::translate("MainWindow", "email", nullptr));
        btnAjouter->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnModifier->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        btnSupprimer->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        groupBoxListe->setTitle(QCoreApplication::translate("MainWindow", "Liste des Appareils", nullptr));
        labelRecherche->setText(QCoreApplication::translate("MainWindow", "Rechercher par:", nullptr));
        comboBoxCritere->setItemText(0, QCoreApplication::translate("MainWindow", "nom", nullptr));

        btnRechercher->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        btnReinitialiser->setText(QCoreApplication::translate("MainWindow", "tri par nom", nullptr));
        btnExporterPDF->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tabGestion), QCoreApplication::translate("MainWindow", "Gestion d'empolye", nullptr));
        groupBoxStats->setTitle(QCoreApplication::translate("MainWindow", "Statistiques des Appareils", nullptr));
        labelGraphTitle->setText(QString());
        labelDetailsTitle->setText(QCoreApplication::translate("MainWindow", "D\303\251tails statistiques", nullptr));
        btnGenererStats->setText(QCoreApplication::translate("MainWindow", "G\303\251n\303\251rer Statistiques", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tabStatistiques_2), QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Gestion_emply\303\251e", nullptr));
        groupBoxFormulaireAppareils->setTitle(QCoreApplication::translate("MainWindow", "Formulaire Appareil", nullptr));
        labelIdAppareil->setText(QCoreApplication::translate("MainWindow", "ID:", nullptr));
        labelType->setText(QCoreApplication::translate("MainWindow", "Type :", nullptr));
        comboBoxType->setItemText(0, QCoreApplication::translate("MainWindow", "Smartphone", nullptr));
        comboBoxType->setItemText(1, QCoreApplication::translate("MainWindow", "Ordinateur Portable", nullptr));
        comboBoxType->setItemText(2, QCoreApplication::translate("MainWindow", "Tablette", nullptr));
        comboBoxType->setItemText(3, QCoreApplication::translate("MainWindow", "Appareil IoT", nullptr));
        comboBoxType->setItemText(4, QCoreApplication::translate("MainWindow", "Autre", nullptr));

        labelMarque->setText(QCoreApplication::translate("MainWindow", "Marque :", nullptr));
        labelModele->setText(QCoreApplication::translate("MainWindow", "Mod\303\250le :", nullptr));
        labelNumeroSerie->setText(QCoreApplication::translate("MainWindow", "Num\303\251ro S\303\251rie:", nullptr));
        labelDateAchat->setText(QCoreApplication::translate("MainWindow", "Date Achat:", nullptr));
        btnAjouterAppareil->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnModifierAppareil->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        btnSupprimerAppareil->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        groupBoxListeAppareils->setTitle(QCoreApplication::translate("MainWindow", "Liste des Appareils", nullptr));
        labelRechercheAppareil->setText(QCoreApplication::translate("MainWindow", "Rechercher par:", nullptr));
        comboBoxCritereAppareil->setItemText(0, QCoreApplication::translate("MainWindow", "Num\303\251ro S\303\251rie", nullptr));

        btnRechercherAppareil->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        btnReinitialiserAppareil->setText(QCoreApplication::translate("MainWindow", "R\303\251initialiser", nullptr));
        labelTotalAppareils->setText(QCoreApplication::translate("MainWindow", "Total: 0 appareils", nullptr));
        btnExporterPDFAppareil->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        btnExporterExcelAppareil->setText(QCoreApplication::translate("MainWindow", "Exporter Excel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabAppareils), QCoreApplication::translate("MainWindow", "Gestion Appareils", nullptr));
        groupBoxFormulaireReparations->setTitle(QCoreApplication::translate("MainWindow", "Formulaire R\303\251paration", nullptr));
        labelIdReparation->setText(QCoreApplication::translate("MainWindow", "CIN client :", nullptr));
        labelAppareilReparation->setText(QCoreApplication::translate("MainWindow", "Matricule Appareil :", nullptr));
        labelDateDepot->setText(QCoreApplication::translate("MainWindow", "Date D\303\251p\303\264t :", nullptr));
        labelDateRetourPrevue->setText(QCoreApplication::translate("MainWindow", "Date Retour Pr\303\251vue:", nullptr));
        labelPanne->setText(QCoreApplication::translate("MainWindow", "Panne:", nullptr));
        labelStatutReparation->setText(QCoreApplication::translate("MainWindow", "Statut:", nullptr));
        comboBoxStatutReparation->setItemText(0, QCoreApplication::translate("MainWindow", "En attente", nullptr));
        comboBoxStatutReparation->setItemText(1, QCoreApplication::translate("MainWindow", "En cours", nullptr));
        comboBoxStatutReparation->setItemText(2, QCoreApplication::translate("MainWindow", "Termin\303\251e", nullptr));
        comboBoxStatutReparation->setItemText(3, QCoreApplication::translate("MainWindow", "Annul\303\251e", nullptr));

        labelCout->setText(QCoreApplication::translate("MainWindow", "Co\303\273t :", nullptr));
        btnAjouterReparation->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnModifierReparation->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        btnSupprimerReparation->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        groupBoxListeReparations->setTitle(QCoreApplication::translate("MainWindow", "Liste des R\303\251parations", nullptr));
        labelRechercheReparation->setText(QCoreApplication::translate("MainWindow", "Rechercher par:", nullptr));
        comboBoxCritereReparation->setItemText(0, QCoreApplication::translate("MainWindow", "Appareil", nullptr));
        comboBoxCritereReparation->setItemText(1, QCoreApplication::translate("MainWindow", "Statut", nullptr));
        comboBoxCritereReparation->setItemText(2, QCoreApplication::translate("MainWindow", "Date", nullptr));

        lineEditRechercheReparation->setPlaceholderText(QCoreApplication::translate("MainWindow", "Terme de recherche...", nullptr));
        btnRechercherReparation->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        btnReinitialiserReparation->setText(QCoreApplication::translate("MainWindow", "R\303\251initialiser", nullptr));
        labelTotalReparations->setText(QCoreApplication::translate("MainWindow", "Total: 0 r\303\251parations", nullptr));
        btnExporterPDFReparation->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        btnExporterExcelReparation->setText(QCoreApplication::translate("MainWindow", "Exporter Excel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabReparations), QCoreApplication::translate("MainWindow", "Gestion R\303\251parations", nullptr));
        groupBoxStatsGenerales->setTitle(QCoreApplication::translate("MainWindow", "Statistiques G\303\251n\303\251rales", nullptr));
        labelStatsClients->setText(QCoreApplication::translate("MainWindow", "Total Clients:", nullptr));
        labelStatsClientsValue->setText(QCoreApplication::translate("MainWindow", "....", nullptr));
        labelStatsAppareils->setText(QCoreApplication::translate("MainWindow", "Total Appareils:", nullptr));
        labelStatsAppareilsValue->setText(QCoreApplication::translate("MainWindow", "....", nullptr));
        labelStatsReparations->setText(QCoreApplication::translate("MainWindow", "R\303\251parations Termin\303\251es:", nullptr));
        labelStatsReparationsValue->setText(QCoreApplication::translate("MainWindow", ".....", nullptr));
        labelStatsCA->setText(QCoreApplication::translate("MainWindow", "Chiffre d'Affaires:", nullptr));
        labelStatsCAValue->setText(QCoreApplication::translate("MainWindow", ".....", nullptr));
        groupBoxFiltres->setTitle(QCoreApplication::translate("MainWindow", "Filtres", nullptr));
        labelPeriode->setText(QCoreApplication::translate("MainWindow", "P\303\251riode:", nullptr));
        comboBoxPeriode->setItemText(0, QCoreApplication::translate("MainWindow", "Ce mois", nullptr));
        comboBoxPeriode->setItemText(1, QCoreApplication::translate("MainWindow", "Ce trimestre", nullptr));
        comboBoxPeriode->setItemText(2, QCoreApplication::translate("MainWindow", "Cette ann\303\251e", nullptr));
        comboBoxPeriode->setItemText(3, QCoreApplication::translate("MainWindow", "Personnalis\303\251", nullptr));

        labelDateDebut->setText(QCoreApplication::translate("MainWindow", "Date D\303\251but:", nullptr));
        labelDateFin->setText(QCoreApplication::translate("MainWindow", "Date Fin:", nullptr));
        btnGenererRapport->setText(QCoreApplication::translate("MainWindow", "G\303\251n\303\251rer Rapport", nullptr));
        groupBoxGraphiques->setTitle(QCoreApplication::translate("MainWindow", "Graphiques", nullptr));
        labelGraphiquePlaceholder->setText(QCoreApplication::translate("MainWindow", "Graphique des r\303\251parations par mois", nullptr));
        labelGraphique2Placeholder->setText(QCoreApplication::translate("MainWindow", "R\303\251partition par type d'appareil", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabStatistiques), QCoreApplication::translate("MainWindow", "Statistiques & Rapports", nullptr));
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
