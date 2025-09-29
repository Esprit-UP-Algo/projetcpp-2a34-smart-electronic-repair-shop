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
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GestionAppareils
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayoutHeader;
    QLabel *labelLogo;
    QLabel *labelTitle;
    QTabWidget *tabWidget;
    QWidget *tabGestion;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBoxFormulaire;
    QFormLayout *formLayout;
    QLabel *labelId;
    QLineEdit *lineEditId;
    QLabel *labelType;
    QComboBox *comboBoxType;
    QLabel *labelMarque;
    QLineEdit *lineEditMarque;
    QLabel *labelModele;
    QLineEdit *lineEditModele;
    QLabel *labelNumeroSerie;
    QLineEdit *lineEditNumeroSerie;
    QLabel *labelDateAcquisition;
    QDateEdit *dateEditAcquisition;
    QLabel *labelEtat;
    QComboBox *comboBoxEtat;
    QHBoxLayout *horizontalLayoutButtons;
    QPushButton *btnAjouter;
    QPushButton *btnModifier;
    QPushButton *btnSupprimer;
    QHBoxLayout *horizontalLayoutQR;
    QGroupBox *groupBoxListe;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayoutRecherche;
    QLabel *labelRecherche;
    QComboBox *comboBoxCritere;
    QPushButton *btnRechercher;
    QPushButton *btnReinitialiser;
    QTableView *tableViewAppareils;
    QHBoxLayout *horizontalLayoutExport;
    QLabel *labelTotal;
    QPushButton *btnExporterPDF;
    QPushButton *btnExporterExcel;
    QWidget *tabStatistiques;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBoxStats;
    QHBoxLayout *horizontalLayout_2;
    QFrame *frameGraphique;
    QVBoxLayout *verticalLayout_4;
    QLabel *labelGraphTitle;
    QWidget *widgetGraphique;
    QFrame *frameDetails;
    QVBoxLayout *verticalLayout_5;
    QLabel *labelDetailsTitle;
    QTextEdit *textEditStats;
    QPushButton *btnGenererStats;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GestionAppareils)
    {
        if (GestionAppareils->objectName().isEmpty())
            GestionAppareils->setObjectName("GestionAppareils");
        GestionAppareils->resize(1200, 807);
        GestionAppareils->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
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
"QLineEdit, QComboBox, QDateEdit {\n"
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
"    border-top-right-radius: 4px;\n"
"}\n"
""
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
"}"));
        centralwidget = new QWidget(GestionAppareils);
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

        labelType = new QLabel(groupBoxFormulaire);
        labelType->setObjectName("labelType");
        labelType->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelType);

        comboBoxType = new QComboBox(groupBoxFormulaire);
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        comboBoxType->setObjectName("comboBoxType");
        comboBoxType->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayout->setWidget(1, QFormLayout::FieldRole, comboBoxType);

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

        labelDateAcquisition = new QLabel(groupBoxFormulaire);
        labelDateAcquisition->setObjectName("labelDateAcquisition");
        labelDateAcquisition->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayout->setWidget(5, QFormLayout::LabelRole, labelDateAcquisition);

        dateEditAcquisition = new QDateEdit(groupBoxFormulaire);
        dateEditAcquisition->setObjectName("dateEditAcquisition");
        dateEditAcquisition->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);font: 9pt \"Segoe UI\";\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));
        dateEditAcquisition->setCalendarPopup(true);

        formLayout->setWidget(5, QFormLayout::FieldRole, dateEditAcquisition);

        labelEtat = new QLabel(groupBoxFormulaire);
        labelEtat->setObjectName("labelEtat");
        labelEtat->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        formLayout->setWidget(6, QFormLayout::LabelRole, labelEtat);

        comboBoxEtat = new QComboBox(groupBoxFormulaire);
        comboBoxEtat->addItem(QString());
        comboBoxEtat->addItem(QString());
        comboBoxEtat->addItem(QString());
        comboBoxEtat->addItem(QString());
        comboBoxEtat->setObjectName("comboBoxEtat");
        comboBoxEtat->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: black;\n"
