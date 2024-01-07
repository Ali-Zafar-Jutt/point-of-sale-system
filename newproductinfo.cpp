#include "newproductinfo.h"
#include "qmessagebox.h"
#include "qregularexpression.h"
#include "ui_newproductinfo.h"
#include <Product.h>
#include<QLineEdit>
#include<QDebug>
#include"Utils.cpp"
Newproductinfo::Newproductinfo(QWidget *parent,QString code) :
    QDialog(parent),
    ui(new Ui::Newproductinfo)
  {
    ui->setupUi(this);
    barCode = code;
  }
Newproductinfo::~Newproductinfo()
{
    delete ui;
}
void Newproductinfo::on_pushButton_newproduct_clicked()
{
    qDebug()<<"New Product Info Dialog Box"<<Qt::endl;
    qDebug()<<"Barcode = "<<barCode<<Qt::endl;
    Product P;
    int check=0;
    QLineEdit * p = findChild<QLineEdit*>("lineEdit_product");
    QString product = p->text();
    QLineEdit * r = findChild<QLineEdit*>("lineEdit_retail");
    QLineEdit * s = findChild<QLineEdit*>("lineEdit_sale");
    QLineEdit * q = findChild<QLineEdit*>("lineEdit_quantity");
    QLineEdit * type = findChild<QLineEdit*>("lineEdit_productType");
    QLineEdit * dscpt = findChild<QLineEdit*>("lineEdit_productDescription");
    QSqlQuery query;
    query.prepare("Select * from Inventory_Table where Product_Name = :product");
    query.bindValue(":product",product);
    if(query.exec() && query.next())
    {
        QString checkProduct = query.value(1).toString();
        qDebug()<<checkProduct<<Qt::endl;
        if(checkProduct==product)
        {
            qDebug()<<"Duplicate Product Name Entered."<<Qt::endl;
            QMessageBox::critical(this,"Error","Duplicate Product Name Is Entered");
        }
        else
        {
            QString rp = r->text();
            QString sp = s->text();
            QString tq = q->text();
            QString Typ = type->text();
            QString descrp = dscpt->text();
            static QRegularExpression regex("^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?$");
            float retail=0;
            float sale=0;
            int salecheck=0;
            int retailcheck=0;
            if(!product.isEmpty())
            {
                P.set_PoductName(product);
                qDebug()<<"Product Name Is Entered "<<Qt::endl;
            }
            else
            {
                qDebug()<<"Product Name Is Not Enterd "<<Qt::endl;
                check++;
                qDebug()<<"Product Name Check Incremented "<<"(Check = "<<check<<")"<<Qt::endl;
            }
            if (!sp.isEmpty() && !regex.match(sp).hasMatch())
            {
                qDebug() << "Invalid Sale Price Format" << Qt::endl;
                salecheck++;
            }
            else if (!sp.isEmpty())
            {
                qDebug()<<"The Sale Price Entered is Correct "<<Qt::endl;
                sale = sp.toFloat();
            }
            else
            {
                qDebug()<<"Sale Price Is Not Enterd "<<Qt::endl;
                check++;
                qDebug()<<"Sale Price Name Check Incremented "<<"(Check = "<<check<<")"<<Qt::endl;
            }
            if(!rp.isEmpty() && !regex.match(rp).hasMatch())
            {
                qDebug() << "Invalid Retail Price Format" << Qt::endl;
                retailcheck++;
            }
            else if(!rp.isEmpty())
            {
                qDebug()<<"Retail Price Is Enterd Correctly"<<Qt::endl;
                retail = rp.toFloat();
            }
            else
            {
                qDebug()<<"Retail Price Is Not Enterd "<<Qt::endl;
                check++;
                qDebug()<<"Retail Price Check Incremented "<<"(Check = "<<check<<")"<<Qt::endl;
            }
            if(!tq.isEmpty())
            {
                qDebug()<<"Total Quantity Is Enterd "<<Qt::endl;
                int total = tq.toInt();
                P.set_TotalQuantity(total);
            }
            else
            {
                qDebug()<<"Total Quantity Is Not Enterd "<<Qt::endl;
                check++;
                qDebug()<<"Product Name Check Incremented "<<"(Check = "<<check<<")"<<Qt::endl;
            }
            if(!Typ.isEmpty())
            {
                P.set_productType(Typ);
                qDebug()<<"Product Type Is Entered "<<Qt::endl;
            }
            else
            {
                qDebug()<<"Product Type Not Entered "<<Qt::endl;
            }
            if(!descrp.isEmpty())
            {
                P.set_productDescription(descrp);
                qDebug()<<"Product Description Is Entered "<<Qt::endl;
            }
            else
            {
                qDebug()<<"Product Description Is Not Entered "<<Qt::endl;
            }
            if(sale<retail)
            {
                QMessageBox::warning(this,"Warning!","The Sale Price Cannot Be Less than The Retail Price.");
            }
            else if(salecheck!=0)
            {
                QMessageBox::critical(this,"Error","Sale Price Entered Is Invalid");
            }
            else if(retailcheck!=0)
            {
                QMessageBox::critical(this,"Error","Retail Price Entered Is Invalid");
            }
            else
            {
                ;
            }
            if (check>0 || salecheck>0 || retailcheck>0)
            {

                qDebug() << "Some Required Information Is Missing or Invalid " << Qt::endl;
                QMessageBox::critical(this, "ERROR", "Please Fill All The Boxes With Valid Product Information");
            }
            else
            {
                qDebug()<<"All The Required Information of Product Is Entered "<<Qt::endl;
                P.set_SalesPrice(sale);
                P.set_RetailPrice(retail);
                P.set_productID(barCode);
                QSqlQuery query;
                query.prepare("INSERT INTO Inventory_Table (Barcode,Product_Name,"
                              "Product_Sale_Price, Product_Retail_Price, Product_Quantities,Product_Type,Product_Description)"
                              "VALUES (:Barcode, :Product_Name,:Product_Sale_Price,:Product_Retail_Price,:Product_Quantities,:Product_Type,:Product_Description)");
                query.bindValue(":Barcode",P.get_ProductID());
                query.bindValue(":Product_Name",P.get_ProductName());
                query.bindValue(":Product_Sale_Price",P.get_SalePrice());
                query.bindValue(":Product_Retail_Price",P.get_retailPrice());
                query.bindValue(":Product_Quantities",P.get_total_Quantity());
                if(!P.get_ProductType().isEmpty())
                {
                    query.bindValue(":Product_Type",P.get_ProductType());
                }
                else
                {
                    query.bindValue(":Product_Type","");
                }
                if(!P.get_ProductDescription().isEmpty())
                {
                    query.bindValue(":Product_Description",P.get_ProductDescription());
                }
                else
                {
                    query.bindValue(":Product_Description","");
                }
                if(query.exec())
                {
                    qDebug() << "Data inserted successfully!";
                    accept();
                }
                else
                {
                    qDebug() << "Data insertion Failed!";
                    QMessageBox::critical(this, "ERROR", "Failed to insert data into the database."+query.lastError().text());
                }
            }
        }
    }
    else
    {
        qDebug()<<"Query Execution Failed"<<Qt::endl;
        QMessageBox::critical(this,"Query Error",query.lastError().text());
    }
}

