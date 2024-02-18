#include "signin.h"
#include "ui_signin.h"
#include <MainMenu.h>
#include <MainWindow.h>
#include <MainMenu.h>
#include <qmessagebox.h>
#include <qsqlquery.h>
signin::signin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::signin)
{
    ui->setupUi(this);
}

signin::~signin()
{
    delete ui;
    setWindowTitle("Sign In");
    connect(ui->lineEdit_Password, &QLineEdit::returnPressed, this, &signin::on_pushButton_clicked);
    connect(ui->lineEdit_Username, &QLineEdit::returnPressed, this, &signin::on_pushButton_clicked);
    qDebug()<<"Return Pressed Function Called: "<<Qt::endl;
}
void signin::on_pushButton_clicked()
{
    QString Name = ui->lineEdit_Username->text();
    QString Password = ui->lineEdit_Password->text();
    QSqlQuery Q;
    Q.prepare("Select * from user_table where Password = :Password And UserName = :Name");
    Q.bindValue(":Name",Name);
    Q.bindValue(":Password",Password);
    if(Q.exec() && Q.next())
    {
        qDebug()<<"User/Password Found: "<<Qt::endl;
        QString Privilege = Q.value(2).toString();
        qDebug()<<"User Privilege Type: "<<Privilege<<Qt::endl;
        close();
        MainWindow * m = new MainWindow(this, Privilege);
        m->setWindowTitle("Menu");
        m->show();
    }
    else
    {
        QMessageBox::critical(this,"ERROR","Invalid UserName Or Password");
    }
}



// #include "mainwindow.h"
// #include "qdebug.h"
// #include "qsqlquery.h"
// #include "ui_mainwindow.h"
// #include"mainmenu.h"
// #include <Product.h>
// #include<ProductArraylist.h>
// #include<QMessageBox>
// MainWindow::MainWindow(QWidget *parent)
//     : QMainWindow(parent)
//     , ui(new Ui::MainWindow)
// {
//     ui->setupUi(this);
//     mainmenu = nullptr;
//     setWindowTitle("Sign In");
//     connect(ui->lineEdit_Password, &QLineEdit::returnPressed, this, &MainWindow::on_pushButton_clicked);
//     connect(ui->lineEdit_Username, &QLineEdit::returnPressed, this, &MainWindow::on_pushButton_clicked);
//     qDebug()<<"Return Pressed Function Called: "<<Qt::endl;
// }

// MainWindow::~MainWindow()
// {
//     delete ui;
// }


// void MainWindow::on_pushButton_clicked()
// {
//     QString Name = ui->lineEdit_Username->text();
//     QString Password = ui->lineEdit_Password->text();
//     QSqlQuery Q;
//     Q.prepare("Select * from user_table where Password = :Password And UserName = :Name");
//     Q.bindValue(":Name",Name);
//     Q.bindValue(":Password",Password);
//     if(Q.exec() && Q.next())
//     {
//         qDebug()<<"User/Password Found: "<<Qt::endl;
//         QString Privilege = Q.value(2).toString();
//         qDebug()<<"User Privilege Type: "<<Privilege<<Qt::endl;
//         mainmenu = new MainMenu(this,Privilege);
//         mainmenu->setWindowTitle("Main Menu");
//         close();
//         mainmenu->exec();
//     }
//     else
//     {
//         QMessageBox::critical(this,"ERROR","Invalid UserName Or Password");
//     }
// }

