// reparations.cpp
#include "reparations.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>

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

bool Reparations::validerIdr(int idr) { return (idr > 0); }
bool Reparations::validerCout(double cout) { return (cout >= 0); }
bool Reparations::validerDates(QDate reception, QDate fin) { return (fin >= reception); }

bool Reparations::existeDeja(int idr)
{
    if (!validerIdr(idr)) return false;

    QSqlQuery query;
    query.prepare("SELECT IDR FROM SIRINE.REPARATIONS WHERE IDR = :idr");
    query.bindValue(":idr", idr);

    if (query.exec() && query.next()) return true;
    return false;
}

bool Reparations::ajouter()
{
    if (!validerIdr(idr)) {
        QMessageBox::warning(nullptr, "Erreur", "ID Réparation invalide !");
        return false;
    }
    if (!validerCout(cout)) {
        QMessageBox::warning(nullptr, "Erreur", "Le coût doit être positif !");
        return false;
    }
    if (!validerDates(dateReception, dateFinEstimee)) {
        QMessageBox::warning(nullptr, "Erreur", "Date fin estimée invalide !");
        return false;
    }
    if (existeDeja(idr)) {
        QMessageBox::warning(nullptr, "Doublon", "Cet ID existe déjà !");
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO SIRINE.REPARATIONS (IDR, DES_PANNE, DATE_REC, DATE_FIN_EST, STATUT_R, COUT, CIN_EMP, NUM_SERIE, MAT_REP) "
                  "VALUES (:idr, :des, :rec, :fin, :statut, :cout, :cin_emp, :num_serie, :mat_rep)");

    query.bindValue(":idr", idr);
    query.bindValue(":des", descriptionPanne);
    query.bindValue(":rec", dateReception);
    query.bindValue(":fin", dateFinEstimee);
    query.bindValue(":statut", statut);
    query.bindValue(":cout", cout);
    query.bindValue(":cin_emp", cinEmploye);
    query.bindValue(":num_serie", numSerie);
    query.bindValue(":mat_rep", matRep);

    return query.exec();
}

QSqlQueryModel* Reparations::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT IDR, DES_PANNE, DATE_REC, DATE_FIN_EST, STATUT_R, COUT, CIN_EMP, NUM_SERIE, MAT_REP FROM SIRINE.REPARATIONS");

    model->setHeaderData(0, Qt::Horizontal, "ID Réparation");
    model->setHeaderData(1, Qt::Horizontal, "Description");
    model->setHeaderData(2, Qt::Horizontal, "Date Réception");
    model->setHeaderData(3, Qt::Horizontal, "Date Fin Estimée");
    model->setHeaderData(4, Qt::Horizontal, "Statut");
    model->setHeaderData(5, Qt::Horizontal, "Coût");
    model->setHeaderData(6, Qt::Horizontal, "CIN Employé");
    model->setHeaderData(7, Qt::Horizontal, "N° Série");
    model->setHeaderData(8, Qt::Horizontal, "Matricule");

    return model;
}

bool Reparations::supprimer(int idr)
{
    QSqlQuery query;
    query.prepare("DELETE FROM SIRINE.REPARATIONS WHERE IDR = :idr");
    query.bindValue(":idr", idr);
    return query.exec();
}

bool Reparations::modifier(int idr)
{
    QSqlQuery query;
    query.prepare("UPDATE SIRINE.REPARATIONS SET "
                  "DES_PANNE = :des, DATE_REC = :rec, DATE_FIN_EST = :fin, "
                  "STATUT_R = :statut, COUT = :cout, CIN_EMP = :cin_emp, "
                  "NUM_SERIE = :num_serie, MAT_REP = :mat_rep "
                  "WHERE IDR = :idr");

    query.bindValue(":idr", idr);
    query.bindValue(":des", descriptionPanne);
    query.bindValue(":rec", dateReception);
    query.bindValue(":fin", dateFinEstimee);
    query.bindValue(":statut", statut);
    query.bindValue(":cout", cout);
    query.bindValue(":cin_emp", cinEmploye);
    query.bindValue(":num_serie", numSerie);
    query.bindValue(":mat_rep", matRep);

    return query.exec();
}

QSqlQueryModel* Reparations::rechercher(QString critere, QString valeur)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString requete = "SELECT * FROM SIRINE.REPARATIONS WHERE ";

    if (critere == "Appareil") {
        requete += "NUM_SERIE IN (SELECT NUM_SERIE FROM SIRINE.APPAREILLES WHERE MARQUE LIKE :valeur)";
    } else if (critere == "Statut") {
        requete += "STATUT_R LIKE :valeur";
    } else if (critere == "Date") {
        requete += "DATE_REC = :valeur";
    } else {
        requete += "1=1";
    }

    QSqlQuery query;
    query.prepare(requete);
    query.bindValue(":valeur", "%" + valeur + "%");

    if (query.exec()) {
        model->setQuery(std::move(query));
    } else {
        qDebug() << "Erreur recherche:" << query.lastError().text();
    }
    return model;
}

QSqlQueryModel* Reparations::getAppareilsDisponibles()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT NUM_SERIE, MARQUE, MODELE FROM SIRINE.APPAREILLES");
    return model;
}

QSqlQueryModel* Reparations::getEmployesDisponibles()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CIN_EMPLOYER, NOM, PRENOM FROM SIRINE.EMPLOYER");
    return model;
}
