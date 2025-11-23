#include "employe.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QWidget>
#include <QVBoxLayout>

Employe::Employe(int cin, QString nom, QString prenom, QString tel, QString email, QString presence)
{
    CINEM = cin;
    NOM = nom;
    PRENOM = prenom;
    TELEPHONE = tel;
    EMAIL = email;
    PRESENCE = presence;
}

int Employe::getCINEM() const { return CINEM; }
QString Employe::getNOM() const { return NOM; }
QString Employe::getPRENOM() const { return PRENOM; }
QString Employe::getTELEPHONE() const { return TELEPHONE; }
QString Employe::getEMAIL() const { return EMAIL; }
QString Employe::getPRESENCE() const { return PRESENCE; }

void Employe::setCINEM(int cin) { CINEM = cin; }
void Employe::setNOM(QString nom) { NOM = nom; }
void Employe::setPRENOM(QString prenom) { PRENOM = prenom; }
void Employe::setTELEPHONE(QString tel) { TELEPHONE = tel; }
void Employe::setEMAIL(QString email) { EMAIL = email; }
void Employe::setPRESENCE(QString presence) { PRESENCE = presence; }

bool Employe::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE (CINEM, NOM, PRENOM, TELEPHONE, EMAIL, PRESENCE) "
                  "VALUES (:cin, :nom, :prenom, :tel, :email, :presence)");

    query.bindValue(":cin", CINEM);
    query.bindValue(":nom", NOM);
    query.bindValue(":prenom", PRENOM);
    query.bindValue(":tel", TELEPHONE);
    query.bindValue(":email", EMAIL);
    query.bindValue(":presence", PRESENCE);

    return query.exec();
}

QSqlQueryModel *Employe::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT CINEM, NOM, PRENOM, TELEPHONE, EMAIL, PRESENCE FROM EMPLOYE");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CINEM"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PRESENCE"));

    return model;
}

bool Employe::supprimer(int cin)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYE WHERE CINEM = :cin");
    query.bindValue(":cin", cin);
    return query.exec();
}

bool Employe::modifier(int cin)
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE SET NOM=:nom, PRENOM=:prenom, TELEPHONE=:tel, EMAIL=:email, "
                  "PRESENCE=:presence WHERE CINEM=:cin");

    query.bindValue(":cin", cin);
    query.bindValue(":nom", NOM);
    query.bindValue(":prenom", PRENOM);
    query.bindValue(":tel", TELEPHONE);
    query.bindValue(":email", EMAIL);
    query.bindValue(":presence", PRESENCE);

    return query.exec();
}

QSqlQueryModel *Employe::rechercherEmploye(QString recherche)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    // Recherche par NOM uniquement
    QSqlQuery query;
    query.prepare("SELECT CINEM, NOM, PRENOM, TELEPHONE, EMAIL, PRESENCE FROM EMPLOYE "
                  "WHERE UPPER(NOM) LIKE UPPER(:recherche)");
    query.bindValue(":recherche", "%" + recherche + "%");

    if (query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "Erreur recherche:" << query.lastError().text();
        // En cas d'erreur, retourner un modèle vide
        model->setQuery("SELECT CINEM, NOM, PRENOM, TELEPHONE, EMAIL, PRESENCE FROM EMPLOYE WHERE 1=0");
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CINEM"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PRESENCE"));

    return model;
}

QSqlQueryModel *Employe::trier(QString tri)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString queryString;

    if(tri == "par défaut"){
        queryString = "SELECT CINEM, NOM, PRENOM, TELEPHONE, EMAIL, PRESENCE FROM EMPLOYE";
    }
    else if(tri == "NOM"){
        queryString = "SELECT CINEM, NOM, PRENOM, TELEPHONE, EMAIL, PRESENCE FROM EMPLOYE ORDER BY NOM ASC";
    }
    else {
        queryString = "SELECT CINEM, NOM, PRENOM, TELEPHONE, EMAIL, PRESENCE FROM EMPLOYE ORDER BY CINEM";
    }

    model->setQuery(queryString);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CINEM"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PRESENCE"));

    return model;
}

QChartView* Employe::DiagrammeCirculaire() {
    QSqlQuery query;
    QPieSeries *series = new QPieSeries();

    query.prepare("SELECT PRESENCE, COUNT(*) AS count FROM EMPLOYE GROUP BY PRESENCE");

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête : " << query.lastError();
        delete series;
        return nullptr;
    }

    while (query.next()) {
        QString PRESENCE = query.value(0).toString();
        int count = query.value(1).toInt();
        series->append(PRESENCE, count);
    }

    QList<QColor> couleurs = {
        QColor("#0D47A1"),
        QColor("#42A5F5"),
        QColor("#FF7043"),
        QColor("#4CAF50"),
        QColor("#FF9800")
    };

    int couleurIndex = 0;
    for (QPieSlice *slice : series->slices()) {
        QColor couleur = couleurs[couleurIndex % couleurs.size()];
        couleurIndex++;
        slice->setBrush(couleur);
        slice->setLabel(slice->label() + " (" + QString::number(slice->percentage() * 100, 'f', 1) + "%)");

        QObject::connect(slice, &QPieSlice::hovered, [slice](bool state) {
            slice->setExploded(state);
            slice->setLabelVisible(state);
        });
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des employés par présence");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}

void Employe::afficherDiagramme_Emp_Stat() {
    QChartView* chartView = DiagrammeCirculaire();
    if (chartView) {
        QWidget *window = new QWidget();
        window->setWindowTitle("Statistiques des Employés");
        QVBoxLayout *layout = new QVBoxLayout();
        layout->addWidget(chartView);
        window->setLayout(layout);
        window->resize(800, 600);
        window->show();
    } else {
        QMessageBox::critical(nullptr, "Erreur", "Erreur lors de la création du diagramme.");
    }
}
