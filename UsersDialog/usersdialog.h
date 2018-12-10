#ifndef USERSDIALOG_H
#define USERSDIALOG_H

#include <QDialog>
#include <QSqlRelationalTableModel>

namespace Ui {
class UsersDialog;
}

class UsersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UsersDialog(QWidget *parent = nullptr);
    ~UsersDialog();


private:
    Ui::UsersDialog *ui;
    QSqlRelationalTableModel *modelUsers;
private:
    void createModel();
    void createUI();
};

#endif // USERSDIALOG_H
