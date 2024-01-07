#ifndef __NEW___PRODUCT_H
#define __NEW___PRODUCT_H

#include <QDialog>

namespace Ui {
class __NEW___PRODUCT;
}

class __NEW___PRODUCT : public QDialog
{
    Q_OBJECT

public:
    explicit __NEW___PRODUCT(QWidget *parent = nullptr);
    ~__NEW___PRODUCT();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::__NEW___PRODUCT *ui;
};

#endif // __NEW___PRODUCT_H
