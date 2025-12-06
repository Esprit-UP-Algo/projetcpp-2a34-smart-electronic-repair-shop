#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
{
private:
    static Connection* instance;
    Connection(); // Constructeur privé
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

public:
    static Connection* getInstance();
    bool createConnect();
    ~Connection();
};

#endif // CONNECTION_H
