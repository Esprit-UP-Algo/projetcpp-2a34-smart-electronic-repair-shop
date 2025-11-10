#include "appareils.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

Appareils::Appareils() {}

Appareils::Appareils(int numSerie, QString type, QString marque, QString modele,
                     QDate dateAcquisition, QString etat, int cinClient)
{
    this->numSerie = numSerie;
    this->type = type;
    this->marque = marque;
    this->modele = modele;
    this->dateAcquisition = dateAcquisition;
    this->etat = etat;
    this->cinClient = cinClient;
}

bool Appareils::validerNumSerie(int numSerie)
{
    return (numSerie > 0);
}

bool Appareils::validerCinClient(int cinClient)
{
    return (cinClient > 0 && cinClient <= 99999999);
}

bool Appareils::clientExiste(int cinClient)
{
    if (!validerCinClient(cinClient)) {
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT CIN_CLIENT FROM CLIENT WHERE CIN_CLIENT = :cinClient");
    query.bindValue(":cinClient", cinClient);

    if(query.exec() && query.next()) {
        return true;
    }
    return false;
}

bool Appareils::existeDeja(int numSerie)
{
    if (!validerNumSerie(numSerie)) {
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT NUM_SERIE FROM APPAREILLES WHERE NUM_SERIE = :numSerie");
    query.bindValue(":numSerie", numSerie);

    if(query.exec() && query.next()) {
        return true;
    }
    return false;
}

bool Appareils::ajouter()
{
    // Validation des données
    if (!validerNumSerie(numSerie)) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le numéro de série doit être un nombre positif!");
        return false;
    }

    if (!validerCinClient(cinClient)) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le CIN client doit être un nombre entre 1 et 99,999,999!");
        return false;
    }

    // Vérifier si le numéro de série existe déjà
    if(existeDeja(numSerie)) {
        QMessageBox::warning(nullptr, "Attention", "Ce numéro de série existe déjà dans la base de données!");
        return false;
    }

    // VÉRIFIER SI LE CLIENT EXISTE
    if(!clientExiste(cinClient)) {
        QMessageBox::warning(nullptr, "Client introuvable",
                             "Le CIN client saisi n'existe pas dans la base de données!\n"
                             "Veuillez d'abord ajouter le client.");
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO APPAREILLES (NUM_SERIE, TYPE, MARQUE, MODELE, DATE_ACQ, ETAT, CIN_CLIENT) "
                  "VALUES (:numSerie, :type, :marque, :modele, :dateAcquisition, :etat, :cinClient)");

    query.bindValue(":numSerie", numSerie);
    query.bindValue(":type", type);
    query.bindValue(":marque", marque);
    query.bindValue(":modele", modele);
    query.bindValue(":dateAcquisition", dateAcquisition);
    query.bindValue(":etat", etat);
    query.bindValue(":cinClient", cinClient);

    return query.exec();
}

QSqlQueryModel* Appareils::getClients()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CIN_CLIENT, NOM, PRENOM FROM CLIENT ORDER BY NOM, PRENOM");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    return model;
}

QSqlQueryModel* Appareils::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT NUM_SERIE, TYPE, MARQUE, MODELE, DATE_ACQ, ETAT, CIN_CLIENT FROM APPAREILLES");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Numéro Série"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Marque"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Modèle"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date Acquisition"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("État"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("CIN Client"));

    return model;
}

bool Appareils::supprimer(int numSerie)
{
    QSqlQuery query;
    query.prepare("DELETE FROM APPAREILLES WHERE NUM_SERIE = :numSerie");
    query.bindValue(":numSerie", numSerie);

    return query.exec();
}

bool Appareils::modifier(int numSerie)
{
    QSqlQuery query;
    query.prepare("UPDATE APPAREILLES SET TYPE = :type, MARQUE = :marque, MODELE = :modele, "
                  "DATE_ACQ = :dateAcquisition, ETAT = :etat, CIN_CLIENT = :cinClient "
                  "WHERE NUM_SERIE = :numSerie");

    query.bindValue(":numSerie", numSerie);
    query.bindValue(":type", type);
    query.bindValue(":marque", marque);
    query.bindValue(":modele", modele);
    query.bindValue(":dateAcquisition", dateAcquisition);
    query.bindValue(":etat", etat);
    query.bindValue(":cinClient", cinClient);

    return query.exec();
}

QSqlQueryModel* Appareils::rechercher(QString valeur)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM APPAREILLES WHERE NUM_SERIE LIKE :valeur OR MARQUE LIKE :valeur");
    query.bindValue(":valeur", "%" + valeur + "%");
    query.exec();

    model->setQuery(query);
    return model;
}
