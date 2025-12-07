#include "SerialPortManager.h"
#include <QDebug>

SerialPortManager::SerialPortManager(QObject *parent)
    : QObject(parent)
    , serial(new QSerialPort(this))
    , currentUID("")
{
    connect(serial, &QSerialPort::readyRead, this, &SerialPortManager::readData);
}

SerialPortManager::~SerialPortManager()
{
    disconnectArduino();
}

bool SerialPortManager::connectToArduino()
{
    // Chercher un port Arduino
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Port:" << info.portName()
        << "Description:" << info.description();

        if (info.description().contains("Arduino") ||
            info.portName().startsWith("COM") ||
            info.portName().startsWith("/dev/ttyUSB") ||
            info.portName().startsWith("/dev/ttyACM")) {

            serial->setPortName(info.portName());
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);

            if (serial->open(QIODevice::ReadWrite)) {
                emit connected(true);
                return true;
            }
        }
    }

    emit error("Aucun Arduino détecté");
    return false;
}

void SerialPortManager::disconnectArduino()
{
    if (serial->isOpen()) {
        serial->close();
        emit connected(false);
    }
}

bool SerialPortManager::isConnected() const
{
    return serial->isOpen();
}

void SerialPortManager::sendCommand(const QString &command)
{
    if (serial->isOpen()) {
        QString cmd = command;
        if (!cmd.endsWith("\n")) cmd += "\n";
        serial->write(cmd.toUtf8());
        qDebug() << "Commande envoyée:" << cmd.trimmed();
    }
}

void SerialPortManager::readData()
{
    while (serial->canReadLine()) {
        QString line = serial->readLine().trimmed();
        qDebug() << "Reçu d'Arduino:" << line;
        parseData(line);
    }
}

void SerialPortManager::parseData(const QString &data)
{
    if (data.startsWith("<U") && data.endsWith(">")) {
        // Format: <UABCD1234>
        currentUID = data.mid(2, data.length() - 3);
        emit cardDetected(currentUID);
    }
    else if (data == "<O1>") {
        emit doorOpened();
    }
    else if (data == "<C1>") {
        emit doorClosed();
    }
    // === NOUVEAU : Demande d'info réparation depuis LCD ===
    else if (data.startsWith("<R") && data.endsWith(">")) {
        QString idRep = data.mid(2, data.length() - 3);
        emit reparationRequested(idRep);
    }
    else if (data.startsWith("<S>") && data.endsWith("</S>")) {
        // Message système
        QString message = data.mid(3, data.length() - 7);
        qDebug() << "Message système:" << message;
    }
}
