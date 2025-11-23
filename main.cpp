#include "mainwindow.h"
#include "connexion.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test = c.createconnection();
    MainWindow w;

    if(test)
    {
        w.show();
        QMessageBox::information(nullptr, "Connexion", "Connexion à la base de données réussie!");
    }
    else
    {
        QMessageBox::critical(nullptr, "Connexion", "Échec de connexion à la base de données!");
    }

    return a.exec();
}
