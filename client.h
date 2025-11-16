#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMap>
#include <QVariant>

class Client
{
private:
    int cin;
    QString nom;
    QString prenom;
    QString telephone;
    QString email;
    QString adresse;
    QDate dateNaissance;

public:
    Client();
    Client(int, QString, QString, QString, QString, QString, QDate);

    // Getters
    int getCin() { return cin; }
    QString getNom() { return nom; }
    QString getPrenom() { return prenom; }
    QString getTelephone() { return telephone; }
    QString getEmail() { return email; }
    QString getAdresse() { return adresse; }
    QDate getDateNaissance() { return dateNaissance; }

    // Setters
    void setCin(int c) { cin = c; }
    void setNom(QString n) { nom = n; }
    void setPrenom(QString p) { prenom = p; }
    void setTelephone(QString t) { telephone = t; }
    void setEmail(QString e) { email = e; }
    void setAdresse(QString a) { adresse = a; }
    void setDateNaissance(QDate d) { dateNaissance = d; }

    // CRUD Operations
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int cin);
    bool modifier(int cin);
    QSqlQueryModel* rechercher(QString critere, QString valeur);
    bool existeDeja(int cin);

    // Méthodes de validation
    bool validerCin(int cin);
    bool validerTelephone(QString telephone);
    bool validerEmail(QString email);
    bool validerNomPrenom(QString texte);

    // ============ MÉTIERS INNOVANTS ============
    // Score de Fidélité & Prédiction
    double calculerScoreFidelite();
    QString getProfilClient();
    int predireProchainRetour();

    // Analyse Maintenance Préventive
    QMap<QString, QVariant> analyserAppareilsMaintenance();

    // Getters pour les données d'historique
    int getNombreVisites();
    double getTotalDepenses();
    QDate getDerniereVisite();
    double getTauxAnnulation();
    int getVarieteAppareils();
    double getRegulariteVisites();

    // Méthodes pour rapports
    QMap<QString, QVariant> getDonneesFidelite();
};

#endif // CLIENT_H
