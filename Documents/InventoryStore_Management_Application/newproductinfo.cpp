#include "newproductinfo.h"
#include "qmessagebox.h"
#include "ui_newproductinfo.h"
#include <Product.h>
#include<QLineEdit>
#include<QDebug>
#include <QStatusBar>
#include"Utils.cpp"
#include<QTimer>
Newproductinfo::Newproductinfo(QWidget *parent,QString code) :
    QDialog(parent),
    ui(new Ui::Newproductinfo)
  {
    ui->setupUi(this);
    barCode = code;
    statusLabel = new QLabel(this);
    statusLabel->setStyleSheet("color: red");
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setGeometry(10, height() - 30, width() - 20, 20);
    statusLabel->setVisible(false);
  }
Newproductinfo::~Newproductinfo()
{
    delete ui;
}
void Newproductinfo::on_pushButton_newproduct_clicked()
{
    qDebug()<<"New Product Info Dialog Box"<<Qt::endl;
    qDebug()<<"Barcode = "<<barCode<<Qt::endl;
    qDebug()<<ValidateFields()<<Qt::endl<<ErrorFieldHighlight()<<Qt::endl;
    if(ValidateFields() && ErrorFieldHighlight() && strictNumFieldsHighlight() && checkRetailSalePrice() && isQuantityValid())
    {
        QString ProductName = ui->lineEdit_product->text();
        int RetailPrice = ui->lineEdit_retail->text().toInt();
        int SalesPrice = ui->lineEdit_sale->text().toInt();
        int Quantity = ui->lineEdit_quantity->text().toInt();
        QString ProductType = ui->lineEdit_productType->text();
        QString ProductDescription = ui->lineEdit_productDescription->text();
        Product P;
        QSqlQuery Q;
        Q.prepare("insert into Inventory_Table (Barcode,Product_Name,Product_Quantity,Product_Salesprice,Product_Retailprice,Product_Type,Product_Description)"
                  "Values(:barCode,:ProductName,:Quantity,:SalesPrice,:RetailPrice,:ProductType,:ProductDescription)");
        Q.bindValue(":barCode", barCode);
        Q.bindValue(":ProductName", ProductName);
        Q.bindValue(":RetailPrice", RetailPrice);
        Q.bindValue(":SalesPrice", SalesPrice);
        Q.bindValue(":Quantity", Quantity);
        Q.bindValue(":ProductType", ProductType);
        Q.bindValue(":ProductDescription", ProductDescription);
        if(Q.exec())
        {
            qDebug()<<"Query Executed Successfully: "<<Qt::endl;
            close();
        }
        else
        {
            QMessageBox::critical(this,"Query Error",Q.lastError().text());
        }
    }
    if(!ValidateFields())
    {
        statusLabel->setText("All Fields Are Required");
        statusLabel->setVisible(true);
        QTimer::singleShot(5000, this, [this]()
        {
            statusLabel->setVisible(false);
        });
    }
    if(checkRetailSalePrice() && ValidateFields() && strictNumFieldsHighlight() && !isQuantityValid())
    {
        ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral");
        statusLabel->setText("Enter Valid Quantity");
        statusLabel->setVisible(true);
        QTimer::singleShot(3500, this, [this]()
        {
            statusLabel->setVisible(false);
        });
    }
    if(!checkRetailSalePrice() && ValidateFields() && strictNumFieldsHighlight())
    {
        statusLabel->setText("Sale Price Cannot Be Less Than Retail Price");
        statusLabel->setVisible(true);
        QTimer::singleShot(3500, this, [this]()
        {
            statusLabel->setVisible(false);
        });
    }
    if(ValidateFields() && !strictNumFieldsHighlight())
    {
        if(!isAllDigits(ui->lineEdit_retail->text()))
        {
            ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral");
        }
        else
        {
            ui->lineEdit_retail->setStyleSheet("border: 1px solid green");
        }
        if(!isAllDigits(ui->lineEdit_sale->text()))
        {
            ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral");
        }
        else
        {
            ui->lineEdit_sale->setStyleSheet("border: 1px solid green");
        }
        if(!isAllDigits(ui->lineEdit_quantity->text()))
        {
            ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral");
        }
        else
        {
            ui->lineEdit_quantity->setStyleSheet("border: 1px solid green");
        }
        statusLabel->setText("Invalid Information For This Field");
        statusLabel->setVisible(true);
        QTimer::singleShot(3500, this, [this]()
        {
            statusLabel->setVisible(false);
        });
    }
}
bool Newproductinfo::isQuantityValid()
{
    if(ui->lineEdit_quantity->text().toInt()<=0)
    {
        return false;
    }
    return true;
}
bool Newproductinfo::checkRetailSalePrice()
{
    if(ui->lineEdit_sale->text().toInt()<ui->lineEdit_retail->text().toInt())
    {
        ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral");
        ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral");
        return false;
    }
    return true;
}
bool Newproductinfo::strictNumFieldsHighlight()
{
    if(!isAllDigits(ui->lineEdit_retail->text()) || !isAllDigits(ui->lineEdit_quantity->text()) || !isAllDigits(ui->lineEdit_sale->text()))
    {
        return false;
    }
    return true;

}
bool Newproductinfo::ErrorFieldHighlight()
{
    int * ErrorFields = ErrorFieldNum();
    if(ErrorFields[0]==1)
    {
        ui->lineEdit_product->setStyleSheet("border: 1px solid lightcoral");
    }
    else
    {
        ui->lineEdit_product->setStyleSheet("border: 1px solid green");
    }
    if(ErrorFields[1]==2)
    {
        ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral");
    }
    else
    {
        ui->lineEdit_retail->setStyleSheet("border: 1px solid green");
    }
    if(ErrorFields[2]==3)
    {
        ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral");
    }
    else
    {
        ui->lineEdit_sale->setStyleSheet("border: 1px solid green");
    }
    if(ErrorFields[3]==4)
    {
        ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral");
    }
    else
    {
        ui->lineEdit_quantity->setStyleSheet("border: 1px solid green");
    }
    if(ErrorFields[4]==5)
    {
        ui->lineEdit_productType->setStyleSheet("border: 1px solid lightcoral");
    }
    else
    {
        ui->lineEdit_productType->setStyleSheet("border: 1px solid green");
    }
    if(ErrorFields[5]==6)
    {
        ui->lineEdit_productDescription->setStyleSheet("border: 1px solid lightcoral");
    }
    else
    {
        ui->lineEdit_productDescription->setStyleSheet("border: 1px solid green");
    }
    int check=0;
    if(ErrorFields[0]==1 || ErrorFields[1]==2 || ErrorFields[2]==3 || ErrorFields[3]==4 || ErrorFields[4]==5 || ErrorFields[5]==6)
    {
        check++;
    }
    delete [] ErrorFields;
    if(check==0)
    {
        return true;
    }
    return false;
}
bool Newproductinfo::ValidateFields()
{
    if(ui->lineEdit_product->text().isEmpty() || ui->lineEdit_productDescription->text().isEmpty() || ui->lineEdit_productType->text().isEmpty()
        || ui->lineEdit_quantity->text().isEmpty() || ui->lineEdit_retail->text().isEmpty() || ui->lineEdit_sale->text().isEmpty())
    {
        return false;
    }
    else
    {
        return true;
    }
}
int * Newproductinfo::ErrorFieldNum()
{
    int * array = new int[6];
    if(ui->lineEdit_product->text().isEmpty())
    {
        array[0]=1;
    }
    else
    {
        array[0]=0;
    }
    if(ui->lineEdit_retail->text().isEmpty())
    {
        array[1]=2;
    }
    else if(!ui->lineEdit_retail->text().isEmpty() && !isAllDigits(ui->lineEdit_retail->text()))
    {
        NotNumFields[0]=1;
    }
    else
    {
        array[1]=0;
    }
    if(ui->lineEdit_sale->text().isEmpty())
    {
        array[2]=3;
    }
    else if((!ui->lineEdit_sale->text().isEmpty() && !isAllDigits(ui->lineEdit_sale->text())))
    {
        NotNumFields[1]=2;
    }
    else
    {
        array[2]=0;
    }
    if(ui->lineEdit_quantity->text().isEmpty())
    {
        array[3]=4;
    }
    else if((!ui->lineEdit_quantity->text().isEmpty() && !isAllDigits(ui->lineEdit_quantity->text())))
    {
        NotNumFields[2]=3;
    }
    else
    {
        array[3]=0;
    }
    if(ui->lineEdit_productType->text().isEmpty())
    {
        array[4]=5;
    }
    else
    {
        array[4]=0;
    }
    if(ui->lineEdit_productDescription->text().isEmpty())
    {
        array[5]=6;
    }
    else
    {
        array[5]=0;
    }
    return array;
}
bool Newproductinfo::isAllDigits(const QString &text)
{
    return std::all_of(text.begin(), text.end(), [](QChar c) {
        return c.isDigit();
    });
}

















