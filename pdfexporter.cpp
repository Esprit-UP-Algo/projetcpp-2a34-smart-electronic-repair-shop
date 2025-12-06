#include "pdfexporter.h"

#include <QTextDocument>
#include <QTextCursor>        // Obligatoire !
#include <QPrinter>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QDebug>>

PDFExporter::PDFExporter(QObject *parent) : QObject(parent) {}

bool PDFExporter::exportClientReport(const QString &filename)
{
    QTextDocument document;
    QTextCursor cursor(&document);

    // En-tête stylé
    cursor.insertHtml(R"(
        <div style='text-align:center; background:#2c3147; color:white; padding:20px;'>
            <h1>Smart Repair Hub - Rapport Complet</h1>
            <p>Généré le : )" + QDateTime::currentDateTime().toString("dd/MM/yyyy à hh:mm") + R"(</p>
        </div><br>
    )");

    // === Statistiques Globales ===
    cursor.insertHtml("<h2 style='color:#2c3147;'>Statistiques Globales</h2>");

    auto clientStats = getClientStats();
    auto techStats = getTechnicalStats();
    auto financeStats = getFinancialStats();

    cursor.insertHtml(QString(R"(
        <table border='1' cellspacing='0' cellpadding='10' width='100%'>
            <tr style='background:#007BFF; color:white;'>
                <th>Indicateur</th><th>Valeur</th>
            </tr>
            <tr><td>Total Clients</td><td><strong>%1</strong></td></tr>
            <tr><td>Nouveaux ce mois</td><td><strong>%2</strong></td></tr>
            <tr><td>Appareils fonctionnels</td><td><strong>%3</strong></td></tr>
            <tr><td>Appareils en panne</td><td><strong>%4</strong></td></tr>
            <tr><td>Revenu total (DT)</td><td><strong>%5</strong></td></tr>
        </table><br>
    )")
                          .arg(clientStats["total"])
                          .arg(clientStats["new_this_month"])
                          .arg(techStats["functional"])
                          .arg(techStats["broken"])
                          .arg(financeStats["total_revenue"], 0, 'f', 2));

    // === Liste des clients ===
    cursor.insertHtml(generateClientListHTML());

    // === Recommandations ===
    cursor.insertHtml(generateRecommendations());

    // Pied de page
    cursor.insertHtml(R"(
        <div style='text-align:center; margin-top:40px; color:#6c757d; font-size:10pt;'>
            <p>Smart Repair Hub © 2025 - Tous droits réservés</p>
        </div>
    )");

    // Export PDF
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filename);
    printer.setPageMargins(QMarginsF(20, 20, 20, 20), QPageLayout::Millimeter);

    document.print(&printer);
    return true;
}

// Toutes les requêtes sont locales → plus jamais de "Function sequence error"
QMap<QString, int> PDFExporter::getClientStats()
{
    QMap<QString, int> stats;
    {
        QSqlQuery q;
        q.exec("SELECT COUNT(*) FROM CLIENT");
        if (q.next()) stats["total"] = q.value(0).toInt();
    }
    {
        QSqlQuery q;
        QDate d = QDate::currentDate();
        QString sql = QString("SELECT COUNT(*) FROM CLIENT WHERE "
                              "EXTRACT(MONTH FROM DATEN) = %1 AND EXTRACT(YEAR FROM DATEN) = %2")
                          .arg(d.month()).arg(d.year());
        q.exec(sql);
        if (q.next()) stats["new_this_month"] = q.value(0).toInt();
    }
    return stats;
}

QMap<QString, int> PDFExporter::getTechnicalStats()
{
    QMap<QString, int> stats;
    {
        QSqlQuery q;
        q.exec("SELECT COUNT(*) FROM APPAREILLES WHERE UPPER(ETAT) = 'FONCTIONNEL'");
        if (q.next()) stats["functional"] = q.value(0).toInt();
    }
    {
        QSqlQuery q;
        q.exec("SELECT COUNT(*) FROM APPAREILLES WHERE UPPER(ETAT) != 'FONCTIONNEL'");
        if (q.next()) stats["broken"] = q.value(0).toInt();
    }
    return stats;
}

QMap<QString, double> PDFExporter::getFinancialStats()
{
    QMap<QString, double> stats;
    {
        QSqlQuery q;
        q.exec("SELECT SUM(COUT) FROM REPARATIONS WHERE STATUT_R = 'TERMINE'");
        if (q.next()) stats["total_revenue"] = q.value(0).toDouble();
    }
    return stats;
}

QString PDFExporter::generateClientListHTML()
{
    QString html = "<h2 style='color:#2c3147;'>Liste des Clients</h2>";
    html += "<table border='1' cellspacing='0' cellpadding='8' width='100%'>"
            "<tr style='background:#007BFF; color:white;'>"
            "<th>CIN</th><th>Nom</th><th>Prénom</th><th>Téléphone</th><th>Email</th><th>Appareils</th>"
            "</tr>";

    QSqlQuery q;
    if (!q.exec("SELECT CIN_CLIENT, NOM, PRENOM, TELEPHONE, EMAIL FROM CLIENT ORDER BY NOM")) {
        html += "<tr><td colspan='6'>Erreur base de données</td></tr>";
        return html;
    }

    while (q.next()) {
        int cin = q.value(0).toInt();
        QString nom = q.value(1).toString();
        QString prenom = q.value(2).toString();
        QString tel = q.value(3).toString();
        QString email = q.value(4).toString();

        // Compteur appareils
        QSqlQuery countQuery;
        countQuery.prepare("SELECT COUNT(*) FROM APPAREILLES WHERE CIN_CLIENT = ?");
        countQuery.addBindValue(cin);
        int count = 0;
        if (countQuery.exec() && countQuery.next()) {
            count = countQuery.value(0).toInt();
        }

        html += QString("<tr>"
                        "<td>%1</td><td>%2</td><td>%3</td><td>%4</td><td>%5</td><td><strong>%6</strong></td>"
                        "</tr>")
                    .arg(cin).arg(nom).arg(prenom)
                    .arg(tel.isEmpty() ? "-" : tel)
                    .arg(email.isEmpty() ? "-" : email)
                    .arg(count);
    }

    html += "</table>";
    return html;
}

QString PDFExporter::generateRecommendations()
{
    return R"(
        <h2 style='color:#28a745;'>Recommandations</h2>
        <ul>
            <li>Envoyer des rappels de maintenance aux clients fidèles</li>
            <li>Augmenter le stock de pièces pour Samsung et Apple</li>
            <li>Former l'équipe aux nouvelles technologies 5G et écrans OLED</li>
            <li>Lancer un programme de fidélité (remise après 3 réparations)</li>
        </ul>
    )";
}
