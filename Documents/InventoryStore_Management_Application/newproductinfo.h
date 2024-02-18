#ifndef NEWPRODUCTINFO_H
#define NEWPRODUCTINFO_H
#include "Product.h"
#include <QString>
#include <QDialog>
#include <qstatusbar.h>
#include <QLabel>

namespace Ui {
class Newproductinfo;
}

class Newproductinfo : public QDialog
{
    Q_OBJECT

public:
    explicit Newproductinfo(QWidget *parent = nullptr,QString code = "");
    ~Newproductinfo();



signals:

private slots:
    void on_pushButton_newproduct_clicked();
    bool isAllDigits(const QString & s);
    bool ValidateFields();
    int * ErrorFieldNum();
    bool checkRetailSalePrice();
    bool isQuantityValid();
    bool ErrorFieldHighlight();
    bool strictNumFieldsHighlight();
private:
    QString barCode;
    int NotNumFields[3];
    Ui::Newproductinfo *ui;
    bool buttonClicked = false;
    QLabel* statusLabel;
};

#endif // NEWPRODUCTINFO_H
