#include "connection.h"

Connection* Connection::instance = nullptr;

Connection::Connection() {}

Connection* Connection::getInstance()
{
    if (instance == nullptr) {
        instance = new Connection();
    }
    return instance;
}

bool Connection::createConnect()
{
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("sourceprojet2A");
    db.setUserName("sirine");
    db.setPassword("sirine123");

    if (db.open()) {
        test = true;
    }
    return test;
}

Connection::~Connection()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        db.close();
    }
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}
