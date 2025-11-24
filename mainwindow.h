#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "reparation.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_BTN_AJOUTER_clicked();
    void on_BTN_MODIFIER_clicked();
    void on_BTN_SUPPRIMER_clicked();
    void on_BTN_RECHERCHER_clicked();
    void on_BTN_TRIER_clicked();
    void on_BTN_PREDICTION_DELAI_clicked();
    void on_BTN_EXPORTER_clicked();
    void on_BTN_STATISTIQUES_clicked();
    void on_BTN_NOTIFIER_clicked();

    void onSmsSent(QNetworkReply *reply);
    void onCritereRechercheChanged(const QString &critere);
    void afficherStatistiquesAvecDiagramme(int enAttente, int enCours, int terminees, int annulees, double coutTotal, int total);
private:
    Ui::MainWindow *ui;
    Reparation Rtmp;
    QNetworkAccessManager *networkManager;

    void actualiserTable();
    void viderChamps();
    void debugCheckDatabase();
    void testerFormatNumeros();
    QString construireRequeteRecherche(const QString &critere, const QString &valeur);

    // Méthodes pour Machine Learning
    double predictRepairDurationML(const QString &typeAppareil, const QString &descriptionPanne,
                                   const QString &marque, const QString &modele);
    void trainPredictionModel();

    // Méthodes pour TextBelt SMS avec sauvegarde locale
    void envoyerSMSTextBelt(const QString &telephone, const QString &message, const QString &clientName);
    void sauvegarderSMSTerme(const QString &telephone, const QString &message, const QString &clientName, bool success, const QString &reponse = "");
    QString formaterNumeroInternational(const QString &telephone);
    void afficherHistoriqueSMS();
    void verifierFichiersSMS();
    // Variables pour ML
    QMap<QString, double> featureWeights;
    double baseDuration;
    QMap<QString, int> panneComplexity;
    QMap<QString, int> brandComplexity;
    QMap<QString, int> typeComplexity;

};

#endif // MAINWINDOW_H
