//#include "sales_history.h"
//#include <QPrintPreviewDialog>
//#include <QPainter>
//#include "qdatetime.h"
//#include "qdebug.h"
//#include "qsqlquery.h"
//#include "qtablewidget.h"
//#include<QPrinter>
//#include <QFileDialog>
//Sales_History::Sales_History(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::Sales_History)
//{
//    ui->setupUi(this);
//}

//Sales_History::~Sales_History()
//{
//    delete ui;
//}

//void Sales_History::on_lineEdit_returnPressed()
//{
//    int row=0;
//    QTableWidget * table = ui->SalesHistory_Table;
//    QTableWidgetItem * pointer = nullptr;
//    QString reference = ui->lineEdit->text();
//    QSqlQuery query;
//    query.prepare("Select * from Sales where ID = :reference");
//    query.bindValue(":reference",reference);
//    int i=0;
//    if(query.exec())
//    {
//        while(query.next())
//        {
//            qDebug()<<"1. "<<query.value(0).toString()<<Qt::endl;
//            qDebug()<<"2. "<<query.value(1).toString()<<Qt::endl;
//            qDebug()<<"3. "<<query.value(2).toString()<<Qt::endl;
//            qDebug()<<"4. "<<query.value(3).toInt()<<Qt::endl;
//            qDebug()<<"5. "<<query.value(4).toFloat()<<Qt::endl;
//            qDebug()<<"6. "<<query.value(5).toString()<<Qt::endl;
//            table->setRowCount(++row);
//            table->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
//            pointer = table->item(i,0);
//            pointer->setTextAlignment(Qt::AlignCenter);
//            table->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
//            pointer = table->item(i,1);
//            pointer->setTextAlignment(Qt::AlignCenter);
//            table->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
//            pointer = table->item(i,2);
//            pointer->setTextAlignment(Qt::AlignCenter);
//            table->setItem(i,3,new QTableWidgetItem(QString::number(query.value(3).toInt())));
//            pointer = table->item(i,3);
//            pointer->setTextAlignment(Qt::AlignCenter);
//            table->setItem(i,4,new QTableWidgetItem(QString::number(query.value(4).toFloat())));
//            pointer = table->item(i,4);
//            pointer->setTextAlignment(Qt::AlignCenter);
//            QDate date = query.value(5).toDate();
//            qDebug()<<"date: "<<date<<Qt::endl;
//            QString DateFormate = date.toString("dd-MM-yyyy");
//            qDebug()<<"DateFormate: "<<DateFormate<<Qt::endl;
//            table->setItem(i,5,new QTableWidgetItem(DateFormate));
//            pointer = table->item(i,5);
//            pointer->setTextAlignment(Qt::AlignCenter);
//            i++;
//        }
//    }
//}
//bool isLeap(int y)
//{
//    if(y%100!=0 && y%4==0 && y%400==0)
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}

//void Sales_History::on_generateReport_Button_clicked()
//{
//    QTableWidget * table = ui->SalesHistory_Table;
//    while (table->rowCount() > 1)
//    {
//        table->removeRow(0);
//    }
//    QString box = ui->comboBox->currentText();
//    QDate date = QDate::currentDate();
//    int year = date.year();
//    int month = date.month();
//    int day = date.day();
//    qDebug() << "Actual Day: " << day << Qt::endl;
//    qDebug() << "Actual Month: " << month << Qt::endl;
//    qDebug() << "Actual Year: " << year << Qt::endl;
//    QString startDate = date.toString("yyyy-MM-dd");
//    int searchMonth = month;
//    int searchDay = day;
//    int searchYear = year;
//    qDebug() << "Current Date: " << startDate << Qt::endl;
//    if (box == "Monthly")
//    {
//        searchMonth = searchMonth - 1;
//        if (searchMonth == 0)
//        {
//            searchMonth = 12;
//            searchYear -= 1;
//        }
//        else if (searchMonth == 2)
//        {
//            bool check = false;
//            check = isLeap(searchYear);
//            if (check && day > 28)
//            {
//                qDebug() << "This is A Leap Year" << Qt::endl;
//                searchDay = 29;
//            }
//            else if (!check && day > 28)
//            {
//                searchDay = 28;
//            }
//            else if (check && day == 28)
//            {
//                qDebug() << "This is A Leap Year" << Qt::endl;
//                searchDay = 29;
//            }
//        }
//        QDate newDate(searchYear, searchMonth, searchDay);
//        QString endDate = newDate.toString("yyyy-MM-dd");
//        qDebug() << "Calculated Date: " << endDate << Qt::endl;
//        QSqlQuery Q;
//        Q.prepare("Select * from Sales where Date>=:endDate and Date<=:startDate");
//        Q.bindValue(":startDate", startDate);
//        Q.bindValue(":endDate", endDate);
//        if (Q.exec())
//        {
//            QPrinter printer;
//            printer.setOutputFormat(QPrinter::PdfFormat);
//            printer.setPageSize(QPageSize(QPageSize::A4));
//            QString filePath = QFileDialog::getSaveFileName(this, "Save PDF Report", "", "PDF Files (*.pdf)");
//            if (filePath.isEmpty())
//            {
//                qDebug() << "PDF generation canceled.";
//                return;
//            }
//            printer.setOutputFileName(filePath);
//            QPainter painter(&printer);
//            painter.begin(&printer);
//            QFont mainHeadingFont;
//            mainHeadingFont.setBold(false);
//            mainHeadingFont.setPointSize(14);
//            painter.setFont(mainHeadingFont);
//            QString mainHeading = "Company Name Here\nPOS Sale Summary\n";
//            painter.drawText(QRect(0, 0, printer.width(), 100), Qt::AlignCenter, mainHeading);
//            QFont subHeadingFont;
//            subHeadingFont.setBold(false);
//            subHeadingFont.setPointSize(12);
//            painter.setFont(subHeadingFont);
//            QString subHeading = "Today's Date: " + startDate + "\n\nSelected Date Range:" + "\nFrom Date: " + startDate + "\nEnd Date: " + endDate + "\n";
//            painter.drawText(QRect(10, 100, printer.width(), 120), Qt::AlignLeft, subHeading);

