#ifndef USERSDIALOG_H
#define USERSDIALOG_H

#include "tableusersmodel.h"
#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class UsersDialog;
}

class UsersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UsersDialog(QWidget *parent = nullptr);
    ~UsersDialog();

private slots:
    void on_pushButtonAdd_clicked();

    void on_pushButtonEdit_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::UsersDialog *ui;
    TableUsersModel *modelUsers;
private:
    void createModel();
    void createUI();
};

#endif // USERSDIALOG_H
