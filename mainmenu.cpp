// #include "mainmenu.h"
// #include "inventory_dialog.h"
// #include "mainwindow.h"
// #include "qmessagebox.h"
// #include "saleshistory.h"
// #include"ui_mainmenu.h"
// #include"sale.h"
// #include"mainmenu.h"
// #include "newuserprevilege.h"
// #include <QTableWidget>
// #include<QStatusBar>
// MainMenu::MainMenu(QWidget *parent,QString s):
//     QDialog(parent),
//     ui(new Ui::MainMenu),
//     u(s)
// {
//     ui->setupUi(this);
// }
// MainMenu::~MainMenu()
// {
//     delete ui;
// }
// void MainMenu::openLayout(QDialog* ql)
// {
//     ;
// }
// void MainMenu::on_pushButton_AddSale_clicked()
// {
//     Sale::row=0;
//     Sale::newRow=0;
//     Sale * sale = new Sale (this,u);
//     openLayout(sale);
// }
// void MainMenu::on_pushButton_Inventory_clicked()
// {
//     if(u=="ADMINUSER")
//     {
//         Inventory_Dialog * dialog = new Inventory_Dialog(this);
//         Sale::row=0;
//         Sale::newRow=0;
//         openLayout(dialog);
//     }
//     else if(u=="STANDARDUSER")
//     {
//         Inventory_Dialog * dialog = new Inventory_Dialog(this);
//         Sale::row=0;
//         Sale::newRow=0;
//         openLayout(dialog);
//     }
//     else
//     {
//         QMessageBox::warning(this,"Unauthorized User","Permission Not Granted");
//     }
// }
// void MainMenu::on_pushButton_AddUser_clicked()
// {
//     if(u=="ADMINUSER")
//     {
//         NewUserPrevilege * newuser = new NewUserPrevilege(this);
//         Sale::row=0;
//         Sale::newRow=0;
//         openLayout(newuser);
//     }
//     else if(u=="STANDARDUSER")
//     {
//         NewUserPrevilege * newuser = new NewUserPrevilege(this);
//         Sale::row=0;
//         Sale::newRow=0;
//         openLayout(newuser);
//     }
//     else
//     {
//         QMessageBox::critical(this,"Unauthorized User","Permission Not Granted");
//     }
// }
// void MainMenu::on_pushButton_ViewHistory_clicked()
// {
//     if(u=="ADMINUSER")
//     {
//         SalesHistory * history = new SalesHistory(this);
//         Sale::row=0;
//         Sale::newRow=0;
//         openLayout(history);
//     }
//     else if(u=="STANDARDUSER")
//     {
//         SalesHistory * history = new SalesHistory(this);
//         Sale::row=0;
//         Sale::newRow=0;
//         openLayout(history);
//     }
//     else
//     {
//         QMessageBox::critical(this,"Unauthorized User","Permission Not Granted");
//     }
// }
// void MainMenu::on_SignOut_Button_clicked()
// {
//     MainWindow * mainmenu = new MainWindow();
//     close();
//     mainmenu->show();
// }
