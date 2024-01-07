#ifndef SALESHISTORY_FILE_H
#define SALESHISTORY_FILE_H

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

    void on_pushButton_clicked();

    void on_Generate_Button_clicked();

private:
    Ui::SalesHistory *ui;
};

#endif // SALESHISTORY_FILE_H
