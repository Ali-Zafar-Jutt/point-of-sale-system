#ifndef SALESHISTORY_H
#define SALESHISTORY_H

#include <QDialog>

namespace Ui {
class SalesHistory;
}

class SalesHistory : public QDialog
{
    Q_OBJECT

public:
    explicit SalesHistory(QWidget *parent = nullptr);
    ~SalesHistory();

private slots:
    void on_lineEdit_returnPressed();
    void on_Generate_Button_clicked();

private:
    Ui::SalesHistory *ui;
};

#endif // SALESHISTORY_H
