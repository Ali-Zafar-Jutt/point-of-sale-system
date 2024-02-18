#include "__new___product.h"
#include "ui___new___product.h"
#include"Product.h"
#include "ProductArraylist.h"
#include <QMessageBox>
__NEW___PRODUCT::__NEW___PRODUCT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::__NEW___PRODUCT)
{
    ui->setupUi(this);
}

__NEW___PRODUCT::~__NEW___PRODUCT()
{
    delete ui;
}

void __NEW___PRODUCT::on_buttonBox_accepted()
{
    QMessageBox::information(this,"Info","Message Box Clicked");
}

