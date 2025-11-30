#include "client.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QSqlError>

Client::Client() {}

Client::Client(int cin, QString nom, QString prenom, QString telephone,
               QString email, QString adresse, QDate dateNaissance)
{
    this->cin = cin;
    this->nom = nom;
    this->prenom = prenom;
    this->telephone = telephone;
    this->email = email;
    this->adresse = adresse;
    this->dateNaissance = dateNaissance;
}

bool Client::validerCin(int cin)
{
    return (cin > 0 && cin <= 99999999);
}

bool Client::validerTelephone(QString telephone)
{
    QRegularExpression regex("^[0-9]{8}$");
    return regex.match(telephone).hasMatch();
}

bool Client::validerEmail(QString email)
{
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return regex.match(email).hasMatch();
}

bool Client::validerNomPrenom(QString texte)
{
    QRegularExpression regex("^[a-zA-ZÀ-ÿ\\s'-]{2,50}$");
    return regex.match(texte).hasMatch();
}

bool Client::existeDeja(int cin)
{
    if (!validerCin(cin)) {
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT CIN_CLIENT FROM CLIENT WHERE CIN_CLIENT = :cin");
    query.bindValue(":cin", cin);

    if(query.exec() && query.next()) {
        return true;
    }
    return false;
}

// GARDER UNE SEULE DÉFINITION DE ajouter() - SUPPRIMER LA DEUXIÈME
bool Client::ajouter()
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
        QMessageBox::warning(nullptr, "Attention", "Ce CIN existe déjà dans la base de données!");
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO CLIENT (CIN_CLIENT, NOM, PRENOM, TELEPHONE, EMAIL, ADRESSE, DATEN) "
                  "VALUES (:cin, :nom, :prenom, :telephone, :email, :adresse, :dateNaissance)");

    query.bindValue(":cin", cin);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);
    query.bindValue(":adresse", adresse);
    query.bindValue(":dateNaissance", dateNaissance);

    return query.exec();
}

QSqlQueryModel* Client::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CIN_CLIENT, NOM, PRENOM, TELEPHONE, EMAIL, ADRESSE, DATEN FROM CLIENT");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date Naissance"));

    return model;
}

bool Client::supprimer(int cin)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENT WHERE CIN_CLIENT = :cin");
    query.bindValue(":cin", cin);

    return query.exec();
}

bool Client::modifier(int cin)
{
    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET NOM = :nom, PRENOM = :prenom, TELEPHONE = :telephone, "
                  "EMAIL = :email, ADRESSE = :adresse, DATEN = :dateNaissance "
                  "WHERE CIN_CLIENT = :cin");

    query.bindValue(":cin", cin);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);
    query.bindValue(":adresse", adresse);
    query.bindValue(":dateNaissance", dateNaissance);

    return query.exec();
}

QSqlQueryModel* Client::rechercher(QString critere, QString valeur)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString requete = "SELECT * FROM CLIENT WHERE ";

    if(critere == "Nom") {
        requete += "NOM LIKE :valeur";
    } else if(critere == "Email") {
        requete += "EMAIL LIKE :valeur";
    } else if(critere == "Téléphone") {
        requete += "TELEPHONE LIKE :valeur";
    }

    QSqlQuery query;
    query.prepare(requete);
    query.bindValue(":valeur", "%" + valeur + "%");
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
        return model;
    }

    model->setQuery(std::move(query));
    return model;
}
