#ifndef NEWPRODUCTINFO_H
#define NEWPRODUCTINFO_H
#include "Product.h"
#include <QString>
#include <QDialog>

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
private:
    QString barCode;
    Ui::Newproductinfo *ui;
    bool buttonClicked = false;
};

#endif // NEWPRODUCTINFO_H
