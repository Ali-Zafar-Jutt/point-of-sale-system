#include "newuserprevilege.h"
#include "qdebug.h"
#include "qsqlquery.h"
#include "ui_newuserprevilege.h"
#include <QSqlDatabase>
#include <qmessagebox.h>

NewUserPrevilege::NewUserPrevilege(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewUserPrevilege)
{
    ui->setupUi(this);
}

NewUserPrevilege::~NewUserPrevilege()
{
    delete ui;
}

void NewUserPrevilege::on_pushButton_create_clicked()
{
    QString userPrivilege = "";
    QString Name = ui->lineEdit_newuser->text().trimmed();
    QString Password = ui->lineEdit_pass->text().trimmed();
    bool validUsername = !Name.isEmpty() && Name.length() >= 6;
    bool validPassword = !Password.isEmpty() && Password.length() >= 8;
    bool matchingPasswords = (Password == ui->lineEdit_3->text().trimmed());
    bool userFound = isDuplicateUser(Name);
    userPrivilege = privilegeCheck();
    if(!validUsername && !userFound && validPassword && matchingPasswords && userPrivilege!="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid green;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid green;");
        ui->radioButton_admin->setStyleSheet("");
        ui->radioButton_normal->setStyleSheet("");
        ui->radioButton_standard->setStyleSheet("");
        QMessageBox::critical(this,"Error","Please Enter a Valid Username (Min 6 Characters)");
        return;
    }
    if(validUsername && userFound && validPassword && matchingPasswords && userPrivilege!="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid green;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid green;");
        ui->radioButton_admin->setStyleSheet("");
        ui->radioButton_normal->setStyleSheet("");
        ui->radioButton_standard->setStyleSheet("");
        QMessageBox::critical(this,"Error","Username Already Exists. Enter A Different Username");
        return;
    }
    if(validUsername && !userFound && !validPassword && matchingPasswords && userPrivilege!="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid green;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid lightcoral;");
        ui->radioButton_admin->setStyleSheet("");
        ui->radioButton_normal->setStyleSheet("");
        ui->radioButton_standard->setStyleSheet("");
        QMessageBox::critical(this,"Error","Please Enter a Valid Password (Min 8 Characters)");
        return;
    }
    if(validUsername && !userFound && validPassword && !matchingPasswords && userPrivilege!="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid green;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid lightcoral;");
        ui->radioButton_admin->setStyleSheet("");
        ui->radioButton_normal->setStyleSheet("");
        ui->radioButton_standard->setStyleSheet("");
        QMessageBox::critical(this,"Error","Please Enter Valid Matching Passwords (Min 8 Characters)");
        return;
    }
    if(validUsername && !userFound && validPassword && matchingPasswords && userPrivilege=="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid green;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid green;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid green;");
        ui->radioButton_admin->setStyleSheet("color: lightcoral;");
        ui->radioButton_normal->setStyleSheet("color: lightcoral;");
        ui->radioButton_standard->setStyleSheet("color: lightcoral;");
        QMessageBox::critical(this,"Error","Please Select Privilge Type");
        return;
    }
    if(!validUsername && userFound && validPassword && matchingPasswords && userPrivilege!="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid green;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid green;");
        ui->radioButton_admin->setStyleSheet("");
        ui->radioButton_normal->setStyleSheet("");
        ui->radioButton_standard->setStyleSheet("");
        QMessageBox::critical(this,"Error","Enter A Different Valid Username (Min 6 Characters)");
        return;
    }
    if(!validUsername && !userFound && validPassword && matchingPasswords && userPrivilege!="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid green;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid green;");
        ui->radioButton_admin->setStyleSheet("");
        ui->radioButton_normal->setStyleSheet("");
        ui->radioButton_standard->setStyleSheet("");
        QMessageBox::critical(this,"Error","Enter A Valid Username (Min 6 Characters)");
        return;
    }
    if(!validUsername && !userFound && !validPassword && matchingPasswords && userPrivilege!="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid lightcoral;");
        ui->radioButton_admin->setStyleSheet("");
        ui->radioButton_normal->setStyleSheet("");
        ui->radioButton_standard->setStyleSheet("");
        QMessageBox::critical(this,"Error","Enter A Valid Username (Min 6 Characters) and Valid Password (Min 8 Characters)");
        return;
    }
    if(!validUsername && !userFound && validPassword && !matchingPasswords && userPrivilege!="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid lightcoral;");
        ui->radioButton_admin->setStyleSheet("");
        ui->radioButton_normal->setStyleSheet("");
        ui->radioButton_standard->setStyleSheet("");
        QMessageBox::critical(this,"Error","Enter A Valid Username (Min 6 Characters) and Matching Passwords");
        return;
    }
    if(!validUsername && !userFound && validPassword && matchingPasswords && userPrivilege=="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid green;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid green;");
        ui->radioButton_admin->setStyleSheet("color: lightcoral;");
        ui->radioButton_normal->setStyleSheet("color: lightcoral;");
        ui->radioButton_standard->setStyleSheet("color: lightcoral;");
        QMessageBox::critical(this,"Error","Enter A Valid Username (Min 6 Characters) and Select Privilege Type");
        return;
    }
    if(!validUsername && userFound && !validPassword && matchingPasswords && userPrivilege!="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid lightcoral;");
        ui->radioButton_admin->setStyleSheet("");
        ui->radioButton_normal->setStyleSheet("");
        ui->radioButton_standard->setStyleSheet("");
        QMessageBox::critical(this,"Error","Enter A Different Valid Username (Min 6 Characters) And Valid Password (Min 8 Characters)");
        return;
    }
    if(!validUsername && !userFound && validPassword && !matchingPasswords && userPrivilege!="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid lightcoral;");
        ui->radioButton_admin->setStyleSheet("");
        ui->radioButton_normal->setStyleSheet("");
        ui->radioButton_standard->setStyleSheet("");
        QMessageBox::critical(this,"Error","Enter A Valid Username (Min 6 Characters) And Matching Passwords");
        return;
    }
    if(!validUsername && userFound && validPassword && !matchingPasswords && userPrivilege!="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid lightcoral;");
        ui->radioButton_admin->setStyleSheet("");
        ui->radioButton_normal->setStyleSheet("");
        ui->radioButton_standard->setStyleSheet("");
        QMessageBox::critical(this,"Error","Enter A Different Valid Username (Min 6 Characters) And Matching Passwords");
        return;
    }
    if(!validUsername && !userFound && validPassword && matchingPasswords && userPrivilege=="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid green;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid green;");
        ui->radioButton_admin->setStyleSheet("color: lightcoral;");
        ui->radioButton_normal->setStyleSheet("color: lightcoral;");
        ui->radioButton_standard->setStyleSheet("color: lightcoral;");
        QMessageBox::critical(this,"Error","Enter A Valid Username (Min 6 Characters) And Select Privilege Type");
        return;
    }
    if(!validUsername && userFound && validPassword && matchingPasswords && userPrivilege=="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid green;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid green;");
        ui->radioButton_admin->setStyleSheet("color: lightcoral;");
        ui->radioButton_normal->setStyleSheet("color: lightcoral;");
        ui->radioButton_standard->setStyleSheet("color: lightcoral;");
        QMessageBox::critical(this,"Error","Enter A Different Valid Username (Min 6 Characters) And Select Privilege Type");
        return;
    }
    if(!validUsername && !userFound && !validPassword && !matchingPasswords && userPrivilege!="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid lightcoral;");
        ui->radioButton_admin->setStyleSheet("");
        ui->radioButton_normal->setStyleSheet("");
        ui->radioButton_standard->setStyleSheet("");
        QMessageBox::critical(this,"Error","Enter A Valid Username (Min 6 Characters) And Valid Matching Passwords (Min 8 Characters)");
        return;
    }
    if(!validUsername && userFound && !validPassword && !matchingPasswords && userPrivilege!="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid lightcoral;");
        ui->radioButton_admin->setStyleSheet("");
        ui->radioButton_normal->setStyleSheet("");
        ui->radioButton_standard->setStyleSheet("");
        QMessageBox::critical(this,"Error","Enter A Different Valid Username (Min 6 Characters) And Valid Matching Passwords (Min 8 Characters)");
        return;
    }
    if(!validUsername && userFound && !validPassword && matchingPasswords && userPrivilege=="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid lightcoral;");
        ui->radioButton_admin->setStyleSheet("color: lightcoral;");
        ui->radioButton_normal->setStyleSheet("color: lightcoral;");
        ui->radioButton_standard->setStyleSheet("color: lightcoral;");
        QMessageBox::critical(this,"Error","Enter A Different Valid Username (Min 6 Characters), Valid Password (Min 8 Characters) and Select Privilege Type");
        return;
    }
    if(!validUsername && userFound && !validPassword && !matchingPasswords && userPrivilege=="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid lightcoral;");
        ui->radioButton_admin->setStyleSheet("color: lightcoral;");
        ui->radioButton_normal->setStyleSheet("color: lightcoral;");
        ui->radioButton_standard->setStyleSheet("color: lightcoral;");
        QMessageBox::critical(this,"Error","Enter A Valid Username (Min 6 Characters), Valid Password (Min 8 Characters) and Select Privilege Type");
        return;
    }
    if(!validUsername && !userFound && !validPassword && !matchingPasswords && userPrivilege=="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid lightcoral;");
        ui->radioButton_admin->setStyleSheet("color: lightcoral;");
        ui->radioButton_normal->setStyleSheet("color: lightcoral;");
        ui->radioButton_standard->setStyleSheet("color: lightcoral;");
        QMessageBox::critical(this,"Error","Enter A Valid Username (Min 6 Characters), Valid Password (Min 8 Characters) and Select Privilege Type");
        return;
    }
    if(ui->lineEdit_3->text().isEmpty() && ui->lineEdit_newuser->text().isEmpty() && ui->lineEdit_pass->text().isEmpty() && privilegeCheck()=="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid lightcoral;");
        ui->radioButton_admin->setStyleSheet("color: lightcoral;");
        ui->radioButton_normal->setStyleSheet("color: lightcoral;");
        ui->radioButton_standard->setStyleSheet("color: lightcoral;");
        QMessageBox::critical(this,"Error","Enter A Valid Username (Min 6 Characters), Valid Password (Min 8 Characters) and Select Privilege Type");
        return;
    }
    if(validUsername && ui->lineEdit_3->text().isEmpty() && ui->lineEdit_pass->text().isEmpty() && privilegeCheck()=="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid green;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid lightcoral;");
        ui->radioButton_admin->setStyleSheet("color: lightcoral;");
        ui->radioButton_normal->setStyleSheet("color: lightcoral;");
        ui->radioButton_standard->setStyleSheet("color: lightcoral;");
        QMessageBox::critical(this,"Error","Enter Valid Matching Passwords (Min 8 Characters) and Select Privilege Type");
        return;
    }
    if(validUsername && ui->lineEdit_3->text().isEmpty() && ui->lineEdit_pass->text().isEmpty() && privilegeCheck()!="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid green;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid lightcoral;");
        ui->radioButton_admin->setStyleSheet("");
        ui->radioButton_normal->setStyleSheet("");
        ui->radioButton_standard->setStyleSheet("");
        QMessageBox::critical(this,"Error","Enter Valid Matching Passwords (Min 8 Characters)");
    }
    if(validUsername && !ui->lineEdit_pass->text().isEmpty() && ui->lineEdit_3->text().isEmpty() && privilegeCheck()=="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid green;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid lightcoral;");
        ui->radioButton_admin->setStyleSheet("color: lightcoral;");
        ui->radioButton_normal->setStyleSheet("color: lightcoral;");
        ui->radioButton_standard->setStyleSheet("color: lightcoral;");
        QMessageBox::critical(this,"Error","Enter Valid Matching Passwords (Min 8 Characters) And Select Privilege Type");
        return;
    }
    if(validUsername && !ui->lineEdit_pass->text().isEmpty() && ui->lineEdit_3->text().isEmpty() && privilegeCheck()!="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid green;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid lightcoral;");
        ui->radioButton_admin->setStyleSheet("");
        ui->radioButton_normal->setStyleSheet("");
        ui->radioButton_standard->setStyleSheet("");
        QMessageBox::critical(this,"Error","Enter Valid Matching Passwords (Min 8 Characters)");
        return;
    }
    if(validUsername && ui->lineEdit_pass->text().isEmpty() && !ui->lineEdit_3->text().isEmpty() && privilegeCheck()=="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid green;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid lightcoral;");
        ui->radioButton_admin->setStyleSheet("color: lightcoral;");
        ui->radioButton_normal->setStyleSheet("color: lightcoral;");
        ui->radioButton_standard->setStyleSheet("color: lightcoral;");
        QMessageBox::critical(this,"Error","Enter Valid Matching Passwords (Min 8 Characters) And Select Privilege Type");
        return;
    }
    if(validUsername && ui->lineEdit_pass->text().isEmpty() && !ui->lineEdit_3->text().isEmpty() && privilegeCheck()!="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid green;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid lightcoral;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid lightcoral;");
        ui->radioButton_admin->setStyleSheet("");
        ui->radioButton_normal->setStyleSheet("");
        ui->radioButton_standard->setStyleSheet("");
        QMessageBox::critical(this,"Error","Enter Valid Matching Passwords (Min 8 Characters)");
        return;
    }
    if(validUsername && !userFound && !validPassword && matchingPasswords && userPrivilege=="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid green;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid green;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid lightcoral;");
        ui->radioButton_admin->setStyleSheet("color: lightcoral;");
        ui->radioButton_normal->setStyleSheet("color: lightcoral;");
        ui->radioButton_standard->setStyleSheet("color: lightcoral;");
        QMessageBox::critical(this,"Error","Enter Valid Matching Passwords (Min 8 Characters) And Select Privilege Type");
        return;
    }
    if(validUsername && !userFound && validPassword && matchingPasswords && userPrivilege!="")
    {
        ui->lineEdit_newuser->setStyleSheet("border: 1px solid green;");
        ui->lineEdit_pass->setStyleSheet("border: 1px solid green;");
        ui->lineEdit_3->setStyleSheet("border: 1px solid green;");
        ui->radioButton_admin->setStyleSheet("");
        ui->radioButton_normal->setStyleSheet("");
        ui->radioButton_standard->setStyleSheet("");
        QSqlQuery insertQuery;
        insertQuery.prepare("insert into user_table (UserName, Password, Privilege) values (:Name,:Password,:userPrivilege)");
        insertQuery.bindValue(":Name",Name);
        insertQuery.bindValue(":Password",Password);
        insertQuery.bindValue(":userPrivilege",userPrivilege);
        if(insertQuery.exec())
        {
            qDebug() << "User Information Added:" << Qt::endl;
            ui->lineEdit_newuser->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit_pass->clear();
        }
    }
}
bool NewUserPrevilege::isDuplicateUser(const QString &name)
{
    QSqlQuery Q;
    Q.prepare("Select * from user_table where UserName = :name");
    Q.bindValue(":name",name);
    if(Q.exec() && Q.next())
    {
        if(name==Q.value(0).toString())
        {
            return true;
        }
        return false;
    }
    return false;
}
QString NewUserPrevilege::privilegeCheck()
{
    QString privilege="";
    if(ui->radioButton_admin->isChecked())
    {
        privilege = "ADMINUSER";
        return privilege;
    }
    else if(ui->radioButton_normal->isChecked())
    {
        privilege = "NORMALUSER";
        return privilege;
    }
    else if(ui->radioButton_standard->isChecked())
    {
        privilege = "STANDARDUSER";
        return privilege;
    }
    else
    {
        return "";
    }
}

































