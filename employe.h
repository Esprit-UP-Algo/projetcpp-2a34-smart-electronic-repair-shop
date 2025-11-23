#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>

class Employe
{
private:
    int CINEM;
    QString NOM;
    QString PRENOM;
    QString TELEPHONE;
    QString EMAIL;
    QString PRESENCE;

public:
    Employe() {}
    Employe(int cin, QString nom, QString prenom, QString tel, QString email, QString presence);

    int getCINEM() const;
    QString getNOM() const;
    QString getPRENOM() const;
    QString getTELEPHONE() const;
    QString getEMAIL() const;
    QString getPRESENCE() const;

    void setCINEM(int cin);
    void setNOM(QString nom);
    void setPRENOM(QString prenom);
    void setTELEPHONE(QString tel);
    void setEMAIL(QString email);
    void setPRESENCE(QString presence);

    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int cin);
    bool modifier(int cin);

    QSqlQueryModel *rechercherEmploye(QString recherche);
    void afficherDiagramme_Emp_Stat();
    QChartView* DiagrammeCirculaire();
    QSqlQueryModel *trier(QString tri);
};

#endif // EMPLOYE_H
