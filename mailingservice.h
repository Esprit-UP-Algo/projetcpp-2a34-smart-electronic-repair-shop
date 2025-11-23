#ifndef MAILINGSERVICE_H
#define MAILINGSERVICE_H

#include <QObject>
#include <QString>

class MailingService : public QObject
{
    Q_OBJECT

public:
    explicit MailingService(QObject *parent = nullptr);

    void setTwilioCredentials(const QString& accountSid, const QString& authToken, const QString& fromEmail);
    bool sendWelcomeEmail(const QString& toEmail, const QString& employeeName, int cin);
    bool sendPresenceNotification(const QString& toEmail, const QString& employeeName, const QString& presenceStatus);
    bool sendCustomEmail(const QString& toEmail, const QString& subject, const QString& body);
    bool sendPdfByEmail(const QString& toEmail, const QString& subject, const QString& body, const QString& pdfFilePath);

signals:
    void emailSent(bool success, const QString& message);

private:
    QString m_accountSid;
    QString m_authToken;
    QString m_fromEmail;
};

#endif // MAILINGSERVICE_H
