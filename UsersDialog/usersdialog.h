#ifndef USERSDIALOG_H
#define USERSDIALOG_H

#include <QDialog>
#include <QSqlRelationalTableModel>
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
        void onCheckBoxChecked(bool isChecked);
        void on_pushButtonAdd_clicked();

private:
    Ui::UsersDialog *ui;
    QSqlRelationalTableModel *modelUsers;
private:
    void createModel();
    void createUI();

};

#endif // USERSDIALOG_H
