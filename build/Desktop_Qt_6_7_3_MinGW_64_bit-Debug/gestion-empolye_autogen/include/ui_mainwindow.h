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
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
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
    QWidget *centralwidget;
    QLabel *label_5;
    QTabWidget *tabWidget;
    QWidget *tabGestion;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBoxFormulaire;
    QFormLayout *formLayout;
    QLabel *labelId;
    QLabel *labelType;
    QLabel *labelMarque;
    QLineEdit *lineEditMarque;
    QLabel *labelModele;
    QLineEdit *lineEditModele;
    QLabel *labelNumeroSerie;
    QLineEdit *lineEditNumeroSerie;
    QHBoxLayout *horizontalLayoutButtons;
    QPushButton *btnAjouter;
    QPushButton *btnModifier;
    QPushButton *btnSupprimer;
    QHBoxLayout *horizontalLayoutQR;
    QLineEdit *lineEditMarque_3;
    QLineEdit *lineEditId;
    QGroupBox *groupBoxListe;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayoutRecherche;
    QLabel *labelRecherche;
    QComboBox *comboBoxCritere;
    QPushButton *btnRechercher;
    QPushButton *btnReinitialiser;
    QTableView *tableViewAppareils;
    QHBoxLayout *horizontalLayoutExport;
    QPushButton *btnExporterPDF;
    QWidget *tabStatistiques;
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
    QLabel *labelTitle;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1398, 828);
        MainWindow->setWindowOpacity(1.000000000000000);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: white;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: navy;  /* fond bleu marine (#000080) */\n"
"    color: white;            /* texte blanc */\n"
"    border: 1px solid black; /* bordure noire */\n"
"    border-radius: 5px;      /* coins arrondis */\n"
"    padding: 5px;            /* espace interne */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #000066; /* bleu marine plus fonc\303\251 au survol */\n"
"}\n"
"QLabel {\n"
"    font-family: \"Arial\";   /* police */\n"
"    font-size: 16px;        /* taille en pixels */\n"
"    font-weight: bold;      /* gras si besoin */\n"
"    font-style: italic;     /* italique si besoin */\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #000033; /* bleu marine tr\303\250s fonc\303\251 quand cliqu\303\251 */\n"
"}\n"
"\n"
"QLabel {\n"
"    font-family: \"Arial\";   /* famille de la police */\n"
"    font-size: 16px;        /* taille en pixels */\n"
"    font-weight: bold;      /"
                        "* gras */\n"
"    font-style: italic;     /* italique */\n"
"}\n"
"QLabel {\n"
"    font-family: \"Arial\";\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"    color: white;           /* texte blanc */\n"
"}\n"
"QPushButton {\n"
"    font-family: \"Arial\";   /* police */\n"
"    font-size: 14px;        /* taille */\n"
"    font-weight: bold;      /* gras */\n"
"    font-style: italic;     /* italique */\n"
"    color: white;           /* texte blanc */\n"
"    background-color: navy; /* fond bleu marine */\n"
"}\n"
"QTabBar::tab {\n"
"    font-family: \"Arial\";   /* police */\n"
"    font-size: 14px;        /* taille */\n"
"    font-weight: bold;      /* gras */\n"
"    font-style: italic;     /* italique */\n"
"    color: white;           /* texte blanc */\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    font-weight: bold;\n"
"    color: white;\n"
"}\n"
"QPushButton {\n"
"    background-color: #00008B;  /* bleu fonc\303\251 */\n"
"    color: white;               /* texte blanc */\n"
"    border: 1px s"
                        "olid black;    /* bordure noire */\n"
"    border-radius: 5px;         /* coins arrondis */\n"
"    padding: 5px;               /* espace interne */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #000070;  /* bleu plus fonc\303\251 au survol */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #000050;  /* bleu tr\303\250s fonc\303\251 quand cliqu\303\251 */\n"
"}\n"
"QLabel {\n"
"    color: black;         /* texte noir */\n"
"    font-family: Arial;   /* police si besoin */\n"
"    font-size: 14px;      /* taille si besoin */\n"
"    font-weight: normal;  /* gras si besoin */\n"
"}\n"
"QLabel {\n"
"    font-family: \"Arial\";   /* famille de police */\n"
"    font-size: 16px;        /* taille de police */\n"
"    font-weight: bold;      /* gras */\n"
"    font-style: italic;     /* italique si besoin */\n"
"    color: black;           /* couleur du texte */\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: navy;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    paddi"
                        "ng: 4px;\n"
