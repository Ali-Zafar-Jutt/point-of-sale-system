#include"Username.h"
User::User()
{
    name = "";
    password = "";
    Privilege ="";
}
void User::set_user(QString s)
{
    name = s;
}
void User::set_password(QString p)
{
    password = p;
}
void User::set_privilege(QString p)
{
    Privilege = p;
}
User::User(QString n, QString p, QString pri)
{
    Privilege = pri;
    name = n;
    password = p;
}
QString User::get_user()
{
    return name;
}
QString User::get_password()
{
    return password;
}
QString User::get_Privilege()
{
    return Privilege;
}
const QString User::NORMAL_USER = "NORMALUSER";
const QString User:: ADMIN_USER = "ADMINUSER";
const QString User::STANDARD_USER = "STANDARDUSER";
