#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Employe
{
private:
    int cin;
    QString nom;
    QString prenom;
    QString telephone;
    QString email;

public:
    Employe();
    Employe(int, QString, QString, QString, QString);

    // Getters
    int getCin() { return cin; }
    QString getNom() { return nom; }
    QString getPrenom() { return prenom; }
    QString getTelephone() { return telephone; }
    QString getEmail() { return email; }

    // Setters
    void setCin(int c) { cin = c; }
    void setNom(QString n) { nom = n; }
    void setPrenom(QString p) { prenom = p; }
    void setTelephone(QString t) { telephone = t; }
    void setEmail(QString e) { email = e; }

    // CRUD Operations
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int cin);
    bool modifier(int cin);
    bool existeDeja(int cin);

    // Méthodes de validation
    bool validerCin(int cin);
    bool validerTelephone(QString telephone);
    bool validerEmail(QString email);
    bool validerNomPrenom(QString texte);
};

#endif // EMPLOYE_H
