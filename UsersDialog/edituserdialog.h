#ifndef EDITUSERDIALOG_H
#define EDITUSERDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QMessageBox>

namespace Ui {
class EditUserDialog;
}

class EditUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditUserDialog(int row = -1, QWidget *parent = nullptr);
    ~EditUserDialog();


private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::EditUserDialog *ui;
    QSqlTableModel *model;
    QDataWidgetMapper *mapper;

private:
    void setupModel();
    void createUI();
};

#endif // EDITUSERDIALOG_H
