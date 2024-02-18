#include "inventory_dialog.h"
#include "qdebug.h"
#include "qmessagebox.h"
#include "qsqlquery.h"
#include "ui_inventory_dialog.h"
#include "Product.h"
#include "ProductArraylist.h"
#include<QLineEdit>
#include "newproductinfo.h"
#include<QSqlDatabase>
Inventory_Dialog::Inventory_Dialog(QWidget *parent) :QDialog(parent),ui(new Ui::Inventory_Dialog)
{
    ui->setupUi(this);
    loadList();
}
void Inventory_Dialog::loadList()
{
    Product P;
    int tp = products.count();
    qDebug()<<"Total Product Available "<<tp<<Qt::endl;
    QTableWidget * item = ui->ScanItem_Table;
    item->setRowCount(tp);
    for(int i=0;i<tp;i++)
    {
        qDebug()<<"Displaying Product"<<Qt::endl;
        P = products[i];
        QTableWidgetItem * productName = new QTableWidgetItem(P.get_ProductName());
        QTableWidgetItem * salePrice = new QTableWidgetItem(QString::number(P.get_SalePrice()));
        QTableWidgetItem * retailPrice = new QTableWidgetItem(QString::number(P.get_retailPrice()));
        QTableWidgetItem * totalQuantity = new QTableWidgetItem(QString::number(P.get_total_Quantity()));
        item->setItem(i,0,productName);
        item->setItem(i,1,retailPrice);
        item->setItem(i,2,salePrice);
        item->setItem(i,3,totalQuantity);
    }
}
Inventory_Dialog::~Inventory_Dialog()
{
    delete ui;
}
void Inventory_Dialog::on_AddnewInventory_returnPressed()
{
    QLineEdit * line = findChild<QLineEdit*>("AddnewInventory");
    if(line->text().isEmpty())
    {
        QMessageBox::critical(this,"ERORR!","No Product Scanned");
    }
    else
    {
        QString barCodeText = line->text();
        QSqlQuery query;
        query.prepare("Select * from Inventory_Table Where Barcode = :barCodeText");
        query.bindValue(":barCodeText",barCodeText);
        if(query.exec() && query.next())
        {
            QMessageBox::critical(this,"Error","The Barcode Already Exists");
        }
        else
        {
            Newproductinfo * newproduct = new Newproductinfo(this,barCodeText);
            line->clear();
            newproduct->exec();
        }
    }
}
void Inventory_Dialog::on_searchInventory_textEdited(const QString &arg1)
{
    QString box = ui->comboBox->currentText();
    QLineEdit * line = ui->searchInventory;
    QTableWidget * table = ui->ScanItem_Table;
    if(box == "Search By ID")
    {
        if(arg1.isEmpty())
        {
            qDebug()<<"Arg1 = "<<arg1<<Qt::endl;
            while(table->rowCount()>0)
            {
                table->removeRow(0);
            }
        }
        else
        {
            while(table->rowCount()>0)
            {
                table->removeRow(0);
            }
            qDebug()<<"Arg1 = "<<arg1<<Qt::endl;
            QSqlQuery Q;
            Q.prepare("SELECT * FROM Inventory_Table WHERE Barcode = :arg1");
            Q.bindValue(":arg1",arg1);
            if(Q.exec())
            {
                qDebug()<<"Query Executed Successfully"<<Qt::endl;
                table->setRowCount(Q.size());
                int currentRow = 0;
                while(Q.next())
                {
                    qDebug()<<"1: "<<Q.value(0).toString()<<Qt::endl;
                    qDebug()<<"2: "<<Q.value(1).toString()<<Qt::endl;
                    qDebug()<<"3: "<<Q.value(2).toString()<<Qt::endl;
                    qDebug()<<"4: "<<Q.value(3).toString()<<Qt::endl;
                    qDebug()<<"5: "<<Q.value(4).toString()<<Qt::endl;
                    qDebug()<<"6: "<<Q.value(5).toString()<<Qt::endl;
                    qDebug()<<"7: "<<Q.value(6).toString()<<Qt::endl;
                    table->setItem(currentRow,0,new QTableWidgetItem (Q.value(0).toString()));
                    table->setItem(currentRow,1,new QTableWidgetItem (Q.value(1).toString()));
                    table->setItem(currentRow,2,new QTableWidgetItem(QString::number(Q.value(4).toInt())));
                    table->setItem(currentRow,3,new QTableWidgetItem(QString::number(Q.value(3).toFloat())));
                    table->setItem(currentRow,4,new QTableWidgetItem(QString::number(Q.value(2).toFloat())));
                    table->setItem(currentRow,5,new QTableWidgetItem(Q.value(5).toString()));
                    table->setItem(currentRow,6,new QTableWidgetItem(Q.value(6).toString()));
                    currentRow++;
                }
            }
        }
    }
    else if(box == "Search By Name")
    {
        if(arg1.isEmpty())
        {
            qDebug()<<"arg1 = "<<arg1<<Qt::endl;
            while(table->rowCount()>0)
            {
                table->removeRow(0);
            }
        }
        else
        {

            QSqlQuery Q;
            Q.prepare("Select * from Inventory_Table where Product_Name like:arg1 order by Product_Name asc");
            Q.bindValue(":arg1","%"+arg1+"%");
            if(Q.exec())
            {
                table->setRowCount(Q.size());
                qDebug() << "Query Executed Successfully" << Qt::endl;
                int currentRow = 0;
                while(Q.next())
                {
                    qDebug() << "1: " << Q.value(0).toString() << Qt::endl;
                    qDebug() << "2: " << Q.value(1).toString() << Qt::endl;
                    qDebug() << "3: " << Q.value(2).toString() << Qt::endl;
                    qDebug() << "4: " << Q.value(3).toString() << Qt::endl;
                    qDebug() << "5: " << Q.value(4).toString() << Qt::endl;
                    qDebug() << "6: " << Q.value(5).toString() << Qt::endl;
                    qDebug() << "7: " << Q.value(6).toString() << Qt::endl;
                    table->setItem(currentRow,0,new QTableWidgetItem (Q.value(0).toString()));
                    table->setItem(currentRow,1,new QTableWidgetItem (Q.value(1).toString()));
                    table->setItem(currentRow,2,new QTableWidgetItem(QString::number(Q.value(4).toInt())));
                    table->setItem(currentRow,3,new QTableWidgetItem(QString::number(Q.value(3).toFloat())));
                    table->setItem(currentRow,4,new QTableWidgetItem(QString::number(Q.value(2).toFloat())));
                    table->setItem(currentRow,5,new QTableWidgetItem(Q.value(5).toString()));
                    table->setItem(currentRow,6,new QTableWidgetItem(Q.value(6).toString()));
                    currentRow++;

                }
            }
        }
    }
    else
    {
        QMessageBox::information(this,"Error","Select Search Option");
        line->clear();
    }







//    qDebug()<<"Product Searching Starts "<<Qt::endl;
//    QLineEdit * line = findChild<QLineEdit*>("searchInventory");
//    QTableWidgetItem **productName;
//    QTableWidgetItem **retailPrice;
//    QTableWidgetItem **salePrice;
//    QTableWidgetItem **totalQuantity;
//    QList<QTableWidgetItem *> productList;
//    QList<QTableWidgetItem *> retailPriceList;
//    QList<QTableWidgetItem *> salePriceList;
//    QList<QTableWidgetItem *> totalQuantityList;
//    QRadioButton * sbid = findChild<QRadioButton*>("radioButton_searchByID");
//    QRadioButton * sbn = findChild<QRadioButton*>("radioButton_searchByName");
//    QTableWidget *table = ui->ScanItem_Table;
//    QSqlQuery query("Select * Inventory_Table");
//    while (query.next())
//    {
//        ;

//    }
//    bool found = false;
//    int matchingProductCount = 0;  // Count of matching products
//    int t = products.count();
//    int i=0;
//    Product P;
//    if(sbn->isChecked())
//    {
//        for(i=0;i<t;i++)
//        {
//            P = products[i];
//            QString check = P.get_ProductName();
//            if (check.contains(arg1, Qt::CaseInsensitive))
//            {
//                ++matchingProductCount;
//                found = true;
//            }
//        }
//        qDebug() << "Total Products Matched = " << matchingProductCount << Qt::endl;
//        productName = new QTableWidgetItem *[matchingProductCount];
//        retailPrice = new QTableWidgetItem *[matchingProductCount];
//        salePrice = new QTableWidgetItem *[matchingProductCount];
//        totalQuantity = new QTableWidgetItem *[matchingProductCount];
//        int itemcount=0;
//        for (int i = 0; i <t; i++)
//        {
//            P = products[i];
//            QString check = P.get_ProductName();
//            if (check.contains(arg1, Qt::CaseInsensitive))
//            {
//                productName[itemcount]= new QTableWidgetItem(P.get_ProductName());
//                retailPrice[itemcount]= new QTableWidgetItem(QString::number(P.get_retailPrice()));
//                salePrice[itemcount] = new QTableWidgetItem(QString::number(P.get_SalePrice()));
//                totalQuantity[itemcount] = new QTableWidgetItem(QString::number(P.get_total_Quantity()));
//                ++itemcount;
//            }
//        }
//        while(table->rowCount()>1)
//        {
//            table->removeRow(1);
//        }
//        for(int i=0;i<itemcount;i++)
//        {
//            productList.append(productName[i]);
//            retailPriceList.append(retailPrice[i]);
//            salePriceList.append(salePrice[i]);
//            totalQuantityList.append(totalQuantity[i]);
//        }
//        table->setRowCount(matchingProductCount);
//        for (int i = 0; i < itemcount; i++)
//        {
//            QTableWidgetItem * name = new QTableWidgetItem (*productList.at(i));
//            QTableWidgetItem * retail = new QTableWidgetItem(*retailPriceList.at(i));
//            QTableWidgetItem * sale = new QTableWidgetItem(*salePriceList.at(i));
//            QTableWidgetItem * quantity = new QTableWidgetItem(*totalQuantityList.at(i));
//            table->setItem(i,0,name);
//            table->setItem(i,1,retail);
//            table->setItem(i,2,sale);
//            table->setItem(i,3,quantity);
//        }

//        // Clean up the dynamically allocated QTableWidgetItem objects
//        for (int i = 0; i < matchingProductCount; i++)
//        {
//            delete productName[i];
//            delete retailPrice[i];
//            delete salePrice[i];
//            delete totalQuantity[i];
//        }
//        delete[] productName;
//        delete[] retailPrice;
//        delete[] salePrice;
//        delete[] totalQuantity;
//    }
//    else if(sbid->isChecked())
//    {
//        for(i=0;i<t;i++)
//        {
//            P = products[i];
//            QString check = P.get_ProductID();
//            int result = check.compare(arg1);
//            if (result==0)
//            {
//                ++matchingProductCount;
//                found = true;
//            }
//        }
//        qDebug() << "Total Products Matched = " << matchingProductCount << Qt::endl;
//        productName = new QTableWidgetItem *[matchingProductCount];
//        retailPrice = new QTableWidgetItem *[matchingProductCount];
//        salePrice = new QTableWidgetItem *[matchingProductCount];
//        totalQuantity = new QTableWidgetItem *[matchingProductCount];
//        int itemcount=0;
//        for (int i = 0; i <t; i++)
//        {
//            P = products[i];
//            QString check = P.get_ProductID();
//            int result = check.compare(arg1);
//            if (result==0)
//            {
//                productName[itemcount]= new QTableWidgetItem(P.get_ProductName());
//                retailPrice[itemcount]= new QTableWidgetItem(QString::number(P.get_retailPrice()));
//                salePrice[itemcount] = new QTableWidgetItem(QString::number(P.get_SalePrice()));
//                totalQuantity[itemcount] = new QTableWidgetItem(QString::number(P.get_total_Quantity()));
//                ++itemcount;
//            }
//        }
//        while(table->rowCount()>1)
//        {
//            table->removeRow(1);
//        }
//        for(int i=0;i<itemcount;i++)
//        {
//            productList.append(productName[i]);
//            retailPriceList.append(retailPrice[i]);
//            salePriceList.append(salePrice[i]);
//            totalQuantityList.append(totalQuantity[i]);
//        }
//        table->setRowCount(matchingProductCount);
//        for (int i = 0; i < itemcount; i++)
//        {
//            QTableWidgetItem * name = new QTableWidgetItem (*productList.at(i));
//            QTableWidgetItem * retail = new QTableWidgetItem(*retailPriceList.at(i));
//            QTableWidgetItem * sale = new QTableWidgetItem(*salePriceList.at(i));
//            QTableWidgetItem * quantity = new QTableWidgetItem(*totalQuantityList.at(i));
//            table->setItem(i,0,name);
//            table->setItem(i,1,retail);
//            table->setItem(i,2,sale);
//            table->setItem(i,3,quantity);
//        }

//        // Clean up the dynamically allocated QTableWidgetItem objects
//        for (int i = 0; i < matchingProductCount; i++)
//        {
//            delete productName[i];
//            delete retailPrice[i];
//            delete salePrice[i];
//            delete totalQuantity[i];
//        }
//        delete[] productName;
//        delete[] retailPrice;
//        delete[] salePrice;
//        delete[] totalQuantity;
//    }
//    else
//    {
//        QMessageBox::information(this,"Error","Select Search Option");
//        line->clear();
//    }
}



