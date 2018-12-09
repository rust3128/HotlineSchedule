#include "optionsdialog.h"
#include "ui_optionsdialog.h"

OptionsDialog::OptionsDialog(bool isConnect, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    if(isConnect) {
        ui->tabWidget->setCurrentIndex(1);
    }
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}
