#include "statistics.h"
#include <QSqlQuery>
#include <QDate>
#include <QLegend>
#include <QPainter>

Statistics::Statistics(QWidget *parent) : QWidget(parent)
{
    setupUI();
    refreshAllStats();
}

void Statistics::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Titre
    QLabel *titleLabel = new QLabel("📊 Tableau de Bord - Statistiques Avancées");
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #2c3147; margin: 10px;");
    mainLayout->addWidget(titleLabel);

    // Layout pour les indicateurs clés
    QHBoxLayout *indicatorsLayout = new QHBoxLayout();

    // Indicateurs clients
    QGroupBox *clientIndicators = new QGroupBox("👥 Indicateurs Clients");
    clientIndicators->setStyleSheet("QGroupBox { font-weight: bold; color: #17A2B8; border: 2px solid #17A2B8; border-radius: 8px; background-color: white; }");
    QVBoxLayout *clientIndLayout = new QVBoxLayout(clientIndicators);
    totalClientsLabel = new QLabel("Total: Chargement...");
    newClientsMonthLabel = new QLabel("Nouveaux/mois: Chargement...");
    avgDevicesPerClientLabel = new QLabel("Moy. appareils: Chargement...");
    totalClientsLabel->setStyleSheet("font-size: 12px; padding: 5px;");
    newClientsMonthLabel->setStyleSheet("font-size: 12px; padding: 5px;");
    avgDevicesPerClientLabel->setStyleSheet("font-size: 12px; padding: 5px;");
    clientIndLayout->addWidget(totalClientsLabel);
    clientIndLayout->addWidget(newClientsMonthLabel);
    clientIndLayout->addWidget(avgDevicesPerClientLabel);

    // Indicateurs techniques
    QGroupBox *techIndicators = new QGroupBox("🔧 Indicateurs Techniques");
    techIndicators->setStyleSheet("QGroupBox { font-weight: bold; color: #FD7E14; border: 2px solid #FD7E14; border-radius: 8px; background-color: white; }");
    QVBoxLayout *techIndLayout = new QVBoxLayout(techIndicators);
    functionalDevicesLabel = new QLabel("Fonctionnels: Chargement...");
    brokenDevicesLabel = new QLabel("En panne: Chargement...");
    functionalDevicesLabel->setStyleSheet("font-size: 12px; padding: 5px;");
    brokenDevicesLabel->setStyleSheet("font-size: 12px; padding: 5px;");
    techIndLayout->addWidget(functionalDevicesLabel);
    techIndLayout->addWidget(brokenDevicesLabel);

    // Indicateurs financiers
    QGroupBox *financeIndicators = new QGroupBox("💰 Indicateurs Financiers");
    financeIndicators->setStyleSheet("QGroupBox { font-weight: bold; color: #28A745; border: 2px solid #28A745; border-radius: 8px; background-color: white; }");
    QVBoxLayout *financeIndLayout = new QVBoxLayout(financeIndicators);
    totalRevenueLabel = new QLabel("Revenu total: Chargement...");
    revenuePerDeviceLabel = new QLabel("Revenu/appareil: Chargement...");
    totalRevenueLabel->setStyleSheet("font-size: 12px; padding: 5px;");
    revenuePerDeviceLabel->setStyleSheet("font-size: 12px; padding: 5px;");
    financeIndLayout->addWidget(totalRevenueLabel);
    financeIndLayout->addWidget(revenuePerDeviceLabel);

    indicatorsLayout->addWidget(clientIndicators);
    indicatorsLayout->addWidget(techIndicators);
    indicatorsLayout->addWidget(financeIndicators);
    mainLayout->addLayout(indicatorsLayout);

    // Layout pour les graphiques
    QHBoxLayout *chartsLayout = new QHBoxLayout();

    // Graphique clients
    QGroupBox *clientChartBox = new QGroupBox("📈 Top Clients par Appareils");
    clientChartBox->setStyleSheet("QGroupBox { font-weight: bold; color: #17A2B8; border: 2px solid #17A2B8; border-radius: 8px; background-color: white; }");
    QVBoxLayout *clientChartLayout = new QVBoxLayout(clientChartBox);
    clientChartView = new QChartView();
    clientChartView->setMinimumSize(300, 250);
    clientChartView->setRenderHint(QPainter::Antialiasing);
    clientChartLayout->addWidget(clientChartView);

    // Graphique technique
    QGroupBox *techChartBox = new QGroupBox("🔧 Types d'Appareils");
    techChartBox->setStyleSheet("QGroupBox { font-weight: bold; color: #FD7E14; border: 2px solid #FD7E14; border-radius: 8px; background-color: white; }");
    QVBoxLayout *techChartLayout = new QVBoxLayout(techChartBox);
    technicalChartView = new QChartView();
    technicalChartView->setMinimumSize(300, 250);
    technicalChartView->setRenderHint(QPainter::Antialiasing);
    techChartLayout->addWidget(technicalChartView);

    // Graphique financier
    QGroupBox *financeChartBox = new QGroupBox("💰 Revenus par Marque");
    financeChartBox->setStyleSheet("QGroupBox { font-weight: bold; color: #28A745; border: 2px solid #28A745; border-radius: 8px; background-color: white; }");
    QVBoxLayout *financeChartLayout = new QVBoxLayout(financeChartBox);
    financialChartView = new QChartView();
    financialChartView->setMinimumSize(300, 250);
    financialChartView->setRenderHint(QPainter::Antialiasing);
    financeChartLayout->addWidget(financialChartView);

    chartsLayout->addWidget(clientChartBox);
    chartsLayout->addWidget(techChartBox);
    chartsLayout->addWidget(financeChartBox);
    mainLayout->addLayout(chartsLayout);
}

