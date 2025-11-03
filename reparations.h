#ifndef REPARATIONS_H
#define REPARATIONS_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Reparations
{
private:
    int matApp;
    QString descriptionPanne;
    QDate dateReception;
    QDate dateFin;
    QString statut;
    double cout;
    int cinEmploye;
    int numSerie;

public:
    Reparations();
    Reparations(int, QString, QDate, QDate, QString, double, int, int);

    // Getters
    int getMatApp() { return matApp; }
    QString getDescriptionPanne() { return descriptionPanne; }
    QDate getDateReception() { return dateReception; }
    QDate getDateFin() { return dateFin; }
    QString getStatut() { return statut; }
    double getCout() { return cout; }
    int getCinEmploye() { return cinEmploye; }
    int getNumSerie() { return numSerie; }

    // Setters
    void setMatApp(int m) { matApp = m; }
    void setDescriptionPanne(QString d) { descriptionPanne = d; }
    void setDateReception(QDate d) { dateReception = d; }
    void setDateFin(QDate d) { dateFin = d; }
    void setStatut(QString s) { statut = s; }
    void setCout(double c) { cout = c; }
    void setCinEmploye(int c) { cinEmploye = c; }
    void setNumSerie(int n) { numSerie = n; }

    // CRUD Operations
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int matApp);
    bool modifier(int matApp);
    QSqlQueryModel* rechercher(QString critere, QString valeur);
    QSqlQueryModel* getAppareilsDisponibles();
    QSqlQueryModel* getEmployesDisponibles();
    bool existeDeja(int matApp);

    // Méthodes de validation
    bool validerMatApp(int matApp);
    bool validerCout(double cout);
    bool validerDates(QDate reception, QDate fin);
};

#endif // REPARATIONS_H
