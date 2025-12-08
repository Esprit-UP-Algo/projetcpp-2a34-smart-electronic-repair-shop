#ifndef ARDUINODEVICE_H
#define ARDUINODEVICE_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class ArduinoDevice : public QObject
{
    Q_OBJECT
public:
    explicit ArduinoDevice(const QString &portName, QObject *parent = nullptr);
    ~ArduinoDevice();

    bool connect();
    void disconnect();
    bool isConnected() const;
    void sendCommand(const QString &cmd);

signals:
    void dataReceived(const QString &data);      // Tout message reçu
    void uidReceived(const QString &uid);        // RFID seulement
    void reparationRequested(const QString &id); // LCD seulement
    void connected(bool status);
    void errorOccurred(const QString &error);

private slots:
    void onReadyRead();

private:
    QSerialPort *serial;
    QString portName;
    QString buffer;
    void parseLine(const QString &line);
};

#endif