// void NewUserPrevilege::on_pushButton_create_clicked()
// {
//     QString userPrivilege = "";
//     QString Name = ui->lineEdit_newuser->text().trimmed();
//     QString Password = ui->lineEdit_pass->text().trimmed();
//     bool validUsername = !Name.isEmpty() && Name.length() >= 6;
//     bool validPassword = !Password.isEmpty() && Password.length() >= 8;
//     bool matchingPasswords = (Password == ui->lineEdit_3->text().trimmed());
//     bool userFound = isDuplicateUser(Name);
//     userPrivilege = privilegeCheck();
//     if(!validUsername)
//     {
//         ui->lineEdit_newuser->setStyleSheet("border: 1px solid lightcoral;");
//         QMessageBox::critical(this,"Error","Please Enter Valid Username (Min 6 Characters)");
//     }
//     else if(userFound)
//     {
//         ui->lineEdit_newuser->setStyleSheet("border: 1px solid lightcoral;");
//         QMessageBox::critical(this,"Error","Username Already Exists. Enter A Different Username");
//     }
//     else if(!validPassword)
//     {
//         ui->lineEdit_pass->setStyleSheet("border: 1px solid lightcoral;");
//         QMessageBox::critical(this,"Error","Please Enter Valid Password (Min 8 Characters");
//     }
//     else if(!matchingPasswords)
//     {
//         ui->lineEdit_pass->setStyleSheet("border: 1px solid lightcoral;");
//         ui->lineEdit_3->setStyleSheet("border: 1px solid lightcoral;");
//         QMessageBox::critical(this,"Error","Please Enter Matching Password");
//     }
//     else if(userPrivilege=="")
//     {
//         QMessageBox::critical(this,"Error","Please Select Privilge Type");
//         ui->radioButton_admin->setStyleSheet("color: lightcoral;");
//         ui->radioButton_normal->setStyleSheet("color: lightcoral;");
//         ui->radioButton_standard->setStyleSheet("color: lightcoral;");
//     }
//     else
//     {
//         ui->lineEdit_newuser->setStyleSheet("border: 1px solid green;");
//         ui->lineEdit_pass->setStyleSheet("border: 1px solid green;");
//         ui->lineEdit_3->setStyleSheet("border: 1px solid green;");
//         ui->radioButton_admin->setStyleSheet("");
//         ui->radioButton_normal->setStyleSheet("");
//         ui->radioButton_standard->setStyleSheet("");
//         QSqlQuery insertQuery;
//         insertQuery.prepare("insert into user_table (UserName, Password, Privilege) values (:Name,:Password,:userPrivilege)");
//         insertQuery.bindValue(":Name",Name);
//         insertQuery.bindValue(":Password",Password);
//         insertQuery.bindValue(":userPrivilege",userPrivilege);
//         if(insertQuery.exec())
//         {
//             qDebug() << "User Information Added:" << Qt::endl;
//             ui->lineEdit_newuser->clear();
//             ui->lineEdit_3->clear();
//             ui->lineEdit_pass->clear();
//         }
//     }
// }

