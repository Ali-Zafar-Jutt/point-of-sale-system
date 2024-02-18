#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Inventory_Dialog.h>
#include <NewUserPrevilege.h>
#include <Product.h>
#include<ProductArraylist.h>
#include<QMessageBox>
#include <Qlayout>
#include <Sale.h>
#include <SalesHistory.h>
#include <signin.h>
QDialog * currentOpenWindow = NULL;
MainWindow::MainWindow(QWidget *parent, QString s)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    u(s)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::openLayout(QDialog* ql)
{
    QLayout * layout = ui->Container;
    if(currentOpenWindow)
    {
        layout->removeWidget(currentOpenWindow);
        delete currentOpenWindow;
    }
    currentOpenWindow=ql;
    layout->addWidget(ql);
}
void MainWindow::on_pushButton_AddUser_clicked()
{
    if(u=="ADMINUSER")
    {
        NewUserPrevilege * newuser = new NewUserPrevilege(this);
        Sale::row=0;
        Sale::newRow=0;
        openLayout(newuser);
    }
    else if(u=="STANDARDUSER")
    {
        NewUserPrevilege * newuser = new NewUserPrevilege(this);
        Sale::row=0;
        Sale::newRow=0;
        openLayout(newuser);
    }
    else
    {
        QMessageBox::critical(this,"Unauthorized User","Permission Not Granted");
    }
}


void MainWindow::on_pushButton_ViewHistory_clicked()
{
    if(u=="ADMINUSER")
    {
        SalesHistory * history = new SalesHistory(this);
        Sale::row=0;
        Sale::newRow=0;
        openLayout(history);
    }
    else if(u=="STANDARDUSER")
    {
        SalesHistory * history = new SalesHistory(this);
        Sale::row=0;
        Sale::newRow=0;
        openLayout(history);
    }
    else
    {
        QMessageBox::critical(this,"Unauthorized User","Permission Not Granted");
    }
}


void MainWindow::on_pushButton_AddSale_clicked()
{
    Sale::row=0;
    Sale::newRow=0;
    Sale * sale = new Sale (this,u);
    openLayout(sale);
}
void MainWindow::on_pushButton_Inventory_clicked()
{
    if(u=="ADMINUSER")
    {
        Inventory_Dialog * dialog = new Inventory_Dialog(this);
        Sale::row=0;
        Sale::newRow=0;
        openLayout(dialog);
    }
    else if(u=="STANDARDUSER")
    {
        Inventory_Dialog * dialog = new Inventory_Dialog(this);
        Sale::row=0;
        Sale::newRow=0;
        openLayout(dialog);
    }
    else
    {
        QMessageBox::warning(this,"Unauthorized User","Permission Not Granted");
    }
}
void MainWindow::on_SignOut_Button_clicked()
{
    signin * SignIn = new signin(nullptr);
    SignIn->setWindowTitle("Sign-In");
    close();
    SignIn->exec();
}

