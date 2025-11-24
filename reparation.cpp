#include "reparation.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Reparation::Reparation()
{
    IDR = 0;
    MAT_REP = "";
    DES_PANNE = "";
    DATE_FIN_EST = QDate::currentDate();
    DATE_REC = QDate::currentDate();
    STATUT_R = "";
    COUT = 0.0;
    NUM_SERIE = "";
    CIN_EMP = 0;
}

Reparation::Reparation(int id, QString mat, QString des, QDate fin, QDate rec, QString statut, double cout, QString num_serie, int cin_emp)
{
    IDR = id;
    MAT_REP = mat;
    DES_PANNE = des;
    DATE_FIN_EST = fin;
    DATE_REC = rec;
    STATUT_R = statut;
    COUT = cout;
    NUM_SERIE = num_serie;
    CIN_EMP = cin_emp;
}

bool Reparation::ajouter()
{
    QSqlQuery query;

    qDebug() << "=== ATTEMPTING INSERT WITH CORRECT DATA TYPES ===";

    // Use TO_DATE for Oracle date conversion with proper format
    query.prepare("INSERT INTO REPARATION (IDR, MAT_REP, DES_PANNE, DATE_FIN_EST, DATE_REC, STATUT_R, COUT, NUM_SERIE, CIN_EMP) "
                  "VALUES (:id, :mat, :des, :fin, :rec, :statut, :cout, :num_serie, :cin_emp)");

    // Bind values with explicit data types
    query.bindValue(":id", IDR); // NUMBER
    query.bindValue(":mat", MAT_REP); // VARCHAR2(60)
    query.bindValue(":des", DES_PANNE); // VARCHAR2(30)
    query.bindValue(":fin", DATE_FIN_EST); // DATE
    query.bindValue(":rec", DATE_REC); // DATE
    query.bindValue(":statut", STATUT_R); // VARCHAR2(30)
    query.bindValue(":cout", COUT); // NUMBER
    query.bindValue(":num_serie", NUM_SERIE); // VARCHAR2(20)
    query.bindValue(":cin_emp", CIN_EMP); // NUMBER

    qDebug() << "Data types being inserted:";
    qDebug() << "  IDR (NUMBER):" << IDR;
    qDebug() << "  MAT_REP (VARCHAR2(60)):" << MAT_REP;
    qDebug() << "  DES_PANNE (VARCHAR2(30)):" << DES_PANNE;
    qDebug() << "  DATE_FIN_EST (DATE):" << DATE_FIN_EST;
    qDebug() << "  DATE_REC (DATE):" << DATE_REC;
    qDebug() << "  STATUT_R (VARCHAR2(30)):" << STATUT_R;
    qDebug() << "  COUT (NUMBER):" << COUT;
    qDebug() << "  NUM_SERIE (VARCHAR2(20)):" << NUM_SERIE;
    qDebug() << "  CIN_EMP (NUMBER):" << CIN_EMP;

    // Check string lengths against VARCHAR2 limits
    if (MAT_REP.length() > 60) {
        qDebug() << "✗ ERROR: MAT_REP too long (max 60, got" << MAT_REP.length() << ")";
        return false;
    }
    if (DES_PANNE.length() > 30) {
        qDebug() << "✗ ERROR: DES_PANNE too long (max 30, got" << DES_PANNE.length() << ")";
        return false;
    }
    if (STATUT_R.length() > 30) {
        qDebug() << "✗ ERROR: STATUT_R too long (max 30, got" << STATUT_R.length() << ")";
        return false;
    }
    if (NUM_SERIE.length() > 20) {
        qDebug() << "✗ ERROR: NUM_SERIE too long (max 20, got" << NUM_SERIE.length() << ")";
        return false;
    }

    if (query.exec()) {
        qDebug() << "✓ INSERT SUCCESSFUL!";
        return true;
    } else {
        qDebug() << "✗ INSERT FAILED:" << query.lastError().text();
        qDebug() << "  Database error:" << query.lastError().databaseText();
        qDebug() << "  Driver error:" << query.lastError().driverText();

        // Try alternative approach without TO_DATE
        qDebug() << "=== TRYING ALTERNATIVE APPROACH ===";
        return tryAlternativeInsert();
    }
}