// if(ui->lineEdit_product->text().isEmpty() && ui->lineEdit_sale->text().isEmpty() && ui->lineEdit_retail->text().isEmpty()
//     && ui->lineEdit_quantity->text().isEmpty() && ui->lineEdit_productType->text().isEmpty() && ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid lightcoral;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && ui->lineEdit_sale->text().isEmpty() && ui->lineEdit_retail->text().isEmpty()
//     && ui->lineEdit_quantity->text().isEmpty() && ui->lineEdit_productType->text().isEmpty() && ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid lightcoral;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(ui->lineEdit_product->text().isEmpty() && !ui->lineEdit_sale->text().isEmpty() && ui->lineEdit_retail->text().isEmpty()
//     && ui->lineEdit_quantity->text().isEmpty() && ui->lineEdit_productType->text().isEmpty() && ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid lightcoral;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(ui->lineEdit_product->text().isEmpty() && ui->lineEdit_sale->text().isEmpty() && !ui->lineEdit_retail->text().isEmpty()
//     && ui->lineEdit_quantity->text().isEmpty() && ui->lineEdit_productType->text().isEmpty() && ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid lightcoral;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(ui->lineEdit_product->text().isEmpty() && ui->lineEdit_sale->text().isEmpty() && ui->lineEdit_retail->text().isEmpty()
//     && !ui->lineEdit_quantity->text().isEmpty() && ui->lineEdit_productType->text().isEmpty() && ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid lightcoral;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(ui->lineEdit_product->text().isEmpty() && ui->lineEdit_sale->text().isEmpty() && ui->lineEdit_retail->text().isEmpty()
//     && ui->lineEdit_quantity->text().isEmpty() && !ui->lineEdit_productType->text().isEmpty() && ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid lightcoral;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(ui->lineEdit_product->text().isEmpty() && ui->lineEdit_sale->text().isEmpty() && ui->lineEdit_retail->text().isEmpty()
//     && ui->lineEdit_quantity->text().isEmpty() && ui->lineEdit_productType->text().isEmpty() && !ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid green;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && !ui->lineEdit_sale->text().isEmpty() && ui->lineEdit_retail->text().isEmpty()
//     && ui->lineEdit_quantity->text().isEmpty() && ui->lineEdit_productType->text().isEmpty() && ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid lightcoral;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && ui->lineEdit_sale->text().isEmpty() && !ui->lineEdit_retail->text().isEmpty()
//     && ui->lineEdit_quantity->text().isEmpty() && ui->lineEdit_productType->text().isEmpty() && ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid lightcoral;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && ui->lineEdit_sale->text().isEmpty() && ui->lineEdit_retail->text().isEmpty()
//     && !ui->lineEdit_quantity->text().isEmpty() && ui->lineEdit_productType->text().isEmpty() && ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid lightcoral;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && ui->lineEdit_sale->text().isEmpty() && ui->lineEdit_retail->text().isEmpty()
//     && ui->lineEdit_quantity->text().isEmpty() && !ui->lineEdit_productType->text().isEmpty() && ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid lightcoral;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && ui->lineEdit_sale->text().isEmpty() && ui->lineEdit_retail->text().isEmpty()
//     && ui->lineEdit_quantity->text().isEmpty() && ui->lineEdit_productType->text().isEmpty() && !ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid green;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && !ui->lineEdit_sale->text().isEmpty() && !ui->lineEdit_retail->text().isEmpty()
//     && ui->lineEdit_quantity->text().isEmpty() && ui->lineEdit_productType->text().isEmpty() && ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid lightcoral;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && !ui->lineEdit_sale->text().isEmpty() && ui->lineEdit_retail->text().isEmpty()
//     && !ui->lineEdit_quantity->text().isEmpty() && ui->lineEdit_productType->text().isEmpty() && ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid lightcoral;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && !ui->lineEdit_sale->text().isEmpty() && ui->lineEdit_retail->text().isEmpty()
//     && ui->lineEdit_quantity->text().isEmpty() && !ui->lineEdit_productType->text().isEmpty() && ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid lightcoral;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && !ui->lineEdit_sale->text().isEmpty() && ui->lineEdit_retail->text().isEmpty()
//     && ui->lineEdit_quantity->text().isEmpty() && ui->lineEdit_productType->text().isEmpty() && !ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid green;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && !ui->lineEdit_sale->text().isEmpty() && !ui->lineEdit_retail->text().isEmpty()
//     && !ui->lineEdit_quantity->text().isEmpty() && ui->lineEdit_productType->text().isEmpty() && ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid lightcoral;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && !ui->lineEdit_sale->text().isEmpty() && !ui->lineEdit_retail->text().isEmpty()
//     && ui->lineEdit_quantity->text().isEmpty() && !ui->lineEdit_productType->text().isEmpty() && ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid lightcoral;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && !ui->lineEdit_sale->text().isEmpty() && !ui->lineEdit_retail->text().isEmpty()
//     && ui->lineEdit_quantity->text().isEmpty() && ui->lineEdit_productType->text().isEmpty() && !ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid green;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && !ui->lineEdit_sale->text().isEmpty() && !ui->lineEdit_retail->text().isEmpty()
//     && !ui->lineEdit_quantity->text().isEmpty() && !ui->lineEdit_productType->text().isEmpty() && ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid lightcoral;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && !ui->lineEdit_sale->text().isEmpty() && !ui->lineEdit_retail->text().isEmpty()
//     && !ui->lineEdit_quantity->text().isEmpty() && ui->lineEdit_productType->text().isEmpty() && !ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid green;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && ui->lineEdit_sale->text().isEmpty() && !ui->lineEdit_retail->text().isEmpty()
//     && !ui->lineEdit_quantity->text().isEmpty() && ui->lineEdit_productType->text().isEmpty() && ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid lightcoral;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && ui->lineEdit_sale->text().isEmpty() && !ui->lineEdit_retail->text().isEmpty()
//     && ui->lineEdit_quantity->text().isEmpty() && !ui->lineEdit_productType->text().isEmpty() && ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid lightcoral;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && ui->lineEdit_sale->text().isEmpty() && !ui->lineEdit_retail->text().isEmpty()
//     && ui->lineEdit_quantity->text().isEmpty() && ui->lineEdit_productType->text().isEmpty() && !ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid green;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && ui->lineEdit_sale->text().isEmpty() && ui->lineEdit_retail->text().isEmpty()
//     && !ui->lineEdit_quantity->text().isEmpty() && !ui->lineEdit_productType->text().isEmpty() && ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid lightcoral;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && ui->lineEdit_sale->text().isEmpty() && ui->lineEdit_retail->text().isEmpty()
//     && !ui->lineEdit_quantity->text().isEmpty() && ui->lineEdit_productType->text().isEmpty() && !ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid lightcoral;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && ui->lineEdit_sale->text().isEmpty() && ui->lineEdit_retail->text().isEmpty()
//     && ui->lineEdit_quantity->text().isEmpty() && !ui->lineEdit_productType->text().isEmpty() && !ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid green;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && ui->lineEdit_sale->text().isEmpty() && ui->lineEdit_retail->text().isEmpty()
//     && !ui->lineEdit_quantity->text().isEmpty() && !ui->lineEdit_productType->text().isEmpty() && !ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid green;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && ui->lineEdit_sale->text().isEmpty() && !ui->lineEdit_retail->text().isEmpty()
//     && ui->lineEdit_quantity->text().isEmpty() && !ui->lineEdit_productType->text().isEmpty() && !ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid green;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && !ui->lineEdit_sale->text().isEmpty() && ui->lineEdit_retail->text().isEmpty()
//     && ui->lineEdit_quantity->text().isEmpty() && !ui->lineEdit_productType->text().isEmpty() && !ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid green;");
//     statusLabel->setText("All Fields Are Required");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && !ui->lineEdit_sale->text().isEmpty() && !ui->lineEdit_retail->text().isEmpty()
//     && !ui->lineEdit_quantity->text().isEmpty() && !isAllDigits(ui->lineEdit_retail->text()) && isAllDigits(ui->lineEdit_quantity->text())
//     && isAllDigits(ui->lineEdit_sale->text()) && !ui->lineEdit_productType->text().isEmpty() && !ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid green;");
//     statusLabel->setText("Invalid Retail Price");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && !ui->lineEdit_sale->text().isEmpty() && !ui->lineEdit_retail->text().isEmpty()
//     && !ui->lineEdit_quantity->text().isEmpty() && isAllDigits(ui->lineEdit_retail->text()) && !isAllDigits(ui->lineEdit_quantity->text())
//     && isAllDigits(ui->lineEdit_sale->text()) && !ui->lineEdit_productType->text().isEmpty() && !ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid green;");
//     statusLabel->setText("Invalid Product Quantity");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && !ui->lineEdit_sale->text().isEmpty() && !ui->lineEdit_retail->text().isEmpty()
//     && !ui->lineEdit_quantity->text().isEmpty() && isAllDigits(ui->lineEdit_retail->text()) && isAllDigits(ui->lineEdit_quantity->text())
//     && !isAllDigits(ui->lineEdit_sale->text()) && !ui->lineEdit_productType->text().isEmpty() && !ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid green;");
//     statusLabel->setText("Invalid Sale Price");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && !ui->lineEdit_sale->text().isEmpty() && !ui->lineEdit_retail->text().isEmpty()
//     && !ui->lineEdit_quantity->text().isEmpty() && !isAllDigits(ui->lineEdit_retail->text()) && !isAllDigits(ui->lineEdit_quantity->text())
//     && !isAllDigits(ui->lineEdit_sale->text()) && !ui->lineEdit_productType->text().isEmpty() && !ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid green;");
//     statusLabel->setText("Enter Valid Product Retail/Sale Price and Quantity");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && !ui->lineEdit_sale->text().isEmpty() && !ui->lineEdit_retail->text().isEmpty()
//     && !ui->lineEdit_quantity->text().isEmpty() && !isAllDigits(ui->lineEdit_retail->text()) && !isAllDigits(ui->lineEdit_quantity->text())
//     && isAllDigits(ui->lineEdit_sale->text()) && !ui->lineEdit_productType->text().isEmpty() && !ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid green;");
//     statusLabel->setText("Enter Valid Product Retail Price and Quantity");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && !ui->lineEdit_sale->text().isEmpty() && !ui->lineEdit_retail->text().isEmpty()
//     && !ui->lineEdit_quantity->text().isEmpty() && !isAllDigits(ui->lineEdit_retail->text()) && isAllDigits(ui->lineEdit_quantity->text())
//     && !isAllDigits(ui->lineEdit_sale->text()) && !ui->lineEdit_productType->text().isEmpty() && !ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid green;");
//     statusLabel->setText("Enter Valid Product Retail and Sale Price");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }
// if(!ui->lineEdit_product->text().isEmpty() && !ui->lineEdit_sale->text().isEmpty() && !ui->lineEdit_retail->text().isEmpty()
//     && !ui->lineEdit_quantity->text().isEmpty() && isAllDigits(ui->lineEdit_retail->text()) && !isAllDigits(ui->lineEdit_quantity->text())
//     && !isAllDigits(ui->lineEdit_sale->text()) && !ui->lineEdit_productType->text().isEmpty() && !ui->lineEdit_productDescription->text().isEmpty())
// {
//     ui->lineEdit_product->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_sale->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_retail->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_quantity->setStyleSheet("border: 1px solid lightcoral;");
//     ui->lineEdit_productType->setStyleSheet("border: 1px solid green;");
//     ui->lineEdit_productDescription->setStyleSheet("border: 1px solid green;");
//     statusLabel->setText("Enter Valid Product Sale Price and Quantity");
//     statusLabel->setVisible(true);
//     QTimer::singleShot(2000, this, [this]()
//     {
//         statusLabel->setVisible(false);
//     });
// }










