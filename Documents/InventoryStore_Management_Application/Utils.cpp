#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QCoreApplication>
#include <QDebug>
class Utils
{
public:
    static void connection()
    {
        try
        {
            QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
            db.setHostName("localhost");
            db.setDatabaseName("pos");
            db.setUserName("root");
            db.setPassword("shippuden");
            if (db.open())
            {
                qDebug() << "Connection created for POS";

                QSqlQuery query;
                query.prepare("SELECT Barcode,Product_Name,Product_Quantity, "
                              "Product_Salesprice, Product_Retailprice, Product_Type, Product_Description "
                              "FROM inventory_table");

                if (!query.exec())
                {
                    qDebug() << "Query execution failed:" << query.lastError().text();
                    QMessageBox::critical(nullptr, "Error", "Database query execution failed.");
                }
            }
            else
            {
                qDebug() << "Database connection failed:" << db.lastError().text();
                QMessageBox::critical(nullptr, "Error", "Database connection failed.");
            }
        }
        catch (const std::exception &ex)
        {
            QMessageBox::warning(nullptr, "Error", ex.what());
        }
    }
};
