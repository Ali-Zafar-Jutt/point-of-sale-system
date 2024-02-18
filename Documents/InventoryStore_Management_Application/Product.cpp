#include "Product.h"
#include<string>
int Product::total_products=0;
Product::Product(QString n, QString id, float sp, float rp, int tq,QString t, QString d):name(n),SalePrice(sp),RetailPrice(rp),totalQuantity(tq),productID(id),productType(t),productDescription(d)
{
    total_products++;
}
void Product::set_productType(QString p)
{
    productType = p;
}
void Product::set_productDescription(QString p)
{
    productDescription = p;
}
void Product::set_PoductName(QString pn)
{
    name = pn;
    check++;
    if(check==5)
    {
        total_products++;
    }
}
void Product::set_RetailPrice(float rp)
{
    RetailPrice = rp;
    check++;
    if(check==5)
    {
        total_products++;
    }
}
void Product::set_SalesPrice(float sp)
{
    SalePrice = sp;
    check++;
    if(check==5)
    {
        total_products++;
    }
}
QString Product::get_ProductName()
{
    return name;
}
void Product::set_productID(QString id)
{
    productID=id;
    check++;
    if(check==5)
    {
        total_products++;
    }
}
void Product::set_TotalQuantity(int tq)
{
    totalQuantity = tq;
    check++;
    if(check==5)
    {
        total_products++;
    }
}
float Product::get_SalePrice()
{
    return SalePrice;
}
float Product::get_retailPrice()
{
    return RetailPrice;
}
int Product::get_total_Quantity()
{
    return totalQuantity;
}
void Product::TotalProducts_Available()
{
    if(check==5)
    {
        total_products++;
    }
}
void Product::Delete_Product()
{
    total_products--;
}
QString Product:: get_ProductID()
{
    return productID;
}
QString Product::get_ProductType()
{
    return productType;
}
QString Product::get_ProductDescription()
{
    return productDescription;
}
