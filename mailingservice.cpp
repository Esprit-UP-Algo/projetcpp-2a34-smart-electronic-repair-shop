#include "mailingservice.h"
#include <QDebug>
#include <QTimer>
#include <QFileInfo>

MailingService::MailingService(QObject *parent)
    : QObject(parent)
{
}

void MailingService::setTwilioCredentials(const QString& accountSid, const QString& authToken, const QString& fromEmail)
{
    m_accountSid = accountSid;
    m_authToken = authToken;
    m_fromEmail = fromEmail;
    qDebug() << "Credentials Twilio configurés - Account SID:" << accountSid.left(10) + "...";
}

bool MailingService::sendWelcomeEmail(const QString& toEmail, const QString& employeeName, int cin)
{
    qDebug() << "=== SIMULATION ENVOI EMAIL BIENVENUE ===";
    qDebug() << "À:" << toEmail;
    qDebug() << "Nom:" << employeeName;
    qDebug() << "CIN:" << cin;
    qDebug() << "De:" << m_fromEmail;

    QTimer::singleShot(2000, this, [this, employeeName]() {
        qDebug() << "✅ Email de bienvenue envoyé avec succès (simulation)";
        emit emailSent(true, "Email de bienvenue envoyé à " + employeeName + " (simulation)");
    });

    return true;
}

bool MailingService::sendPresenceNotification(const QString& toEmail, const QString& employeeName, const QString& presenceStatus)
{
    qDebug() << "=== SIMULATION NOTIFICATION PRÉSENCE ===";
    qDebug() << "À:" << toEmail;
    qDebug() << "Nom:" << employeeName;
    qDebug() << "Statut:" << presenceStatus;
    qDebug() << "De:" << m_fromEmail;

    QTimer::singleShot(2000, this, [this, employeeName, presenceStatus]() {
        qDebug() << "✅ Notification de présence envoyée avec succès (simulation)";
        emit emailSent(true, "Notification de présence (" + presenceStatus + ") envoyée à " + employeeName + " (simulation)");
    });

    return true;
}

bool MailingService::sendCustomEmail(const QString& toEmail, const QString& subject, const QString& body)
{
    qDebug() << "=== SIMULATION ENVOI EMAIL PERSONNALISÉ ===";
    qDebug() << "À:" << toEmail;
    qDebug() << "Sujet:" << subject;
    qDebug() << "Message:" << body;
    qDebug() << "De:" << m_fromEmail;
    qDebug() << "Account SID:" << (m_accountSid.isEmpty() ? "Non configuré" : m_accountSid.left(10) + "...");
    qDebug() << "Auth Token:" << (m_authToken.isEmpty() ? "Non configuré" : "Configuré");

    QTimer::singleShot(2000, this, [this, toEmail, subject]() {
        qDebug() << "✅ Email personnalisé envoyé avec succès (simulation)";
        emit emailSent(true, "Email '" + subject + "' envoyé à " + toEmail + " (simulation)");
    });

    return true;
}

bool MailingService::sendPdfByEmail(const QString& toEmail, const QString& subject, const QString& body, const QString& pdfFilePath)
{
    qDebug() << "=== SIMULATION ENVOI PDF PAR EMAIL ===";
    qDebug() << "À:" << toEmail;
    qDebug() << "Sujet:" << subject;
    qDebug() << "Message:" << body;
    qDebug() << "Fichier PDF:" << pdfFilePath;
    qDebug() << "De:" << m_fromEmail;

    // Vérifier si le fichier PDF existe
    QFileInfo fileInfo(pdfFilePath);
    if (!fileInfo.exists()) {
        qDebug() << "❌ Fichier PDF non trouvé:" << pdfFilePath;
        emit emailSent(false, "Fichier PDF non trouvé: " + pdfFilePath);
        return false;
    }

    qDebug() << "✅ Fichier PDF trouvé - Taille:" << fileInfo.size() << "bytes";

    QTimer::singleShot(2000, this, [this, toEmail, subject, pdfFilePath]() {
        qDebug() << "✅ PDF envoyé par email avec succès (simulation)";
        qDebug() << "📎 Fichier joint:" << pdfFilePath;
        emit emailSent(true, "PDF '" + subject + "' envoyé à " + toEmail + " avec pièce jointe (simulation)");
    });

    return true;
}
