#include "Inventory.h"
#include "ui_signin.h"
#include "mainwindow.h"
Signin::Signin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signin)
{
    ui->setupUi(this);
}

Signin::~Signin()
{
    delete ui;
}


