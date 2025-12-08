#include "arduinodevice.h"
#include <QDebug>

ArduinoDevice::ArduinoDevice(const QString &portName, QObject *parent)
    : QObject(parent), serial(new QSerialPort(this)), portName(portName)
{
    // CORRECTION QT6 : syntaxe moderne obligatoire
    QObject::connect(serial, &QSerialPort::readyRead, this, &ArduinoDevice::onReadyRead);
}

ArduinoDevice::~ArduinoDevice() {
    disconnect();
}

bool ArduinoDevice::connect() {
    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite)) {
        emit connected(true);
        qDebug() << "Connecté à" << portName;
        return true;
    } else {
        emit errorOccurred("Impossible d'ouvrir " + portName + ": " + serial->errorString());
        return false;
    }
}

void ArduinoDevice::disconnect() {
    if (serial->isOpen()) serial->close();
    emit connected(false);
}

bool ArduinoDevice::isConnected() const {
    return serial->isOpen();
}

void ArduinoDevice::sendCommand(const QString &cmd) {
    if (serial->isOpen()) {
        QString final = cmd;
        if (!final.endsWith("\n")) final += "\n";
        serial->write(final.toUtf8());
    }
}

void ArduinoDevice::onReadyRead() {
    buffer += serial->readAll();
    int idx;
    while ((idx = buffer.indexOf('\n')) != -1) {
        QString line = buffer.left(idx).trimmed();
        buffer.remove(0, idx + 1);
        if (!line.isEmpty()) {
            qDebug() << portName << "← Reçu:" << line;
            parseLine(line);
            emit dataReceived(line);
        }
    }
}

void ArduinoDevice::parseLine(const QString &line) {
    if (line.startsWith("<U") && line.endsWith(">")) {
        QString uid = line.mid(2, line.length() - 3);
        emit uidReceived(uid);
    }
    else if (line.startsWith("<R") && line.endsWith(">")) {
        QString id = line.mid(2, line.length() - 3);
        emit reparationRequested(id);
    }
    // Tu peux ajouter d'autres formats ici
}
