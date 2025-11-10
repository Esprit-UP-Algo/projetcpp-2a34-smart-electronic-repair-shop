#ifndef REPARATIONS_H
#define REPARATIONS_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Reparations
{
private:
    int idr;
    QString descriptionPanne;
    QDate dateReception;
    QDate dateFinEstimee;
    QString statut;
    double cout;
    int cinEmploye;
    int numSerie;
    QString matRep;

public:
    Reparations();
    Reparations(int, QString, QDate, QDate, QString, double, int, int, QString);

    // Getters
    int getIdr() { return idr; }
    QString getDescriptionPanne() { return descriptionPanne; }
    QDate getDateReception() { return dateReception; }
    QDate getDateFinEstimee() { return dateFinEstimee; }
    QString getStatut() { return statut; }
    double getCout() { return cout; }
    int getCinEmploye() { return cinEmploye; }
    int getNumSerie() { return numSerie; }
    QString getMatRep() { return matRep; }

    // Setters
    void setIdr(int i) { idr = i; }
    void setDescriptionPanne(QString d) { descriptionPanne = d; }
    void setDateReception(QDate d) { dateReception = d; }
    void setDateFinEstimee(QDate d) { dateFinEstimee = d; }
    void setStatut(QString s) { statut = s; }
    void setCout(double c) { cout = c; }
    void setCinEmploye(int c) { cinEmploye = c; }
    void setNumSerie(int n) { numSerie = n; }
    void setMatRep(QString m) { matRep = m; }

    // CRUD Operations
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int idr);
    bool modifier(int idr);
    QSqlQueryModel* rechercher(QString critere, QString valeur);
    QSqlQueryModel* getAppareilsDisponibles();
    QSqlQueryModel* getEmployesDisponibles();
    bool existeDeja(int idr);

    // Méthodes de validation
    bool validerIdr(int idr);
    bool validerCout(double cout);
    bool validerDates(QDate reception, QDate fin);
};

#endif // REPARATIONS_H