"    border: 1px solid #CCCCCC;\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(30, 300, 101, 16));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(40, 90, 1182, 679));
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

        labelType = new QLabel(groupBoxFormulaire);
        labelType->setObjectName("labelType");
        labelType->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelType);

        labelMarque = new QLabel(groupBoxFormulaire);
        labelMarque->setObjectName("labelMarque");
        labelMarque->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelMarque);

        lineEditMarque = new QLineEdit(groupBoxFormulaire);
        lineEditMarque->setObjectName("lineEditMarque");
        lineEditMarque->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditMarque);

        labelModele = new QLabel(groupBoxFormulaire);
        labelModele->setObjectName("labelModele");
        labelModele->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayout->setWidget(3, QFormLayout::LabelRole, labelModele);

        lineEditModele = new QLineEdit(groupBoxFormulaire);
        lineEditModele->setObjectName("lineEditModele");
        lineEditModele->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEditModele);

        labelNumeroSerie = new QLabel(groupBoxFormulaire);
        labelNumeroSerie->setObjectName("labelNumeroSerie");
        labelNumeroSerie->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayout->setWidget(4, QFormLayout::LabelRole, labelNumeroSerie);

        lineEditNumeroSerie = new QLineEdit(groupBoxFormulaire);
        lineEditNumeroSerie->setObjectName("lineEditNumeroSerie");
        lineEditNumeroSerie->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayout->setWidget(4, QFormLayout::FieldRole, lineEditNumeroSerie);

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

        lineEditId = new QLineEdit(groupBoxFormulaire);
        lineEditId->setObjectName("lineEditId");
        lineEditId->setEnabled(false);
        lineEditId->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-color: rgb(0, 0, 0);\n"
"color: black;"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditId);


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

        tableViewAppareils = new QTableView(groupBoxListe);
        tableViewAppareils->setObjectName("tableViewAppareils");
        tableViewAppareils->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tableViewAppareils->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tableViewAppareils->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        tableViewAppareils->setSortingEnabled(true);

        verticalLayout_2->addWidget(tableViewAppareils);

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

        tabWidget->addTab(tabGestion, QString());
        tabStatistiques = new QWidget();
        tabStatistiques->setObjectName("tabStatistiques");
        tabStatistiques->setStyleSheet(QString::fromUtf8("background-color: rgb(44, 49, 71);"));
        verticalLayout_3 = new QVBoxLayout(tabStatistiques);
        verticalLayout_3->setObjectName("verticalLayout_3");
        groupBoxStats = new QGroupBox(tabStatistiques);
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

        tabWidget->addTab(tabStatistiques, QString());
        labelTitle = new QLabel(centralwidget);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setGeometry(QRect(40, 0, 1181, 80));
        labelTitle->setStyleSheet(QString::fromUtf8("font: 700 40pt \"Bahnschrift\";\n"
"color: #35b95f;\n"
"margin: 0px;\n"
"background-color: #2c3147;"));
        labelTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1398, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_5->setText(QString());
        groupBoxFormulaire->setTitle(QCoreApplication::translate("MainWindow", "Formulaire Appareil", nullptr));
        labelId->setText(QCoreApplication::translate("MainWindow", "cin", nullptr));
        labelType->setText(QCoreApplication::translate("MainWindow", "nom", nullptr));
        labelMarque->setText(QCoreApplication::translate("MainWindow", "prenom", nullptr));
        labelModele->setText(QCoreApplication::translate("MainWindow", "num de tel", nullptr));
        labelNumeroSerie->setText(QCoreApplication::translate("MainWindow", "email", nullptr));
        btnAjouter->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnModifier->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        btnSupprimer->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        lineEditId->setText(QString());
        groupBoxListe->setTitle(QCoreApplication::translate("MainWindow", "Liste des Appareils", nullptr));
        labelRecherche->setText(QCoreApplication::translate("MainWindow", "Rechercher par:", nullptr));
        comboBoxCritere->setItemText(0, QCoreApplication::translate("MainWindow", "nom", nullptr));

        btnRechercher->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        btnReinitialiser->setText(QCoreApplication::translate("MainWindow", "tri par nom", nullptr));
        btnExporterPDF->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabGestion), QCoreApplication::translate("MainWindow", "Gestion d'empolye", nullptr));
        groupBoxStats->setTitle(QCoreApplication::translate("MainWindow", "Statistiques des Appareils", nullptr));
        labelGraphTitle->setText(QString());
        labelDetailsTitle->setText(QCoreApplication::translate("MainWindow", "D\303\251tails statistiques", nullptr));
        btnGenererStats->setText(QCoreApplication::translate("MainWindow", "G\303\251n\303\251rer Statistiques", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabStatistiques), QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
        labelTitle->setText(QCoreApplication::translate("MainWindow", "Gestion d'empolye", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
