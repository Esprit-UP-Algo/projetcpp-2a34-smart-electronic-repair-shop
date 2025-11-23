#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employe.h"

class MailingService;

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
    void on_btnAjouter_4_clicked();
    void on_btnModifier_4_clicked();
    void on_btnSupprimer_4_clicked();
    void on_tableViewAppareils_4_clicked(const QModelIndex &index);
    void on_btnRechercher_4_clicked();
    void on_btnReinitialiser_4_clicked();
    void on_btnExporterPDF_4_clicked();
    void on_btnGenererStats_4_clicked();

    void on_btnAjouter_5_clicked();
    void on_btnAjouter_6_clicked();
    void on_btnSendRealEmail_clicked();
    void on_btnSendPdfEmail_clicked();  // AJOUTEZ CETTE LIGNE
    void onEmailSent(bool success, const QString& message);

private:
    void setupValidators();
    void setupRechercheField();
    void setupMailingService();
    bool validateFields();
    QString getRechercheText();
    void setRechercheFocus();
    void showConfigurationDialog();
    QString generatePdf();

    Employe emp;
    MailingService *m_mailingService;
    Ui::MainWindow *ui;
    QString m_lastPdfPath;
};

#endif // MAINWINDOW_H
