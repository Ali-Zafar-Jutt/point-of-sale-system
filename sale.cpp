#include "sale.h"
#include "qsqlerror.h"
#include "ui_sale.h"
#include<QMessageBox>
#include<QDebug>
#include <qsqlquery.h>
#include <QSortFilterProxyModel>
#include <QItemDelegate>
#include <QDateTime>
class EditableDelegate : public QItemDelegate
{
public:
    EditableDelegate(QObject* parent = nullptr) : QItemDelegate(parent) {}

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        qDebug()<<"Editing Index = "<<index.row()<<Qt::endl;
        if (index.column() == 3)
        {
            return QItemDelegate::createEditor(parent, option, index);
        }
        return nullptr;
    }
};
Sale::Sale(QWidget *parent, QString p) :
    QDialog(parent),
    ui(new Ui::Sale),
    privilege(p)
{
    ui->setupUi(this);
    auto * table = ui->SaleTable;
    table->setItemDelegate(new EditableDelegate());
    QSqlQuery Q;
    Q.prepare("Select * from TaxRate");
    if(Q.exec())
    {
        while(Q.next())
        {
            int n = Q.value(0).toInt();
            ui->spinBox->setValue(n);
        }
    }
    ui->SaleTable->setColumnWidth(0,50);
}
Sale::~Sale()
{
    delete ui;
}


