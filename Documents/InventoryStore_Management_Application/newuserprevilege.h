#ifndef NEWUSERPREVILEGE_H
#define NEWUSERPREVILEGE_H

#include <QDialog>

namespace Ui {
class NewUserPrevilege;
}

class NewUserPrevilege : public QDialog
{
    Q_OBJECT

public:
    explicit NewUserPrevilege(QWidget *parent = nullptr);
    ~NewUserPrevilege();

private slots:
    void on_pushButton_create_clicked();
    QString privilegeCheck();
    bool isDuplicateUser(const QString &name);
private:
    Ui::NewUserPrevilege *ui;
};

#endif // NEWUSERPREVILEGE_H
