#include "AddNewItem.h"
#include "ui_inventory_menu.h"
#include<qmainwindow.h>
#include"Product.h"
#include<QLineEdit>
#include"ProductArraylist.h"
Inventory_Menu::Inventory_Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Inventory_Menu)
{
    ui->setupUi(this);
}

Inventory_Menu::~Inventory_Menu()
{
    delete ui;
}

void Inventory_Menu::on_lineEdit_ScanNewItem_returnPressed()
{
    QLineEdit * ID = findChild<QLineEdit*>("lineEdit_ScanNewItem");
    QLineEdit * productname = findChild<QLineEdit*>("textEdit_ProductName");
    QLineEdit * retailprice = findChild<QLineEdit*>("textEdit_RetailPrice");
    QLineEdit * saleprice = findChild<QLineEdit*>("textEdit_SalePrice");
    QLineEdit * totalquantity = findChild<QLineEdit*>("textEdit_TotalQuantity");
    QString pro = productname->text();
    QString id = ID->text();
    QString rp = retailprice->text();
    float RP = rp.toFloat();
    QString sp = saleprice->text();
    float SP = sp.toFloat();
    QString tq = totalquantity->text();
    int TQ = tq.toInt();
    Product p(pro,id,SP,RP,TQ);
    products.append(p);
    close();
}

