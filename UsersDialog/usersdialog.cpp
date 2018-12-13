#include "usersdialog.h"
#include "ui_usersdialog.h"
#include "edituserdialog.h"

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
    modelUsers = new TableUsersModel();
    modelUsers->setTable("users");
    modelUsers->select();
    modelUsers->setHeaderData(1,Qt::Horizontal,"Логин");
    modelUsers->setHeaderData(2,Qt::Horizontal,"Пароль");
    modelUsers->setHeaderData(3,Qt::Horizontal,"Ф.И.О.");
    modelUsers->setHeaderData(4,Qt::Horizontal,"Активен");
}

void UsersDialog::createUI()
{
    ui->tableView->setModel(modelUsers);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->hideColumn(2);
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->verticalHeader()->setDefaultSectionSize(ui->tableView->verticalHeader()->minimumSectionSize());
}

void UsersDialog::on_pushButtonAdd_clicked()
{
    EditUserDialog *edUserDlg = new EditUserDialog();
    edUserDlg->exec();
}

void UsersDialog::on_pushButtonEdit_clicked()
{
    int row = ui->tableView->currentIndex().row();
    if(row>=0){
        EditUserDialog *edUserDlg = new EditUserDialog(row);
        edUserDlg->exec();
        if(edUserDlg->Accepted){
            modelUsers->select();
        }
    }
}

void UsersDialog::on_pushButtonClose_clicked()
{
    this->reject();
}