int Sale::row = 0;
int Sale::newRow = 0;
void Sale::on_lineEdit_scan_returnPressed()
{
    QTableWidget * table = ui->SaleTable;
    int quantity=1;
    QTableWidgetItem * pointer = nullptr;
    QLineEdit * line = ui->lineEdit_scan;
    QString arg = line->text().trimmed();
    bool found = false;
    int currentQuantity = 0;
    for(int i=0;i<table->rowCount();i++)
    {
        QTableWidgetItem * check = table->item(i,1);
        if(check && check->text() == arg)
        {
            currentQuantity = table->item(i,3)->text().toInt();
            ++currentQuantity;
            qDebug()<<"Total Quantity Saved: "<<quantity<<Qt::endl;
            qDebug()<<"Actual Quantity = "<<currentQuantity<<Qt::endl;
            --newRow;
            found=true;
            table->setRowCount(++newRow);
            qDebug()<<"Product Found at Index: "<<i<<Qt::endl;
            QSqlQuery Q;
            Q.prepare("Select * from Inventory_Table where Barcode = :arg");
            Q.bindValue(":arg",arg);
            if (Q.exec() && Q.next())
            {
                qDebug()<<"Product Match Found: "<<Qt::endl;
                int check = Q.value(2).toInt();
                qDebug()<<"Check = "<<check<<Qt::endl;
                if(currentQuantity>check)
                {
                    qDebug()<<"The Current Quantity Found Greater Than The Quantity Available In DB"<<Qt::endl;
                    qDebug()<<"CurrentQuantity: "<<currentQuantity<<Qt::endl;
                    QMessageBox::information(this,"Error","Max Quantity Available For This Product is: "+QString::number(check));
                    break;
                }
                else if(currentQuantity<=check)
                {
                    qDebug()<<"The Current Quantity is Less Than the Quantity Available in DB"<<Qt::endl;
                    qDebug()<<"Current Quantity: "<<currentQuantity<<Qt::endl;
                    qDebug()<<"Updated Current Quantity: "<<currentQuantity<<Qt::endl;
                    float price = Q.value(3).toFloat();
                    float totalPrice = price * currentQuantity;
                    table->setItem(i,3, new QTableWidgetItem(QString::number(currentQuantity)));
                    table->setItem(i,5, new QTableWidgetItem(QString::number(totalPrice)));
                    qDebug() << "Current Quantity = " << currentQuantity << Qt::endl;
                    break;
                }
                else
                {
                    ;
                }
                qDebug() << "Row = " << row << " newRow = " << newRow << Qt::endl;
                ui->lineEdit_scan->clear();
            }
            else
            {
                QMessageBox::critical(this,"Error",Q.lastError().text());
            }

        }
        else
        {
            qDebug()<<"At Index "<<i<<". The Product is Not Found"<<Qt::endl;
        }
    }
    if(!found)
    {
        QSqlQuery query;
        query.prepare("Select * from Inventory_Table where Barcode = :arg");
        query.bindValue(":arg",arg);
        if(query.exec())
        {
            qDebug()<<"Query Executed Successfully"<<Qt::endl;

            while(query.next())
            {
                if(query.value(2).toInt()==0)
                {
                    QMessageBox::information(this,"Error","This Product Is Out Of Stock");
                    break;
                }
                qDebug()<<"1: "<<query.value(0).toString()<<Qt::endl;
                qDebug()<<"2: "<<query.value(1).toString()<<Qt::endl;
                qDebug()<<"3: "<<query.value(2).toString()<<Qt::endl;
                qDebug()<<"4: "<<query.value(3).toString()<<Qt::endl;
                qDebug()<<"5: "<<query.value(4).toString()<<Qt::endl;
                qDebug()<<"6: "<<query.value(5).toString()<<Qt::endl;
                qDebug()<<"7: "<<query.value(6).toString()<<Qt::endl;
                QPushButton *button = new QPushButton("DEL");
                QFont font;
                font.setBold(true);
                button->setFont(font);
                table->setRowCount(++newRow);
                table->setCellWidget(row, 0, button);
                table->setItem(row,1,new QTableWidgetItem(query.value(0).toString()));
                pointer = table->item(row,1);
                pointer->setTextAlignment(Qt::AlignCenter);
                if(query.value(0).toString().length()>15)
                {
                    table->resizeColumnToContents(1);
                }
                table->setItem(row,2,new QTableWidgetItem(query.value(1).toString()));
                pointer = table->item(row,2);
                pointer->setTextAlignment(Qt::AlignCenter);
                if(query.value(1).toString().length()>15)
                {
                    table->resizeColumnToContents(2);
                }
                table->setItem(row,3,new QTableWidgetItem(QString::number(quantity)));
                pointer = table->item(row,3);
                pointer->setTextAlignment(Qt::AlignCenter);
                int total = query.value(2).toInt();
                qDebug()<<"Total Quantity Available: "<<total<<Qt::endl;
                table->setItem(row,4,new QTableWidgetItem(QString::number(query.value(3).toFloat())));
                pointer = table->item(row,4);
                pointer->setTextAlignment(Qt::AlignCenter);
                table->setItem(row,5,new QTableWidgetItem(QString::number(query.value(3).toFloat())));
                pointer = table->item(row,5);
                pointer->setTextAlignment(Qt::AlignCenter);
                table->setItem(row,6,new QTableWidgetItem(query.value(5).toString()));
                pointer = table->item(row,6);
                pointer->setTextAlignment(Qt::AlignCenter);
                if(query.value(5).toString().length()>15)
                {
                    table->resizeColumnToContents(6);
                }
                table->setItem(row,7,new QTableWidgetItem(query.value(6).toString()));
                pointer = table->item(row,7);
                pointer->setTextAlignment(Qt::AlignCenter);
                if(query.value(6).toString().length()>15)
                {
                    table->resizeColumnToContents(7);
                }
                row++;
                qDebug()<<"Row = "<<row<<" newRow = "<<newRow<<Qt::endl;
            }
            ui->lineEdit_scan->clear();
        }
        else
        {
            QMessageBox::information(this,"Error","Query Not Executed"+query.lastError().text());
        }
    }
}

void Sale::currentQuantity(int n)
{
   num = n;
}

void Sale::on_SaleTable_cellDoubleClicked(int row, int column)
{
    qDebug()<<" At Column "<<column<<" And Row "<<row<<" Is Doubled Clicked "<<Qt::endl;
    if(column==3)
    {
        int quantity = ui->SaleTable->item(row,column)->text().toInt();
        qDebug()<<"Current Quantity : "<<quantity<<Qt::endl;
        currentQuantity(quantity);
    }
}

