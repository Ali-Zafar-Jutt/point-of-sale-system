#ifndef SALES_HISTORY_H
#define SALES_HISTORY_H

#include <QDialog>

namespace Ui {
class Sales_History;
}

class Sales_History : public QDialog
{
    Q_OBJECT

public:
    explicit Sales_History(QWidget *parent = nullptr);
    ~Sales_History();

private slots:
    void on_lineEdit_returnPressed();
    void on_generateReport_Button_clicked();

private:
    Ui::Sales_History *ui;
};

#endif // SALES_HISTORY_H
