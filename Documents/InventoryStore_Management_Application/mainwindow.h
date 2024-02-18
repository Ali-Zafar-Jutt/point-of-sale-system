#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <mainmenu.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, QString s="");
    ~MainWindow();
private slots:
    void on_pushButton_AddUser_clicked();
    void openLayout(QDialog* ql);
    void on_pushButton_ViewHistory_clicked();

    void on_pushButton_AddSale_clicked();

    void on_pushButton_Inventory_clicked();

    void on_SignOut_Button_clicked();

private:
    Ui::MainWindow *ui;
    QString u;
};
#endif // MAINWINDOW_H