void Sale::on_SaleTable_cellChanged(int row, int column)
{
    QTableWidgetItem * pointer = nullptr;
    qDebug() << "Row: " << row << Qt::endl << "Column: " << column << Qt::endl;
    int actualQuantity = num;
    int checkQuantity = 0;
    QTableWidget* table = ui->SaleTable;
    try
    {
        if (column==3)
        {
            QTableWidgetItem* ID = table->item(row,1);
            QTableWidgetItem* changedQuantity = table->item(row, column);
            QTableWidgetItem* priceItem = table->item(row, column+1);
            int check = changedQuantity->text().toInt();
            if (changedQuantity && priceItem)
            {
                QString barcode = ID->text();
                QSqlQuery Q;
                Q.prepare("Select * from Inventory_Table where Barcode = :barcode");
                Q.bindValue(":barcode",barcode);
                if(Q.exec() && Q.next())
                {
                    checkQuantity = Q.value(2).toInt();
                    qDebug()<<"Initial Quantity: "<<actualQuantity<<Qt::endl;
                    qDebug()<<"Total Quantity for Product ID "<<barcode<<" Available in DB is/are: "<<checkQuantity<<Qt::endl;
                    qDebug()<<"Total Read Quantity For This Product From QTable is/are: "<<check<<Qt::endl;
                    if(check>checkQuantity)
                    {
                        table->setItem(row,column,new QTableWidgetItem(QString::number(actualQuantity)));
                        pointer = table->item(row,column);
                        pointer->setTextAlignment(Qt::AlignCenter);
                        float price = Q.value(3).toFloat();
                        table->setItem(row,column+2,new QTableWidgetItem(QString::number(actualQuantity*price)));
                        pointer = table->item(row,column+2);
                        pointer->setTextAlignment(Qt::AlignCenter);
                        QMessageBox::critical(this,"Error","Insufficient quantity in stock. Available quantity: "+QString::number(checkQuantity));
                    }
                    else if(check<=checkQuantity)
                    {
                        float price = Q.value(3).toFloat();
                        qDebug()<<"Price of Single Product: "<<price<<Qt::endl;
                        table->setItem(row,column+2,new QTableWidgetItem(QString::number(check*price)));
                        pointer = table->item(row,column+2);
                        pointer->setTextAlignment(Qt::AlignCenter);
                    }
                }
            }
        }
    }
    catch(const std::exception& ex)
    {
        QMessageBox::critical(this, "Error", ex.what());
    }
}

