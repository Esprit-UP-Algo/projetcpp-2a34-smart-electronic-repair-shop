#ifndef REPARATION_H
#define REPARATION_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>

class Reparation
{
private:
    int IDR;
    QString MAT_REP;
    QString DES_PANNE;
    QDate DATE_FIN_EST;
    QDate DATE_REC;
    QString STATUT_R;
    double COUT;
    QString NUM_SERIE;
    int CIN_EMP;

public:
    Reparation();
    Reparation(int, QString, QString, QDate, QDate, QString, double, QString, int);

    // Getters
    int getIDR() const { return IDR; }
    QString getMAT_REP() const { return MAT_REP; }
    QString getDES_PANNE() const { return DES_PANNE; }
    QDate getDATE_FIN_EST() const { return DATE_FIN_EST; }
    QDate getDATE_REC() const { return DATE_REC; }
    QString getSTATUT_R() const { return STATUT_R; }
    double getCOUT() const { return COUT; }
    QString getNUM_SERIE() const { return NUM_SERIE; }
    int getCIN_EMP() const { return CIN_EMP; }

    // Setters
    void setIDR(int id) { IDR = id; }
    void setMAT_REP(QString mat) { MAT_REP = mat; }
    void setDES_PANNE(QString des) { DES_PANNE = des; }
    void setDATE_FIN_EST(QDate date) { DATE_FIN_EST = date; }
    void setDATE_REC(QDate date) { DATE_REC = date; }
    void setSTATUT_R(QString statut) { STATUT_R = statut; }
    void setCOUT(double cout) { COUT = cout; }
    void setNUM_SERIE(QString num) { NUM_SERIE = num; }
    void setCIN_EMP(int cin) { CIN_EMP = cin; }

    // CRUD operations
    bool ajouter();
    bool supprimer(int id);
    bool modifier(int id);
    QSqlQueryModel* rechercher(const QString &critere);

private:
    // Helper methods for debugging
    bool tryFullInsert();
    bool tryAlternativeInsert();
    bool checkNullConstraints();
};

#endif // REPARATION_H
