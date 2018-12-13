#include "edituserdialog.h"
#include "ui_edituserdialog.h"
#include "LoggingCategories/loggingcategories.h"
#include <QSqlQuery>
#include <QSqlError>

EditUserDialog::EditUserDialog(int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditUserDialog)
{
    ui->setupUi(this);

    setupModel();
    if(row == -1){
        model->insertRow(model->rowCount(QModelIndex()));
        mapper->toLast();
    } else {
        mapper->setCurrentModelIndex(model->index(row,0));
    }
}

EditUserDialog::~EditUserDialog()
{
    delete ui;
}

void EditUserDialog::setupModel()
{
    model = new QSqlTableModel();
    model->setTable("users");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    mapper = new QDataWidgetMapper();
    mapper->setModel(model);
    mapper->addMapping(ui->lineEditLogin,1);
    mapper->addMapping(ui->lineEditPass,2);
    mapper->addMapping(ui->lineEditFIO,3);
    mapper->addMapping(ui->checkBox,4,"checked");

    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

void EditUserDialog::createUI()
{

}

void EditUserDialog::on_pushButtonOK_clicked()
{
    mapper->submit();
    model->submitAll();
    this->accept();
}

void EditUserDialog::on_pushButtonClose_clicked()
{
    this->reject();
}
