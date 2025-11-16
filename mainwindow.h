#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegularExpressionValidator>

// Inclure les classes nécessaires
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    // Slots pour les clients
    void on_btnAjouterClient_clicked();
    void on_btnModifierClient_clicked();
    void on_btnSupprimerClient_clicked();
    void on_btnRechercherClient_clicked();
    void on_btnReinitialiserClient_clicked();
    void on_tableViewClients_clicked(const QModelIndex &index);

    // Slots pour les statistiques
    void on_btnGenererRapport_clicked();

    // Nouveaux slots pour le contrôle de saisie et tri
    void onTextChanged(const QString &text);
    void onHeaderReparationClicked(int logicalIndex);

    // ============ SLOTS MÉTIERS INNOVANTS ============
    void on_btnAnalyserFidelite_clicked();
    void on_btnMaintenancePreventive_clicked();
    void on_btnGenererRapportFidelite_clicked();
    void on_btnEnvoyerSMS_clicked();

private:
    Ui::MainWindow *ui;
    Client clt;

    void refreshClientTable();
    void loadComboBoxData();
    void clearClientFields();
    void setupValidators();
    void highlightEmptyFields(const QStringList& fields, const QStringList& values);

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

    // ============ MÉTHODES MÉTIERS INNOVANTS ============
    void afficherProfilClient(int cin);
    void genererPDFProfilClient(int cin);
    void genererPDFMaintenance(int cin);
    void afficherWidgetMetiersInnovants();
};

#endif // MAINWINDOW_H