// void Newproductinfo::on_pushButton_newproduct_clicked()
// {
//     qDebug()<<"New Product Info Dialog Box"<<Qt::endl;
//     qDebug()<<"Barcode = "<<barCode<<Qt::endl;
//     Product P;
//     int check=0;
//     QLineEdit * p = findChild<QLineEdit*>("lineEdit_product");
//     QString product = p->text();
//     QLineEdit * r = findChild<QLineEdit*>("lineEdit_retail");
//     QLineEdit * s = findChild<QLineEdit*>("lineEdit_sale");
//     QLineEdit * q = findChild<QLineEdit*>("lineEdit_quantity");
//     QLineEdit * type = findChild<QLineEdit*>("lineEdit_productType");
//     QLineEdit * dscpt = findChild<QLineEdit*>("lineEdit_productDescription");
//     QSqlQuery query;
//     query.prepare("Select * from Inventory_Table where Product_Name = :product");
//     query.bindValue(":product",product);
//     if(query.exec() && query.next())
//     {
//         QString checkProduct = query.value(1).toString();
//         qDebug()<<checkProduct<<Qt::endl;
//         if(checkProduct==product)
//         {
//             qDebug()<<"Duplicate Product Name Entered."<<Qt::endl;
//             QMessageBox::critical(this,"Error","Duplicate Product Name Is Entered");
//         }
//         else
//         {
//             QString rp = r->text();
//             QString sp = s->text();
//             QString tq = q->text();
//             QString Typ = type->text();
//             QString descrp = dscpt->text();
//             static QRegularExpression regex("^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?$");
//             float retail=0;
//             float sale=0;
//             int salecheck=0;
//             int retailcheck=0;
//             if(!product.isEmpty())
//             {
//                 P.set_PoductName(product);
//                 qDebug()<<"Product Name Is Entered "<<Qt::endl;
//             }
//             else
//             {
//                 qDebug()<<"Product Name Is Not Enterd "<<Qt::endl;
//                 check++;
//                 qDebug()<<"Product Name Check Incremented "<<"(Check = "<<check<<")"<<Qt::endl;
//             }
//             if (!sp.isEmpty() && !regex.match(sp).hasMatch())
//             {
//                 qDebug() << "Invalid Sale Price Format" << Qt::endl;
//                 salecheck++;
//             }
//             else if (!sp.isEmpty())
//             {
//                 qDebug()<<"The Sale Price Entered is Correct "<<Qt::endl;
//                 sale = sp.toFloat();
//             }
//             else
//             {
//                 qDebug()<<"Sale Price Is Not Enterd "<<Qt::endl;
//                 check++;
//                 qDebug()<<"Sale Price Name Check Incremented "<<"(Check = "<<check<<")"<<Qt::endl;
//             }
//             if(!rp.isEmpty() && !regex.match(rp).hasMatch())
//             {
//                 qDebug() << "Invalid Retail Price Format" << Qt::endl;
//                 retailcheck++;
//             }
//             else if(!rp.isEmpty())
//             {
//                 qDebug()<<"Retail Price Is Enterd Correctly"<<Qt::endl;
//                 retail = rp.toFloat();
//             }
//             else
//             {
//                 qDebug()<<"Retail Price Is Not Enterd "<<Qt::endl;
//                 check++;
//                 qDebug()<<"Retail Price Check Incremented "<<"(Check = "<<check<<")"<<Qt::endl;
//             }
//             if(!tq.isEmpty())
//             {
//                 qDebug()<<"Total Quantity Is Enterd "<<Qt::endl;
//                 int total = tq.toInt();
//                 P.set_TotalQuantity(total);
//             }
//             else
//             {
//                 qDebug()<<"Total Quantity Is Not Enterd "<<Qt::endl;
//                 check++;
//                 qDebug()<<"Product Name Check Incremented "<<"(Check = "<<check<<")"<<Qt::endl;
//             }
//             if(!Typ.isEmpty())
//             {
//                 P.set_productType(Typ);
//                 qDebug()<<"Product Type Is Entered "<<Qt::endl;
//             }
//             else
//             {
//                 qDebug()<<"Product Type Not Entered "<<Qt::endl;
//             }
//             if(!descrp.isEmpty())
//             {
//                 P.set_productDescription(descrp);
//                 qDebug()<<"Product Description Is Entered "<<Qt::endl;
//             }
//             else
//             {
//                 qDebug()<<"Product Description Is Not Entered "<<Qt::endl;
//             }
//             if(sale<retail)
//             {
//                 QMessageBox::warning(this,"Warning!","The Sale Price Cannot Be Less than The Retail Price.");
//             }
//             else if(salecheck!=0)
//             {
//                 QMessageBox::critical(this,"Error","Sale Price Entered Is Invalid");
//             }
//             else if(retailcheck!=0)
//             {
//                 QMessageBox::critical(this,"Error","Retail Price Entered Is Invalid");
//             }
//             else
//             {
//                 ;
//             }
//             if (check>0 || salecheck>0 || retailcheck>0)
//             {

