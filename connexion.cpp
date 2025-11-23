
#include "connexion.h"

Connection::Connection()
{

}
bool Connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("projet_qt");
    db.setUserName("boubaker");
    db.setPassword("esprit2026");
    if(db.open()) test=true;
    return test;
}
void Connection::closeConnection(){db.close();}
