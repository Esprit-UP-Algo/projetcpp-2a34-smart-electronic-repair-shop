#include "reparations.h"
#include <QMessageBox>

Reparations::Reparations() {}

Reparations::Reparations(int matApp, QString descriptionPanne, QDate dateReception,
                         QDate dateFin, QString statut, double cout, int cinEmploye, int numSerie)
{
    this->matApp = matApp;
    this->descriptionPanne = descriptionPanne;
    this->dateReception = dateReception;
    this->dateFin = dateFin;
    this->statut = statut;
    this->cout = cout;
    this->cinEmploye = cinEmploye;
    this->numSerie = numSerie;
}

bool Reparations::validerMatApp(int matApp)
{
    return (matApp > 0);
}

bool Reparations::validerCout(double cout)
{
    return (cout >= 0);
}

bool Reparations::validerDates(QDate reception, QDate fin)
{
    return (fin >= reception);
}

bool Reparations::existeDeja(int matApp)
{
    if (!validerMatApp(matApp)) {
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT MAT_APP FROM REPARATIONS WHERE MAT_APP = :matApp");
    query.bindValue(":matApp", matApp);

    if(query.exec() && query.next()) {
        return true;
    }
    return false;
}

bool Reparations::ajouter()
{
    // Validation des données
    if (!validerMatApp(matApp)) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le matricule doit être un nombre positif!");
        return false;
    }

    if (!validerCout(cout)) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le coût ne peut pas être négatif!");
        return false;
    }

    if (!validerDates(dateReception, dateFin)) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "La date de fin ne peut pas être avant la date de réception!");
        return false;
    }

    // Vérifier si le matricule existe déjà
    if(existeDeja(matApp)) {
        QMessageBox::warning(nullptr, "Attention", "Ce matricule de réparation existe déjà dans la base de données!");
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO REPARATIONS (MAT_APP, DES_PANNE, DATE_REC, DATE_FIN, STATUT, COUT, CIN_EMPLOYER, NUM_SERIE) "
                  "VALUES (:matApp, :descriptionPanne, :dateReception, :dateFin, :statut, :cout, :cinEmploye, :numSerie)");

    query.bindValue(":matApp", matApp);
    query.bindValue(":descriptionPanne", descriptionPanne);
    query.bindValue(":dateReception", dateReception);
    query.bindValue(":dateFin", dateFin);
    query.bindValue(":statut", statut);
    query.bindValue(":cout", cout);
    query.bindValue(":cinEmploye", cinEmploye);
    query.bindValue(":numSerie", numSerie);

    return query.exec();
}

QSqlQueryModel* Reparations::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT MAT_APP, DES_PANNE, DATE_REC, DATE_FIN, STATUT, COUT, CIN_EMPLOYER, NUM_SERIE FROM REPARATIONS");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Matricule"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Description Panne"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Réception"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Fin"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Coût"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("CIN Employé"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Numéro Série"));

    return model;
}

bool Reparations::supprimer(int matApp)
{
    QSqlQuery query;
    query.prepare("DELETE FROM REPARATIONS WHERE MAT_APP = :matApp");
    query.bindValue(":matApp", matApp);

    return query.exec();
}

bool Reparations::modifier(int matApp)
{
    QSqlQuery query;
    query.prepare("UPDATE REPARATIONS SET DES_PANNE = :descriptionPanne, DATE_REC = :dateReception, "
                  "DATE_FIN = :dateFin, STATUT = :statut, COUT = :cout, CIN_EMPLOYER = :cinEmploye, "
                  "NUM_SERIE = :numSerie WHERE MAT_APP = :matApp");

    query.bindValue(":matApp", matApp);
    query.bindValue(":descriptionPanne", descriptionPanne);
    query.bindValue(":dateReception", dateReception);
    query.bindValue(":dateFin", dateFin);
    query.bindValue(":statut", statut);
    query.bindValue(":cout", cout);
    query.bindValue(":cinEmploye", cinEmploye);
    query.bindValue(":numSerie", numSerie);

    return query.exec();
}

QSqlQueryModel* Reparations::rechercher(QString critere, QString valeur)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString requete = "SELECT * FROM REPARATIONS WHERE ";

    if(critere == "Appareil") {
        requete += "NUM_SERIE IN (SELECT NUM_SERIE FROM APPAREILLES WHERE MARQUE LIKE :valeur)";
    } else if(critere == "Statut") {
        requete += "STATUT LIKE :valeur";
    } else if(critere == "Date") {
        requete += "DATE_REC = :valeur";
    }

    QSqlQuery query;
    query.prepare(requete);
    query.bindValue(":valeur", "%" + valeur + "%");
    query.exec();

    model->setQuery(query);
    return model;
}

QSqlQueryModel* Reparations::getAppareilsDisponibles()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT NUM_SERIE, MARQUE, MODELE FROM APPAREILLES");
    return model;
}

QSqlQueryModel* Reparations::getEmployesDisponibles()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CIN_EMPLOYER, NOM, PRENOM FROM EMPLOYER");
    return model;
}
