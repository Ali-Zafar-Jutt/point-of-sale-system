#ifndef INVENTORY_DIALOG_H
#define INVENTORY_DIALOG_H
#include <QDialog>
#include<QString>
namespace Ui
{
class Inventory_Dialog;
}
class Inventory_Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Inventory_Dialog(QWidget *parent = nullptr);
    ~Inventory_Dialog();
private slots:
    void on_AddnewInventory_returnPressed();
    void loadList();
    void on_searchInventory_textEdited(const QString &arg1);
private:
    Ui::Inventory_Dialog *ui;
};
#endif // INVENTORY_DIALOG_H
