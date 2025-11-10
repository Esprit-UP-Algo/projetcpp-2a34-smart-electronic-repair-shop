#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QRegularExpression>
#include <QToolTip>
#include <QPoint>
#include "empolye.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAjouter_clicked();
    void on_btnModifier_clicked();
    void on_btnSupprimer_clicked();
    void on_btnRafraichir_clicked();
    void on_tableView_clicked(const QModelIndex &index);
    void on_tableViewAppareils_clicked(const QModelIndex &index);

    // Slots pour validation en temps réel
    void validerCIN();
    void validerNom();
    void validerPrenom();
    void validerTelephone();
    void validerEmail();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *model;

    void setupDatabase();
    void chargerDonnees();
    void viderChamps();
    bool validerDonnees(QString cin, QString nom, QString prenom, QString numTel, QString email);
};

#endif // MAINWINDOW_H