//                 qDebug() << "Some Required Information Is Missing or Invalid " << Qt::endl;
//                 QMessageBox::critical(this, "ERROR", "Please Fill All The Boxes With Valid Product Information");
//             }
//             else
//             {
//                 qDebug()<<"All The Required Information of Product Is Entered "<<Qt::endl;
//                 P.set_SalesPrice(sale);
//                 P.set_RetailPrice(retail);
//                 P.set_productID(barCode);
//                 QSqlQuery query;
//                 query.prepare("INSERT INTO Inventory_Table (Barcode,Product_Name,"
//                               "Retail_Price, Sale_Price,Total_Quantity,Product_Type,Product_Description)"
//                               "VALUES (:Barcode, :Product_Name,:Product_Sale_Price,:Product_Retail_Price,:Product_Quantities,:Product_Type,:Product_Description)");
//                 query.bindValue(":Barcode",P.get_ProductID());
//                 query.bindValue(":Product_Name",P.get_ProductName());
//                 query.bindValue(":Retail_Price",P.get_retailPrice());
//                 query.bindValue(":Sale_Price",P.get_SalePrice());
//                 query.bindValue(":Total_Quantity",P.get_total_Quantity());
//                 query.bindValue(":Product_Type",P.get_ProductType());
//                 query.bindValue(":Product_Description",P.get_ProductDescription());
//                 if(query.exec())
//                 {
//                     qDebug() << "Data inserted successfully!";
//                     accept();
//                 }
//                 else
//                 {
//                     qDebug() << "Data insertion Failed!";
//                     QMessageBox::critical(this, "ERROR", "Failed to insert data into the database."+query.lastError().text());
//                 }
//             }
//         }
//     }
//     else
//     {
//         qDebug()<<"Query Execution Failed"<<Qt::endl;
//         QMessageBox::critical(this,"Query Error",query.lastError().text());
//     }
// }