void Sale::on_pushButton_clicked()
{
    QDateTime currentDate = QDateTime::currentDateTime();
    QString formattedDate = currentDate.toString("yyyy-MM-dd hh:mm:ss");
    QString saleReference = currentDate.toString("yyyyMMddhhmmss");
    qDebug()<<"Current Date and Time: "<<formattedDate<<Qt::endl;
    QTableWidget * table = ui->SaleTable;
    try
    {
        int totalScannedProducts = table->rowCount();
        qDebug()<<"Total Scanned Products: "<<totalScannedProducts<<Qt::endl;
        QString Product_ID = "";
        QString Product_Name = "";
        int quantity = 0;
        float totalPrice = 0;
        int total=0;
        int availableInDB=0;
        for(int i = 0; i< totalScannedProducts; i++)
        {
            Product_ID = table->item(i,0)->text();
            Product_Name = table->item(i,1)->text();
            quantity = table->item(i,2)->text().toInt();
            totalPrice = table->item(i,4)->text().toFloat();
            qDebug()<<"Scanned ID's = "<<Product_ID<<Qt::endl;
            qDebug()<<"Product Quantity = "<<quantity<<Qt::endl;
            QSqlQuery query;
            query.prepare("select * from Inventory_Table where Barcode=:Product_ID");
            query.bindValue(":Product_ID",Product_ID);
            if(query.exec() && query.next())
            {
                qDebug()<<"Product ID: "<<Product_ID<<" Found and Total Quantity Remaining is : "<<query.value(2).toString().toInt()<<Qt::endl;
                availableInDB = query.value(2).toInt();
                total = availableInDB - quantity;
                if(total>=0)
                {
                    QSqlQuery Q;
                    Q.prepare("update Inventory_Table set Product_Quantities = :total where Barcode = :Product_ID");
                    Q.bindValue(":Product_ID",Product_ID);
                    Q.bindValue(":total",total);
                    if(Q.exec())
                    {
                        qDebug()<<"Product ID's: "<<"'"<<Product_ID<<"' "<<" Quantity is Updated To "<<total<<Qt::endl;
                        QSqlQuery saleQ;
                        saleQ.prepare("Insert into Sales(ID, Order_ID, Product_Name, Quantity, Price, Date)"
                                    "VALUES(:ID,:Order_ID,:Product_Name,:Quantity,:Price,:Date)");
                        saleQ.bindValue(":ID",saleReference);
                        saleQ.bindValue(":Order_ID",Product_ID);
                        saleQ.bindValue(":Product_Name",Product_Name);
                        saleQ.bindValue(":Quantity",quantity);
                        saleQ.bindValue(":Price",totalPrice);
                        saleQ.bindValue(":Date",formattedDate);
                        if(saleQ.exec())
                        {
                            qDebug()<<"Information Of The Products Sold Are Added In Sales Table"<<Qt::endl;

                        }
                        else
                        {
                            qDebug()<<"Sales Query Not Executed because "<<saleQ.lastError()<<Qt::endl;
                        }
                    }
                }
            }
        }
    }
    catch(std::exception & ex)
    {
        QMessageBox::critical(this,"Error",ex.what());
    }
    while(table->rowCount()>0)
    {
        table->removeRow(0);
    }
}

void Sale::on_pushButton_2_clicked()
{
    QTableWidget *table = ui->SaleTable;
    QList<int> rowsToRemove;
    for (int row = 0; row < table->rowCount(); ++row)
    {
        QTableWidgetItem * item1 = table->item(row, 0);
        QTableWidgetItem * item2 = table->item(row, 1);
        QTableWidgetItem * item3 = table->item(row, 2);
        QTableWidgetItem * item4 = table->item(row, 3);
        QTableWidgetItem * item5 = table->item(row, 4);
        QTableWidgetItem * item6 = table->item(row, 5);
        QTableWidgetItem * item7 = table->item(row, 6);
        if ((item1 && item1->isSelected()) || (item2 && item2->isSelected()) || (item3 && item3->isSelected()) || (item4 && item4->isSelected()) || (item5 && item5->isSelected()) || (item6 && item6->isSelected()) || (item7 && item7->isSelected()))
        {
            rowsToRemove.append(row);
        }
    }
    --newRow;
    --row;
    std::sort(rowsToRemove.begin(), rowsToRemove.end(), std::greater<int>());
    foreach (int row, rowsToRemove)
    {
        table->removeRow(row);
    }
    QTableWidgetItem * item = table->item(0,0);
    if(!item)
    {
        newRow=0;
        row=0;
    }
}



void Sale::on_Reset_button_clicked()
{
    QTableWidget * table = ui->SaleTable;
    while(table->rowCount()>0)
    {
        table->removeRow(0);
    }
    newRow=0;
    row=0;
}


void Sale::on_spinBox_textChanged(const QString &arg1)
{
    ui->spinBox->setEnabled(true);
    if (privilege == "STANDARDUSER" || privilege == "ADMINUSER")
    {
        int newRate = arg1.toInt();
        QSqlQuery Q;
        Q.prepare("UPDATE TaxRate SET rate = :newRate");
        Q.bindValue(":newRate", newRate);

        if (Q.exec())
        {
            qDebug() << "Tax Rate Updated Successfully." << Qt::endl;
        }
        else
        {
            qDebug() << "Update failed: " << Q.lastError();
        }
    }
    else
    {
        ui->spinBox->setEnabled(false);
    }
}


