#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegularExpressionValidator>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>

// Inclure les classes nécessaires
#include "employe.h"
#include "client.h"
#include "appareils.h"
#include "reparations.h"

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


    // Nouveaux slots pour le contrôle de saisie et tri
    void onTextChanged(const QString &text);
    void onHeaderReparationClicked(int logicalIndex);

private:
    Ui::MainWindow *ui;
    Employe emp;
    Client clt;
    Appareils app;
    Reparations rep;

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
};

#endif // MAINWINDOW_H
