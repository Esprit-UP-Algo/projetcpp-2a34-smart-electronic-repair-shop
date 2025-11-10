#ifndef EMPOLYE_H
#define EMPOLYE_H

#include <QString>
#include <QList>

class empolye
{
private:
    int id;
    QString nom;
    QString prenom;
    QString poste;
    double salaire;

public:
    // Constructeurs
    empolye();
    empolye(int id, QString nom, QString prenom, QString poste, double salaire);

    // Getters
    int getId() const { return id; }
    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    QString getPoste() const { return poste; }
    double getSalaire() const { return salaire; }

    // Setters
    void setId(int id) { this->id = id; }
    void setNom(QString nom) { this->nom = nom; }
    void setPrenom(QString prenom) { this->prenom = prenom; }
    void setPoste(QString poste) { this->poste = poste; }
    void setSalaire(double salaire) { this->salaire = salaire; }

    // Méthodes CRUD
    bool ajouter();
    static QList<empolye> afficher();
    bool modifier();
    bool supprimer();
    static empolye rechercherParId(int id);
};

#endif // EMPOLYE_H
