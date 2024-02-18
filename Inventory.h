#ifndef INVENTORY_H
#define INVENTORY_H

#include <QDialog>
namespace Ui {
class Signin;
}

class Signin : public QDialog
{
    Q_OBJECT

public:
    explicit Signin(QWidget *parent = nullptr);
    ~Signin();

private:
    Ui::Signin *ui;
};

#endif // INVENTORY_H