void Statistics::refreshAllStats()
{
    createClientStats();
    createTechnicalStats();
    createFinancialStats();
}

void Statistics::createClientStats()
{
    QMap<QString, int> clientStats = getClientStats();

    // Mise à jour des indicateurs
    totalClientsLabel->setText(QString("Total: %1 clients").arg(clientStats["total"]));
    newClientsMonthLabel->setText(QString("Nouveaux/mois: %1").arg(clientStats["new_this_month"]));
    avgDevicesPerClientLabel->setText(QString("Moy. appareils: %1").arg(clientStats["avg_devices"]));

    // Création du pie chart
    QPieSeries *series = new QPieSeries();

    QMap<QString, int> topClients = getTopClients();
    for(auto it = topClients.begin(); it != topClients.end(); ++it) {
        if(it.value() > 0) {
            QPieSlice *slice = series->append(it.key(), it.value());
            slice->setLabelVisible(true);
            slice->setLabel(QString("%1\n%2 appareils").arg(it.key()).arg(it.value()));
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Top Clients par Nombre d'Appareils");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    clientChartView->setChart(chart);
}

void Statistics::createTechnicalStats()
{
    QMap<QString, int> techStats = getTechnicalStats();

    // Mise à jour des indicateurs
    functionalDevicesLabel->setText(QString("Fonctionnels: %1").arg(techStats["functional"]));
    brokenDevicesLabel->setText(QString("En panne: %1").arg(techStats["broken"]));

    // Pie chart pour les types d'appareils
    QPieSeries *series = new QPieSeries();

    QMap<QString, int> deviceTypes = getDeviceTypesStats();
    for(auto it = deviceTypes.begin(); it != deviceTypes.end(); ++it) {
        if(it.value() > 0) {
            QPieSlice *slice = series->append(it.key(), it.value());
            slice->setLabelVisible(true);
            slice->setLabel(QString("%1\n%2 appareils").arg(it.key()).arg(it.value()));
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition par Type d'Appareil");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    technicalChartView->setChart(chart);
}

void Statistics::createFinancialStats()
{
    QMap<QString, double> financeStats = getFinancialStats();

    // Mise à jour des indicateurs
    totalRevenueLabel->setText(QString("Revenu total: %1 DT").arg(financeStats["total_revenue"], 0, 'f', 2));
    revenuePerDeviceLabel->setText(QString("Revenu/appareil: %1 DT").arg(financeStats["revenue_per_device"], 0, 'f', 2));

    // Pie chart pour les revenus par marque
    QPieSeries *series = new QPieSeries();

    // Simulation des revenus par marque
    QMap<QString, int> brands = getBrandStats();
    int totalDevices = 0;
    for(int count : brands.values()) {
        totalDevices += count;
    }

    for(auto it = brands.begin(); it != brands.end(); ++it) {
        if(it.value() > 0) {
            double revenue = (it.value() * 1.0 / totalDevices) * financeStats["total_revenue"];
            if (revenue > 0) {
                QPieSlice *slice = series->append(it.key(), revenue);
                slice->setLabelVisible(true);
                slice->setLabel(QString("%1\n%2 DT").arg(it.key()).arg(revenue, 0, 'f', 2));
            }
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des Revenus par Marque");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    financialChartView->setChart(chart);
}

// Méthodes de calcul des statistiques
QMap<QString, int> Statistics::getClientStats()
{
    QMap<QString, int> stats;

    // Total clients
    QSqlQuery query("SELECT COUNT(*) FROM CLIENT");
    if(query.exec() && query.next()) {
        stats["total"] = query.value(0).toInt();
    } else {
        stats["total"] = 0;
    }

    // Nouveaux clients ce mois
    QDate currentDate = QDate::currentDate();
    QString monthQuery = QString("SELECT COUNT(*) FROM CLIENT WHERE EXTRACT(MONTH FROM DATEN) = %1 AND EXTRACT(YEAR FROM DATEN) = %2")
                             .arg(currentDate.month())
                             .arg(currentDate.year());
    QSqlQuery newClientsQuery(monthQuery);
    if(newClientsQuery.exec() && newClientsQuery.next()) {
        stats["new_this_month"] = newClientsQuery.value(0).toInt();
    } else {
        stats["new_this_month"] = 0;
    }

    // Moyenne d'appareils par client
    QSqlQuery avgQuery("SELECT COUNT(*) FROM APPAREILLES");
    int totalDevices = 0;
    if(avgQuery.exec() && avgQuery.next()) {
        totalDevices = avgQuery.value(0).toInt();
    }
    stats["avg_devices"] = stats["total"] > 0 ? totalDevices / stats["total"] : 0;

    return stats;
}

QMap<QString, int> Statistics::getTechnicalStats()
{
    QMap<QString, int> stats;

    // Appareils fonctionnels
    QSqlQuery functionalQuery("SELECT COUNT(*) FROM APPAREILLES WHERE UPPER(ETAT) = 'FONCTIONNEL'");
    if(functionalQuery.exec() && functionalQuery.next()) {
        stats["functional"] = functionalQuery.value(0).toInt();
    } else {
        stats["functional"] = 0;
    }

    // Appareils en panne
    QSqlQuery brokenQuery("SELECT COUNT(*) FROM APPAREILLES WHERE UPPER(ETAT) != 'FONCTIONNEL'");
    if(brokenQuery.exec() && brokenQuery.next()) {
        stats["broken"] = brokenQuery.value(0).toInt();
    } else {
        stats["broken"] = 0;
    }

    return stats;
}

QMap<QString, double> Statistics::getFinancialStats()
{
    QMap<QString, double> stats;

    // Revenu total
    QSqlQuery revenueQuery("SELECT SUM(COUT) FROM REPARATIONS WHERE STATUT_R = 'TERMINE'");
    if(revenueQuery.exec() && revenueQuery.next()) {
        stats["total_revenue"] = revenueQuery.value(0).toDouble();
    } else {
        stats["total_revenue"] = 0.0;
    }

    // Revenu par appareil
    QSqlQuery deviceCountQuery("SELECT COUNT(*) FROM REPARATIONS WHERE STATUT_R = 'TERMINE'");
    int deviceCount = 0;
    if(deviceCountQuery.exec() && deviceCountQuery.next()) {
        deviceCount = deviceCountQuery.value(0).toInt();
    }
    stats["revenue_per_device"] = deviceCount > 0 ? stats["total_revenue"] / deviceCount : 0;

    return stats;
}

QMap<QString, int> Statistics::getTopClients()
{
    QMap<QString, int> topClients;

    QSqlQuery query("SELECT c.NOM, c.PRENOM, COUNT(a.NUM_SERIE) as device_count "
                    "FROM CLIENT c LEFT JOIN APPAREILLES a ON c.CIN_CLIENT = a.CIN_CLIENT "
                    "GROUP BY c.CIN_CLIENT, c.NOM, c.PRENOM "
                    "ORDER BY device_count DESC LIMIT 5");

    while(query.next()) {
        QString clientName = query.value(0).toString() + " " + query.value(1).toString();
        topClients[clientName] = query.value(2).toInt();
    }

    // Si pas de données, ajouter des valeurs par défaut
    if(topClients.isEmpty()) {
        topClients["Aucun client"] = 1;
    }

    return topClients;
}

QMap<QString, int> Statistics::getDeviceTypesStats()
{
    QMap<QString, int> types;

    QSqlQuery query("SELECT TYPE, COUNT(*) FROM APPAREILLES GROUP BY TYPE");
    while(query.next()) {
        types[query.value(0).toString()] = query.value(1).toInt();
    }

    // Si pas de données, ajouter des valeurs par défaut
    if(types.isEmpty()) {
        types["Smartphone"] = 5;
        types["Tablette"] = 3;
        types["Ordinateur"] = 2;
    }

    return types;
}

QMap<QString, int> Statistics::getBrandStats()
{
    QMap<QString, int> brands;

    QSqlQuery query("SELECT MARQUE, COUNT(*) FROM APPAREILLES GROUP BY MARQUE");
    while(query.next()) {
        brands[query.value(0).toString()] = query.value(1).toInt();
    }

    // Si pas de données, ajouter des valeurs par défaut
    if(brands.isEmpty()) {
        brands["Samsung"] = 4;
        brands["Apple"] = 3;
        brands["Huawei"] = 2;
        brands["Xiaomi"] = 1;
    }

    return brands;
}

QMap<QString, int> Statistics::getFrequentIssues()
{
    QMap<QString, int> issues;

    QSqlQuery query("SELECT DES_PANNE, COUNT(*) FROM REPARATIONS GROUP BY DES_PANNE ORDER BY COUNT(*) DESC LIMIT 5");
    while(query.next()) {
        issues[query.value(0).toString()] = query.value(1).toInt();
    }

    return issues;
}
