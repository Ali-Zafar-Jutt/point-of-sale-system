#include <QApplication>
#include <signin.h>
#include <mainwindow.h>
#include "signin.h"
#include "Utils.cpp"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<QSqlDatabase::drivers();
    Utils::connection();
    signin *s = new signin(nullptr);
    s->setWindowTitle("Sign-In");
    s->show();
    return a.exec();
}
