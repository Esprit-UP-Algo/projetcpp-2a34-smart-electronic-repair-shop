#include "employe.h"
#include <QMessageBox>
#include <QRegularExpression>

Employe::Employe() {}

Employe::Employe(int cin, QString nom, QString prenom, QString telephone, QString email)
{
    this->cin = cin;
    this->nom = nom;
    this->prenom = prenom;
    this->telephone = telephone;
    this->email = email;
}

bool Employe::validerCin(int cin)
{
    return (cin > 0 && cin <= 99999999);
}

bool Employe::validerTelephone(QString telephone)
{
    QRegularExpression regex("^[0-9]{8}$");
    return regex.match(telephone).hasMatch();
}

bool Employe::validerEmail(QString email)
{
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return regex.match(email).hasMatch();
}

bool Employe::validerNomPrenom(QString texte)
{
    QRegularExpression regex("^[a-zA-ZÀ-ÿ\\s'-]{2,50}$");
    return regex.match(texte).hasMatch();
}

bool Employe::existeDeja(int cin)
{
    if (!validerCin(cin)) {
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT CIN_EMPLOYER FROM EMPLOYER WHERE CIN_EMPLOYER = :cin");
    query.bindValue(":cin", cin);

    if(query.exec() && query.next()) {
        return true;
    }
    return false;
}

bool Employe::ajouter()
{
    // Validation des données
    if (!validerCin(cin)) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le CIN doit être un nombre entre 1 et 99,999,999!");
        return false;
    }

    if (!validerNomPrenom(nom)) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le nom n'est pas valide!");
        return false;
    }

    if (!validerNomPrenom(prenom)) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le prénom n'est pas valide!");
        return false;
    }

    if (!telephone.isEmpty() && !validerTelephone(telephone)) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le téléphone doit contenir 8 chiffres!");
        return false;
    }

    if (!email.isEmpty() && !validerEmail(email)) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "L'email n'est pas valide!");
        return false;
    }

    // Vérifier si le CIN existe déjà
    if(existeDeja(cin)) {
        QMessageBox::warning(nullptr, "Attention", "Ce CIN employé existe déjà dans la base de données!");
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYER (CIN_EMPLOYER, NOM, PRENOM, TELEPHONE, EMAIL) "
                  "VALUES (:cin, :nom, :prenom, :telephone, :email)");

    query.bindValue(":cin", cin);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);

    return query.exec();
}

QSqlQueryModel* Employe::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CIN_EMPLOYER, NOM, PRENOM, TELEPHONE, EMAIL FROM EMPLOYER");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));

    return model;
}

bool Employe::supprimer(int cin)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYER WHERE CIN_EMPLOYER = :cin");
    query.bindValue(":cin", cin);

    return query.exec();
}

bool Employe::modifier(int cin)
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYER SET NOM = :nom, PRENOM = :prenom, "
                  "TELEPHONE = :telephone, EMAIL = :email WHERE CIN_EMPLOYER = :cin");

    query.bindValue(":cin", cin);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);

    return query.exec();
}
