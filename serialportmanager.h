#ifndef SERIALPORTMANAGER_H
#define SERIALPORTMANAGER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

class SerialPortManager : public QObject
{
    Q_OBJECT

public:
    explicit SerialPortManager(QObject *parent = nullptr);
    ~SerialPortManager();

    bool connectToArduino();
    void disconnectArduino();
    bool isConnected() const;
    void sendCommand(const QString &command);
    QString getCurrentUID() const { return currentUID; }

signals:
    void cardDetected(const QString &uid);
    void doorOpened();
    void doorClosed();
    void connected(bool status);
    void error(const QString &errorMessage);
    //arduino sirine//
    void reparationRequested(const QString &idRep);  // Nouveau

private slots:
    void readData();

private:
    QSerialPort *serial;
    QString currentUID;
    QString buffer;
    void parseData(const QString &data);
};

#endif // SERIALPORTMANAGER_H
