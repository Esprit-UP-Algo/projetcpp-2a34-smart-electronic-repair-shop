#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegularExpressionValidator>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QTextEdit>
#include <QSerialPort>        // ← À AJOUTER OBLIGATOIREMENT
#include <QSerialPortInfo>    // ← À AJOUTER AUSSI

// Inclure les classes nécessaires
#include "employe.h"
#include "client.h"
#include "appareils.h"
#include "reparations.h"
#include "statistics.h"
#include "pdfexporter.h"
#include "config.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // Twilio configuration

    void loadTwilioCredentials();

private slots:
    //clavier
   void readKeyboardData();
    void processKeyboardCommand(const QString &command);
    void verifyReparationID(int idr);
    // Slots pour les employés
    void on_btnAjouter_clicked();
    void on_btnModifier_clicked();
    void on_btnSupprimer_clicked();
    void on_btnRechercher_clicked();
    void on_btnReinitialiser_clicked();
    void on_tableViewAppareils_2_clicked(const QModelIndex &index);

    // Slots pour les clients
    void on_btnAjouterClient_clicked();
    void on_btnModifierClient_clicked();
    void on_btnSupprimerClient_clicked();
    void on_btnRechercherClient_clicked();
    void on_btnReinitialiserClient_clicked();
    void on_tableViewClients_clicked(const QModelIndex &index);

    // Slots pour les appareils
    void on_btnAjouterAppareil_clicked();
    void on_btnModifierAppareil_clicked();
    void on_btnSupprimerAppareil_clicked();
    void on_btnRechercherAppareil_clicked();
    void on_btnReinitialiserAppareil_clicked();
    void on_btnVieAppareil_clicked();
    void on_tableViewAppareils_clicked(const QModelIndex &index);

    // Slots pour les réparations
    void on_btnAjouterReparation_clicked();
    void on_btnModifierReparation_clicked();
    void on_btnSupprimerReparation_clicked();
    void on_btnRechercherReparation_clicked();
    void on_btnReinitialiserReparation_clicked();
    void on_tableViewReparationsListe_clicked(const QModelIndex &index);

    // Slots pour les statistiques
    void on_btnGenererRapport_clicked();
    void on_btnStatistiquesAppareil_clicked();

    // Slot pour le bouton Calendrier
    void on_btnCalendrier_clicked();

    // Nouveaux slots pour le contrôle de saisie et tri
    void onTextChanged(const QString &text);
    void onHeaderReparationClicked(int logicalIndex);
    // ============ SLOTS MÉTIERS INNOVANTS ============
    void on_btnAnalyserFidelite_clicked();
    void on_btnMaintenancePreventive_clicked();
    // Nouveaux slots pour les fonctionnalités avancées
    void on_btnShowStatistics_clicked();
    void on_btnExportPDF_clicked();
    //----------------------------
    void on_BTN_NOTIFIER_clicked();
    void on_BTN_STATISTIQUES_clicked();
    void on_BTN_EXPORTER_clicked();
    void on_BTN_PREDICTION_DELAI_clicked();


    void onTwilioSent(QNetworkReply *reply);
    void afficherStatistiquesAvecDiagramme(int enAttente, int enCours, int terminees, int annulees, double coutTotal, int total);
    //clavier
   /* void lireEntreeClavier();
    void traiterCommandeClavier(const QString &commande);*/
private:
    Ui::MainWindow *ui;
    Employe emp;
    Client clt;
    Appareils app;
    Reparations rep;
    PDFExporter *pdfExporter = nullptr;
    Statistics *statisticsWindow = nullptr;
    QNetworkAccessManager *networkManager;

    // ============ ARDUINO RFID ============
    QSerialPort *arduino;
    QString arduino_port_name;
    bool arduino_available;

    // Pour l'association automatique RFID → Client
    int clientEnAttenteRFID;  // CIN du client en cours d'association
    bool modeAssociationRFID;
private:

    // Variables pour le clavier
    QSerialPort *keyboardArduino;
    QString keyboardPortName;
    bool keyboardArduinoAvailable;
    QString keyboardBuffer;

    // Méthodes pour le clavier
    void initKeyboardArduino();
    // ============ MÉTHODES RFID ============
    void initArduino();
    void lireUIDArduino();
    void verifierAccesRFID(const QString &uid);
    void associerRFIDAuClient(const QString &uid);
    void on_btnAssocierRFID_clicked();


    // ============ MÉTHODES COMMUNES ============
    void refreshEmployeTable();
    void refreshClientTable();
    void refreshAppareilTable();
    void refreshReparationTable();
    void loadComboBoxData();
    void clearEmployeFields();
    void clearClientFields();
    void clearAppareilFields();
    void clearReparationFields();
    void setupValidators();
    void highlightEmptyFields(const QStringList& fields, const QStringList& values);
    void setupAdvancedFeatures();
    void testerFormatNumeros();


    // Variable pour suivre l'ordre de tri
    bool sortOrderAscending_ = true;

    // Méthodes de validation
    bool validateCIN(const QString& cinStr, int& cin);
    bool validateTelephone(const QString& telephone);
    bool validateEmail(const QString& email);
    bool validateNomPrenom(const QString& texte);
    bool validateNumSerie(const QString& numStr, int& numSerie);
    bool validateCout(const QString& coutStr, double& cout);
    bool validateIdReparation(const QString& idStr, int& idReparation);
    bool validateTextField(const QString& text, const QString& fieldName);
    bool validateRequiredFields(const QStringList& fields, const QStringList& values, const QString& formName);
    void afficherChampsTexte(); // Fonction utilitaire pour le débogage
    // ============ MÉTHODES MÉTIERS INNOVANTS ============
    void afficherProfilClient(int cin);
    // Machine Learning methods
    double predictRepairDurationML(const QString &typeAppareil, const QString &descriptionPanne,
                                   const QString &marque, const QString &modele);
    void trainPredictionModel();

    // Twilio WhatsApp methods
    void envoyerWhatsAppTwilio(const QString &telephone, const QString &message, const QString &clientName);
    void sauvegarderWhatsAppHistorique(const QString &telephone, const QString &message, const QString &clientName, bool success, const QString &reponse = "");
    QString formaterNumeroTwilio(const QString &telephone);
    void verifierFichiersWhatsApp();
    void envoyerSMSTwilio(const QString &telephone, const QString &message, const QString &clientName);
    // Variables for ML
    QMap<QString, double> featureWeights;
    double baseDuration;
    QMap<QString, int> panneComplexity;
    QMap<QString, int> brandComplexity;
    QMap<QString, int> typeComplexity;
    bool verifierConnexionInternet();
    QString nettoyerTelephone(const QString &telephone);
};

#endif // MAINWINDOW_H
