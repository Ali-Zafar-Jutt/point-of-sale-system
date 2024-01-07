#ifndef PRODUCT_H
#define PRODUCT_H
#include<QString>
class Product
{
    QString name;
    float SalePrice;
    float RetailPrice;
    int totalQuantity;
    QString productID;
    QString productType;
    QString productDescription;
    static int total_products;
    int check;
public:
    Product()
    {
        name = "";
        SalePrice=0.0;
        RetailPrice=0.0;
        totalQuantity=0;
        productID="";
        check=0;
    }
    Product(QString n, QString id, float sp, float rp, int tq, QString t, QString d);
    void set_PoductName(QString pn);
    void set_productID(QString id);
    void set_SalesPrice(float sp);
    void set_RetailPrice(float rp);
    void set_TotalQuantity(int tq);
    void TotalProducts_Available();
    void Delete_Product();
    void set_productType(QString p);
    void set_productDescription(QString p);
    QString get_ProductName();
    float get_SalePrice();
    float get_retailPrice();
    int get_total_Quantity();
    QString get_ProductID();
    QString get_ProductDescription();
    QString get_ProductType();
 };
#endif // PRODUCT_H
