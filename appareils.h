#ifndef APPAREILS_H
#define APPAREILS_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Appareils
{
private:
    int numSerie;
    QString type;
    QString marque;
    QString modele;
    QDate dateAcquisition;
    QString etat;
    int cinClient;

public:
    Appareils();
    Appareils(int, QString, QString, QString, QDate, QString, int);

    // Getters
    int getNumSerie() { return numSerie; }
    QString getType() { return type; }
    QString getMarque() { return marque; }
    QString getModele() { return modele; }
    QDate getDateAcquisition() { return dateAcquisition; }
    QString getEtat() { return etat; }
    int getCinClient() { return cinClient; }

    // Setters
    void setNumSerie(int n) { numSerie = n; }
    void setType(QString t) { type = t; }
    void setMarque(QString m) { marque = m; }
    void setModele(QString m) { modele = m; }
    void setDateAcquisition(QDate d) { dateAcquisition = d; }
    void setEtat(QString e) { etat = e; }
    void setCinClient(int c) { cinClient = c; }

    // CRUD Operations
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int numSerie);
    bool modifier(int numSerie);
    QSqlQueryModel* rechercher(const QString& valeur, const QString& typeRecherche = "");
    bool existeDeja(int numSerie);
    bool clientExiste(int cinClient);
    QSqlQueryModel* getClients();

    // Nouvelles méthodes pour les contrôles
    bool validerNumSerie(int numSerie);
    bool validerCinClient(int cinClient);
};

#endif // APPAREILS_H