"border-color: rgb(0, 0, 0);"));

        formLayout->setWidget(6, QFormLayout::FieldRole, comboBoxEtat);

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


        formLayout->setLayout(7, QFormLayout::SpanningRole, horizontalLayoutButtons);

        horizontalLayoutQR = new QHBoxLayout();
        horizontalLayoutQR->setObjectName("horizontalLayoutQR");

        formLayout->setLayout(8, QFormLayout::SpanningRole, horizontalLayoutQR);


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
        labelTotal = new QLabel(groupBoxListe);
        labelTotal->setObjectName("labelTotal");
        labelTotal->setStyleSheet(QString::fromUtf8("font: 14pt \"Bauhaus 93\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayoutExport->addWidget(labelTotal);

        btnExporterPDF = new QPushButton(groupBoxListe);
        btnExporterPDF->setObjectName("btnExporterPDF");
        btnExporterPDF->setStyleSheet(QString::fromUtf8("background-color: #DC3545;\n"
"color: rgb(255, 255, 255);\n"
"font: 900 12pt \"Swis721 BlkCn BT\";"));

        horizontalLayoutExport->addWidget(btnExporterPDF);

        btnExporterExcel = new QPushButton(groupBoxListe);
        btnExporterExcel->setObjectName("btnExporterExcel");
        btnExporterExcel->setStyleSheet(QString::fromUtf8("background-color: #28A745;\n"
"color: rgb(255, 255, 255);\n"
"font: 900 12pt \"Swis721 BlkCn BT\";"));

        horizontalLayoutExport->addWidget(btnExporterExcel);


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
        labelGraphTitle = new QLabel(frameGraphique);
        labelGraphTitle->setObjectName("labelGraphTitle");
        labelGraphTitle->setStyleSheet(QString::fromUtf8("font-family: 'Montserrat Bold';\n"
"font-size: 16px;\n"
"color: #007BFF;\n"
"margin: 10px;"));
        labelGraphTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(labelGraphTitle);

        widgetGraphique = new QWidget(frameGraphique);
        widgetGraphique->setObjectName("widgetGraphique");
        widgetGraphique->setMinimumSize(QSize(400, 300));
        widgetGraphique->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border: 1px solid #6C757D;\n"
"border-radius: 4px;"));

        verticalLayout_4->addWidget(widgetGraphique);


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

        verticalLayout->addWidget(tabWidget);

        GestionAppareils->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(GestionAppareils);
        statusbar->setObjectName("statusbar");
        GestionAppareils->setStatusBar(statusbar);

        retranslateUi(GestionAppareils);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GestionAppareils);
    } // setupUi

    void retranslateUi(QMainWindow *GestionAppareils)
    {
        GestionAppareils->setWindowTitle(QCoreApplication::translate("GestionAppareils", "Smart Repair Hub - Gestion des Appareils", nullptr));
        labelLogo->setText(QString());
        labelTitle->setText(QCoreApplication::translate("GestionAppareils", "Gestion des Appareils", nullptr));
        groupBoxFormulaire->setTitle(QCoreApplication::translate("GestionAppareils", "Formulaire Appareil", nullptr));
        labelId->setText(QCoreApplication::translate("GestionAppareils", "ID:", nullptr));
        labelType->setText(QCoreApplication::translate("GestionAppareils", "Type :", nullptr));
        comboBoxType->setItemText(0, QCoreApplication::translate("GestionAppareils", "Smartphone", nullptr));
        comboBoxType->setItemText(1, QCoreApplication::translate("GestionAppareils", "Ordinateur Portable", nullptr));
        comboBoxType->setItemText(2, QCoreApplication::translate("GestionAppareils", "Tablette", nullptr));
        comboBoxType->setItemText(3, QCoreApplication::translate("GestionAppareils", "Appareil IoT", nullptr));
        comboBoxType->setItemText(4, QCoreApplication::translate("GestionAppareils", "Autre", nullptr));

        labelMarque->setText(QCoreApplication::translate("GestionAppareils", "Marque :", nullptr));
        labelModele->setText(QCoreApplication::translate("GestionAppareils", "Mod\303\250le :", nullptr));
        labelNumeroSerie->setText(QCoreApplication::translate("GestionAppareils", "Num\303\251ro S\303\251rie:", nullptr));
        labelDateAcquisition->setText(QCoreApplication::translate("GestionAppareils", "Date Acquisition:", nullptr));
        labelEtat->setText(QCoreApplication::translate("GestionAppareils", "\303\211tat:", nullptr));
        comboBoxEtat->setItemText(0, QCoreApplication::translate("GestionAppareils", "Neuf", nullptr));
        comboBoxEtat->setItemText(1, QCoreApplication::translate("GestionAppareils", "Bon \303\251tat", nullptr));
        comboBoxEtat->setItemText(2, QCoreApplication::translate("GestionAppareils", "Us\303\251", nullptr));
        comboBoxEtat->setItemText(3, QCoreApplication::translate("GestionAppareils", "D\303\251fectueux", nullptr));

        btnAjouter->setText(QCoreApplication::translate("GestionAppareils", "Ajouter", nullptr));
        btnModifier->setText(QCoreApplication::translate("GestionAppareils", "Modifier", nullptr));
        btnSupprimer->setText(QCoreApplication::translate("GestionAppareils", "Supprimer", nullptr));
        groupBoxListe->setTitle(QCoreApplication::translate("GestionAppareils", "Liste des Appareils", nullptr));
        labelRecherche->setText(QCoreApplication::translate("GestionAppareils", "Rechercher par:", nullptr));
        comboBoxCritere->setItemText(0, QCoreApplication::translate("GestionAppareils", "Num S\303\251rie", nullptr));

        btnRechercher->setText(QCoreApplication::translate("GestionAppareils", "Rechercher", nullptr));
        btnReinitialiser->setText(QCoreApplication::translate("GestionAppareils", "R\303\251initialiser", nullptr));
        labelTotal->setText(QCoreApplication::translate("GestionAppareils", "Total: 0 appareils", nullptr));
        btnExporterPDF->setText(QCoreApplication::translate("GestionAppareils", "Exporter PDF", nullptr));
        btnExporterExcel->setText(QCoreApplication::translate("GestionAppareils", "Exporter Excel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabGestion), QCoreApplication::translate("GestionAppareils", "Gestion des Appareils", nullptr));
        groupBoxStats->setTitle(QCoreApplication::translate("GestionAppareils", "Statistiques des Appareils", nullptr));
        labelGraphTitle->setText(QCoreApplication::translate("GestionAppareils", "Types d'appareils les plus r\303\251par\303\251s", nullptr));
        labelDetailsTitle->setText(QCoreApplication::translate("GestionAppareils", "D\303\251tails statistiques", nullptr));
        btnGenererStats->setText(QCoreApplication::translate("GestionAppareils", "G\303\251n\303\251rer Statistiques", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabStatistiques), QCoreApplication::translate("GestionAppareils", "Statistiques", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GestionAppareils: public Ui_GestionAppareils {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
