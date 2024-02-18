#ifndef USERNAME_H
#define USERNAME_H
#include<QString>
#include<QList>

class User
{

    QString name;
    QString password;
    QString Privilege;

public:
    const static QString NORMAL_USER;
    const static QString ADMIN_USER;
    const static QString STANDARD_USER;
    User();
    User(QString n, QString p, QString pri);
    void set_user(QString);
    void set_password(QString);
    void set_privilege(QString);
    QString get_user();
    QString get_Privilege();
    QString get_password();
};

#endif // USERNAME_H
