#include "reparations.h"
#include <QMessageBox>
#include <QSqlError>

Reparations::Reparations() {}

Reparations::Reparations(int idr, QString descriptionPanne, QDate dateReception,
                         QDate dateFinEstimee, QString statut, double cout,
                         int cinEmploye, int numSerie, QString matRep)
{
    this->idr = idr;
    this->descriptionPanne = descriptionPanne;
    this->dateReception = dateReception;
    this->dateFinEstimee = dateFinEstimee;
    this->statut = statut;
    this->cout = cout;
    this->cinEmploye = cinEmploye;
    this->numSerie = numSerie;
    this->matRep = matRep;
}

bool Reparations::validerIdr(int idr)
{
    return (idr > 0);
}

bool Reparations::validerCout(double cout)
{
    return (cout >= 0);
}

bool Reparations::validerDates(QDate reception, QDate fin)
{
    return (fin >= reception);
}

bool Reparations::existeDeja(int idr)
{
    if (!validerIdr(idr)) {
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT IDR FROM REPARATIONS WHERE IDR = :idr");
    query.bindValue(":idr", idr);

    if(query.exec() && query.next()) {
        return true;
    }
    return false;
}

bool Reparations::ajouter()
{
    // Validation des données
    if (!validerIdr(idr)) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "L'ID de réparation doit être un nombre positif!");
        return false;
    }

    if (!validerCout(cout)) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le coût ne peut pas être négatif!");
        return false;
    }

    if (!validerDates(dateReception, dateFinEstimee)) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "La date de fin estimée ne peut pas être avant la date de réception!");
        return false;
    }

    // Vérifier si l'ID existe déjà
    if(existeDeja(idr)) {
        QMessageBox::warning(nullptr, "Attention", "Cet ID de réparation existe déjà dans la base de données!");
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO REPARATIONS (IDR, DES_PANNE, DATE_REC, DATE_FIN_EST, STATUT_R, COUT, CIN_EMP, NUM_SERIE, MAT_REP) "
                  "VALUES (:idr, :descriptionPanne, :dateReception, :dateFinEstimee, :statut, :cout, :cinEmploye, :numSerie, :matRep)");

    query.bindValue(":idr", idr);
    query.bindValue(":descriptionPanne", descriptionPanne);
    query.bindValue(":dateReception", dateReception);
    query.bindValue(":dateFinEstimee", dateFinEstimee);
    query.bindValue(":statut", statut);
    query.bindValue(":cout", cout);
    query.bindValue(":cinEmploye", cinEmploye);
    query.bindValue(":numSerie", numSerie);
    query.bindValue(":matRep", matRep);

    return query.exec();
}

QSqlQueryModel* Reparations::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT IDR, DES_PANNE, DATE_REC, DATE_FIN_EST, STATUT_R, COUT, CIN_EMP, NUM_SERIE, MAT_REP FROM REPARATIONS");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Réparation"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Description Panne"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Réception"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Fin Estimée"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Coût"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("CIN Employé"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Numéro Série"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Matricule Réparation"));

    return model;
}

bool Reparations::supprimer(int idr)
{
    QSqlQuery query;
    query.prepare("DELETE FROM REPARATIONS WHERE IDR = :idr");
    query.bindValue(":idr", idr);

    return query.exec();
}

bool Reparations::modifier(int idr)
{
    QSqlQuery query;
    query.prepare("UPDATE REPARATIONS SET DES_PANNE = :descriptionPanne, DATE_REC = :dateReception, "
                  "DATE_FIN_EST = :dateFinEstimee, STATUT_R = :statut, COUT = :cout, CIN_EMP = :cinEmploye, "
                  "NUM_SERIE = :numSerie, MAT_REP = :matRep WHERE IDR = :idr");

    query.bindValue(":idr", idr);
    query.bindValue(":descriptionPanne", descriptionPanne);
    query.bindValue(":dateReception", dateReception);
    query.bindValue(":dateFinEstimee", dateFinEstimee);
    query.bindValue(":statut", statut);
    query.bindValue(":cout", cout);
    query.bindValue(":cinEmploye", cinEmploye);
    query.bindValue(":numSerie", numSerie);
    query.bindValue(":matRep", matRep);

    return query.exec();
}

QSqlQueryModel* Reparations::rechercher(QString critere, QString valeur)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString requete = "SELECT * FROM REPARATIONS WHERE ";

    if(critere == "Appareil") {
        requete += "NUM_SERIE IN (SELECT NUM_SERIE FROM APPAREILLES WHERE MARQUE LIKE :valeur)";
    } else if(critere == "Statut") {
        requete += "STATUT_R LIKE :valeur";
    } else if(critere == "Date") {
        requete += "DATE_REC = :valeur";
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

QSqlQueryModel* Reparations::getAppareilsDisponibles()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query("SELECT NUM_SERIE, MARQUE, MODELE FROM APPAREILLES");
    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des appareils disponibles:" << query.lastError().text();
        return model;
    }
    model->setQuery(std::move(query));
    return model;
}

QSqlQueryModel* Reparations::getEmployesDisponibles()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CIN_EMPLOYER, NOM, PRENOM FROM EMPLOYER");
    return model;
}
