#include "newuserprevilege.h"
#include "qdebug.h"
#include "qsqlerror.h"
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
    int duplicateUserName=0;
    int privilegeFlag=0;
    QString Name = ui->lineEdit_newuser->text().trimmed();
    QString Password = ui->lineEdit_pass->text().trimmed();
    bool validUsername = !Name.isEmpty() && Name.length() >= 6;
    bool validPassword = !Password.isEmpty() && Password.length() >= 8;
    bool matchingPasswords = (Password == ui->lineEdit_3->text().trimmed());
    QSqlQuery q;
    q.prepare("Select * from user_table where Username = :Name");
    q.bindValue(":Name",Name);
    if(q.exec() && q.next())
    {
        if(Name==q.value(0).toString())
        {
            duplicateUserName=0;
        }
        else
        {
            duplicateUserName++;
        }
    }
    if(ui->radioButton_admin->isChecked())
    {
        userPrivilege=ui->radioButton_admin->text();
        privilegeFlag++;
    }
    else if(ui->radioButton_normal->isChecked())
    {
        userPrivilege=ui->radioButton_normal->text();
        privilegeFlag++;
    }
    else if(ui->radioButton_standard->isChecked())
    {
        userPrivilege=ui->radioButton_standard->text();
        privilegeFlag++;
    }
    if(validUsername && validPassword && matchingPasswords && privilegeFlag!=0 && duplicateUserName!=0)
    {
        qDebug()<<"privilegeFlag: "<<privilegeFlag<<Qt::endl;
        QSqlQuery q;
        q.prepare("Insert Into user_table(UserName,Password,Privilege) VALUES (:Name,:Password,:userPrivilege) ");
        q.bindValue(":Name",Name);
        q.bindValue(":Password",Password);
        q.bindValue(":userPrivilege",userPrivilege);
        if(q.exec())
        {
            qDebug() << "User Information Added:" << Qt::endl;
            ui->lineEdit_newuser->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit_pass->clear();
        }
        else
        {
            QMessageBox::critical(this,"Error",q.lastError().text());
        }
    }
    else if(duplicateUserName==0 && !validUsername && !validPassword && !matchingPasswords && privilegeFlag==0)
    {
        qDebug()<<"privilegeFlag: "<<privilegeFlag<<Qt::endl;
        QMessageBox::critical(this,"Error","Enter Valid Username (Min 6 Characters), Valid Matching Passwords (Min 8 Characters) and Select Privilege Type");
    }
    else if(duplicateUserName==0 && validUsername && !validPassword && !matchingPasswords && privilegeFlag==0)
    {
        qDebug()<<"privilegeFlag: "<<privilegeFlag<<Qt::endl;
        QMessageBox::critical(this,"Error","Enter Valid Matching Passwords (Min 8 Characters) and Select Privilege Type");
    }
    else if(duplicateUserName==0 && validUsername && !validPassword && matchingPasswords && privilegeFlag==0)
    {
        qDebug()<<"privilegeFlag: "<<privilegeFlag<<Qt::endl;
        QMessageBox::critical(this,"Error","Enter Valid Password (Min 8 Characters) and Select Privilege Type");
    }
    else if(duplicateUserName==0 && validUsername && validPassword && !matchingPasswords && privilegeFlag==0)
    {
        qDebug()<<"privilegeFlag: "<<privilegeFlag<<Qt::endl;
        QMessageBox::critical(this,"Error","Enter Matching Passwords (Min 8 Characters) and Select Privilege Type");
    }
    else if(duplicateUserName==0 && validUsername && validPassword && !matchingPasswords && privilegeFlag!=0)
    {
        qDebug()<<"privilegeFlag: "<<privilegeFlag<<Qt::endl;
        QMessageBox::critical(this,"Error","Enter Matching Passwords (Min 8 Characters)");
    }
    else if(duplicateUserName==0 && validUsername && validPassword && matchingPasswords && privilegeFlag==0)
    {
        qDebug()<<"privilegeFlag: "<<privilegeFlag<<Qt::endl;
        QMessageBox::critical(this,"Error","Please Select Privilege Type");
    }
    else if(duplicateUserName==0 && !validUsername && validPassword && matchingPasswords && privilegeFlag!=0)
    {
        qDebug()<<"privilegeFlag: "<<privilegeFlag<<Qt::endl;
        QMessageBox::critical(this,"Error","Please Enter Valid Username (Min 6 Characters)");
    }
    else if(duplicateUserName==0 && validUsername && !validPassword && matchingPasswords && privilegeFlag!=0)
    {
        qDebug()<<"privilegeFlag: "<<privilegeFlag<<Qt::endl;
        QMessageBox::critical(this,"Error","Please Enter Valid Password (Min 8 Characters)");
    }
    else if(duplicateUserName==0 && validUsername && validPassword && !matchingPasswords && privilegeFlag!=0)
    {
        qDebug()<<"privilegeFlag: "<<privilegeFlag<<Qt::endl;
        QMessageBox::critical(this,"Error","Please Enter Valid Matching Password (Min 8 Characters)");
    }
    else if(duplicateUserName!=0 && validUsername && validPassword && matchingPasswords && privilegeFlag!=0)
    {
        qDebug()<<"privilegeFlag: "<<privilegeFlag<<Qt::endl;
        QMessageBox::critical(this,"Error","Username Already Exists. Please Enter a Different Username (Min 6 Characters)");
    }
    else if(duplicateUserName!=0 && validUsername && !validPassword && matchingPasswords && privilegeFlag!=0)
    {
        qDebug()<<"privilegeFlag: "<<privilegeFlag<<Qt::endl;
        QMessageBox::critical(this,"Error","Username Already Exists and Invalid Password. Please Enter a Different Username (Min 6 Characters) and Enter Valid Password (Min 8 Characters)");
    }
    else if(duplicateUserName!=0 && validUsername && validPassword && !matchingPasswords && privilegeFlag!=0)
    {
        qDebug()<<"privilegeFlag: "<<privilegeFlag<<Qt::endl;
        QMessageBox::critical(this,"Error","Username Already Exists and Not Matching Password. Please Enter a Different Username (Min 6 Characters) and Valid Matching Password (Min 8 Characters)");
    }
    else if(duplicateUserName!=0 && validUsername && !validPassword && !matchingPasswords && privilegeFlag!=0)
    {
        qDebug()<<"privilegeFlag: "<<privilegeFlag<<Qt::endl;
        QMessageBox::critical(this,"Error","Username Already Exists and Invalid Password. Please Enter a Different Username (Min 6 Characters) and Valid Matching Password (Min 8 Characters)");
    }
    else if(duplicateUserName!=0 && validUsername && validPassword && matchingPasswords && privilegeFlag==0)
    {
        qDebug()<<"privilegeFlag: "<<privilegeFlag<<Qt::endl;
        QMessageBox::critical(this,"Error","Username Already Exists and Privilege Not Selected. Please Enter a Different Username and Select Privilege Type");
    }
}


