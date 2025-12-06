#ifndef STATISTICS_H
#define STATISTICS_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QPieSeries>
#include <QBarSeries>
#include <QBarSet>
#include <QLineSeries>
#include <QValueAxis>
#include <QSqlQuery>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>

class Statistics : public QWidget
{
    Q_OBJECT

public:
    explicit Statistics(QWidget *parent = nullptr);
    void refreshAllStats();

private:
    void setupUI();
    void createClientStats();
    void createTechnicalStats();
    void createFinancialStats();

    // Méthodes de calcul des statistiques
    QMap<QString, int> getClientStats();
    QMap<QString, int> getTechnicalStats();
    QMap<QString, double> getFinancialStats();
    QMap<QString, int> getTopClients();
    QMap<QString, int> getDeviceTypesStats();
    QMap<QString, int> getBrandStats();
    QMap<QString, int> getFrequentIssues();

    // Widgets
    QChartView *clientChartView;
    QChartView *technicalChartView;
    QChartView *financialChartView;

    QLabel *totalClientsLabel;
    QLabel *newClientsMonthLabel;
    QLabel *avgDevicesPerClientLabel;
    QLabel *totalRevenueLabel;
    QLabel *revenuePerDeviceLabel;
    QLabel *functionalDevicesLabel;
    QLabel *brokenDevicesLabel;
};

#endif // STATISTICS_H
