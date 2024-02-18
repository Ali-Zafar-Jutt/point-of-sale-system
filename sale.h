#ifndef SALE_H
#define SALE_H
#include <QDialog>

namespace Ui {
class Sale;
}

class Sale : public QDialog
{
    Q_OBJECT

public:
    explicit Sale(QWidget *parent = nullptr, QString p= NULL);
    ~Sale();
    static int row;
    static int newRow;
    int num;

private slots:

    void on_lineEdit_scan_returnPressed();

    void on_SaleTable_cellChanged(int row, int column);

    void on_SaleTable_cellDoubleClicked(int row, int column);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_Reset_button_clicked();

    void on_spinBox_textChanged(const QString &arg1);

private:
    Ui::Sale *ui;
    QString privilege;
    void currentQuantity(int n);
};

#endif // SALE_H