bool Reparation::tryAlternativeInsert()
{
    QSqlQuery query;

    qDebug() << "=== TRYING INSERT WITH ORACLE DATE LITERALS ===";

    // Use Oracle date literals instead of TO_DATE
    QString sql = QString(
                      "INSERT INTO REPARATION (IDR, MAT_REP, DES_PANNE, DATE_FIN_EST, DATE_REC, STATUT_R, COUT, NUM_SERIE, CIN_EMP) "
                      "VALUES (%1, '%2', '%3', DATE '%4', DATE '%5', '%6', %7, '%8', %9)"
                      ).arg(IDR)
                      .arg(MAT_REP)
                      .arg(DES_PANNE)
                      .arg(DATE_FIN_EST.toString("yyyy-MM-dd"))
                      .arg(DATE_REC.toString("yyyy-MM-dd"))
                      .arg(STATUT_R)
                      .arg(COUT)
                      .arg(NUM_SERIE)
                      .arg(CIN_EMP);

    qDebug() << "Executing SQL:" << sql;

    if (query.exec(sql)) {
        qDebug() << "✓ ALTERNATIVE INSERT SUCCESSFUL!";
        return true;
    } else {
        qDebug() << "✗ ALTERNATIVE INSERT FAILED:" << query.lastError().text();

        // Final attempt: Check if there are NULL constraints
        qDebug() << "=== CHECKING FOR NULL CONSTRAINTS ===";
        return checkNullConstraints();
    }
}

bool Reparation::checkNullConstraints()
{
    QSqlQuery query;

    // Check which columns have NOT NULL constraints
    QSqlQuery constraintQuery;
    if (constraintQuery.exec(
            "SELECT column_name, nullable FROM user_tab_columns "
            "WHERE table_name = 'REPARATION' AND nullable = 'N'"))
    {
        qDebug() << "Columns with NOT NULL constraint:";
        while (constraintQuery.next()) {
            QString column = constraintQuery.value(0).toString();
            qDebug() << "  - " << column;

            // Check if we're providing values for NOT NULL columns
            if (column == "IDR" && IDR == 0) {
                qDebug() << "✗ ERROR: IDR is NOT NULL but value is 0";
            }
            if (column == "NUM_SERIE" && NUM_SERIE.isEmpty()) {
                qDebug() << "✗ ERROR: NUM_SERIE is NOT NULL but value is empty";
            }
            if (column == "CIN_EMP" && CIN_EMP == 0) {
                qDebug() << "✗ ERROR: CIN_EMP is NOT NULL but value is 0";
            }
        }
    }

    return false;
}

bool Reparation::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM REPARATION WHERE IDR = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        qDebug() << "✓ Réparation supprimée avec succès!";
        return true;
    } else {
        qDebug() << "✗ Erreur lors de la suppression:" << query.lastError().text();
        return false;
    }
}

bool Reparation::modifier(int id)
{
    QSqlQuery query;

    query.prepare("UPDATE REPARATION SET "
                  "MAT_REP = :mat, "
                  "DES_PANNE = :des, "
                  "DATE_FIN_EST = :fin, "
                  "DATE_REC = :rec, , "
                  "STATUT_R = :statut, "
                  "COUT = :cout, "
                  "NUM_SERIE = :num_serie, "
                  "CIN_EMP = :cin_emp "
                  "WHERE IDR = :id");

    query.bindValue(":id", id);
    query.bindValue(":mat", MAT_REP);
    query.bindValue(":des", DES_PANNE);
    query.bindValue(":fin", DATE_FIN_EST);
    query.bindValue(":rec", DATE_REC);
    query.bindValue(":statut", STATUT_R);
    query.bindValue(":cout", COUT);
    query.bindValue(":num_serie", NUM_SERIE);
    query.bindValue(":cin_emp", CIN_EMP);

    if (query.exec()) {
        qDebug() << "✓ Réparation modifiée avec succès!";
        return true;
    } else {
        qDebug() << "✗ Erreur lors de la modification:" << query.lastError().text();
        return false;
    }
}

QSqlQueryModel* Reparation::rechercher(const QString &critere)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QString queryString = "SELECT * FROM REPARATION WHERE "
                          "IDR LIKE '%" + critere + "%' OR "
                                      "MAT_REP LIKE '%" + critere + "%' OR "
                                      "DES_PANNE LIKE '%" + critere + "%' OR "
                                      "STATUT_R LIKE '%" + critere + "%' OR "
                                      "NUM_SERIE LIKE '%" + critere + "%' OR "
                                      "CIN_EMP LIKE '%" + critere + "%'";

    model->setQuery(queryString);

    if (model->lastError().isValid()) {
        qDebug() << "Erreur recherche:" << model->lastError().text();
    }

    return model;
}
