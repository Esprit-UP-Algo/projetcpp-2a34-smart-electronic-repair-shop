#ifndef PDFEXPORTER_H
#define PDFEXPORTER_H

#include <QObject>
#include <QTextDocument>
#include <QPrinter>
#include <QSqlQuery>
#include <QMap>
#include <QDateTime>

class PDFExporter : public QObject
{
    Q_OBJECT

public:
    explicit PDFExporter(QObject *parent = nullptr);
    bool exportClientReport(const QString &filename);

private:
    QString generateClientListHTML();
    QString generateStatisticsHTML();
    QString generateRecommendations();
    QMap<QString, int> getClientStats();
    QMap<QString, int> getTechnicalStats();
    QMap<QString, double> getFinancialStats();
};

#endif // PDFEXPORTER_H
