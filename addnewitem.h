#ifndef ADDNEWITEM (INVENTORY)_H
#define ADDNEWITEM(INVENTORY)_H

#include <QDialog>

namespace Ui {
class Inventory_Menu;
}

class Inventory_Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Inventory_Menu(QWidget *parent = nullptr);
    ~Inventory_Menu();

private slots:
void on_lineEdit_ScanNewItem_returnPressed();
private:
    Ui::Inventory_Menu *ui;
};

#endif // ADDNEWITEM(INVENTORY)_H
