#include "empolye.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

empolye::empolye() {
    id = 0;
    nom = "";
    prenom = "";
    poste = "";
    salaire = 0.0;
}

empolye::empolye(int id, QString nom, QString prenom, QString poste, double salaire) {
    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->poste = poste;
    this->salaire = salaire;
}

// CREATE - Ajouter un employé
bool empolye::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO employes (nom, prenom, poste, salaire) "
                  "VALUES (:nom, :prenom, :poste, :salaire)");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":salaire", salaire);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Erreur d'ajout:" << query.lastError().text();
        return false;
    }
}

// READ - Afficher tous les employés
QList<empolye> empolye::afficher() {
    QList<empolye> liste;
    QSqlQuery query("SELECT * FROM employes");

    while (query.next()) {
        empolye emp;
        emp.setId(query.value(0).toInt());
        emp.setNom(query.value(1).toString());
        emp.setPrenom(query.value(2).toString());
        emp.setPoste(query.value(3).toString());
        emp.setSalaire(query.value(4).toDouble());
        liste.append(emp);
    }

    return liste;
}

// UPDATE - Modifier un employé
bool empolye::modifier() {
    QSqlQuery query;
    query.prepare("UPDATE employes SET nom=:nom, prenom=:prenom, "
                  "poste=:poste, salaire=:salaire WHERE id=:id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":salaire", salaire);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Erreur de modification:" << query.lastError().text();
        return false;
    }
}

// DELETE - Supprimer un employé
bool empolye::supprimer() {
    QSqlQuery query;
    query.prepare("DELETE FROM employes WHERE id=:id");
    query.bindValue(":id", id);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Erreur de suppression:" << query.lastError().text();
        return false;
    }
}

