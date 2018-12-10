#include "usersdialog.h"
#include "ui_usersdialog.h"
#include <QSqlRelationalDelegate>

UsersDialog::UsersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsersDialog)
{
    ui->setupUi(this);

    createModel();
    createUI();
}

UsersDialog::~UsersDialog()
{
    delete ui;
}

void UsersDialog::createModel()
{
    modelUsers = new QSqlRelationalTableModel();
    modelUsers->setTable("users");
    modelUsers->setRelation(8, QSqlRelation("userrole","role_ID","rolename"));
    modelUsers->select();

}

void UsersDialog::createUI()
{
    ui->tableView->setModel(modelUsers);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

    ui->tableView->verticalHeader()->hide();
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnsToContents();

}