//            int columnX = 10;
//            int columnWidth = 125;
//            int columnHeight = 160; // Increase the height for column headings
//            QFont columnHeadingFont;
//            columnHeadingFont.setBold(false);
//            columnHeadingFont.setPointSize(12);
//            painter.setFont(columnHeadingFont);
//            QStringList columnHeading = {"Sale Reference#", "Barcode", "Product Name", "Quantity", "Price", "Date of Sale"};
//            int width1 = 150;
//            int width2 = 150;
//            int width3 = 150;
//            int width4 = 80;
//            int width5 = 80;
//            int width6 = 100;
//            for (const QString &heading : columnHeading)
//            {
//                if(heading=="Sale Reference#")
//                {
//                    columnWidth = width1;
//                }
//                if(heading=="Barcode")
//                {
//                    columnWidth = width2;
//                }
//                if(heading=="Product Name")
//                {
//                    columnWidth = width3;
//                }
//                if(heading=="Quantity")
//                {
//                    columnWidth = width4;
//                }
//                if(heading=="Price")
//                {
//                    columnWidth = width5;
//                }
//                if(heading=="Date of Sale")
//                {
//                    columnWidth = width6;
//                }
//                painter.drawText(QRect(columnX, 170, columnWidth, columnHeight), Qt::AlignCenter, heading);
//                columnX += columnWidth;
//            }
//            int rowY = 255; // You can adjust this value
//            painter.drawLine(10, rowY + 30, printer.width() - 10, rowY + 30);
//            rowY += 30;
//            int check = 0; // Initialize the check variable
//            while (Q.next())
//            {
//                int columnX2 = 10;
//                int columnWidth2 = 125;
//                QFont rowFont;
//                rowFont.setBold(false);
//                rowFont.setPointSize(12);
//                painter.setFont(rowFont);
//                int tempRowY = rowY; // Temporary variable to store rowY
//                int previousHeight = 0; // Track the height of the text before split
//                for (int col = 0; col < 6; col++)
//                {
//                    QString columnText = Q.value(col).toString();
//                    int columnWidth=0;
//                    if (col == 0 || col == 1 || col == 2)
//                    {
//                        columnWidth = width1;
//                    }
//                    else if(col == 3 || col == 4)
//                    {
//                        columnWidth = width4;
//                    }
//                    else if(col == 5)
//                    {
//                        columnWidth = width6;
//                    }
//                    if (col == 2 && columnText.size() > 17)
//                    {
//                        check++;
//                        int maxCharsPerLine = 17;
//                        for (int i = 0; i < columnText.size(); i += maxCharsPerLine)
//                                    {
//                                        QString subText = columnText.mid(i, maxCharsPerLine);
//                                        qDebug() << subText << Qt::endl;
//                                        QRect textRect(columnX2, tempRowY, columnWidth, 30);

//                                        if (i == 0)
//                                        {
//                                            // Only the first part of the split text needs to adjust the rowY
//                                            painter.drawText(textRect, Qt::AlignCenter, subText);
//                                            previousHeight = painter.fontMetrics().height(); // Store the height
//                                        }
//                                        else
//                                        {
//                                            // For subsequent parts of split text, use the previous height
//                                            tempRowY += previousHeight;
//                                            textRect.moveTop(tempRowY);
//                                            painter.drawText(textRect, Qt::AlignCenter, subText);
//                                        }
//                                    }
//                    }
//                    else
//                    {
//                        painter.drawText(QRect(columnX2, rowY, columnWidth, 30), Qt::AlignCenter, columnText);
//                    }
//                    columnX2 += columnWidth;
//                }

//                if (check > 0)
//                {
//                    rowY += 10;
//                    rowY += 30 * check;
//                    check = 0;
//                    painter.drawLine(10, rowY + 10, printer.width() - 10, rowY + 10);
//                    rowY+=7;
//                }
//                else
//                {
//                    rowY += 30;
//                    painter.drawLine(10, rowY, printer.width() - 10, rowY);
//                }
//            }
//        }
//        qDebug() << "PDF Report generated successfully" << Qt::endl;
//    }
//}

