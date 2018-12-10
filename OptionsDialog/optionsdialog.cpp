#include "optionsdialog.h"
#include "ui_optionsdialog.h"
#include "LoggingCategories/loggingcategories.h"

#include <QPushButton>


OptionsDialog::OptionsDialog(bool isConnect, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    m_connected = isConnect;
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);

    settings = new QSettings("HotlineSchedule.cfg", QSettings::IniFormat);

    connect(ui->LineEditDataBase,&QLineEdit::textChanged,this,&OptionsDialog::optionChanged);
    connect(ui->LineEditServer,&QLineEdit::textChanged,this,&OptionsDialog::optionChanged);
    connect(ui->LineEditUser,&QLineEdit::textChanged,this,&OptionsDialog::optionChanged);
    connect(ui->LineEditPassword,&QLineEdit::textChanged,this,&OptionsDialog::optionChanged);

    connect(ui->checkBoxShowUser,&QCheckBox::clicked,this,&OptionsDialog::optionChanged);
    if(!isConnect) {
        ui->tabWidget->setCurrentWidget(ui->tabConnections);
    } else {
        ui->tabWidget->setCurrentWidget(ui->tabGlobal);
        createUI();
    }


}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

bool OptionsDialog::isOptionChanged()
{
    return changedOptions;
}

void OptionsDialog::createUI()
{

    settings->beginGroup("MYSQL");
    ui->LineEditServer->setText(settings->value("HostName").toString());
    ui->LineEditDataBase->setText(settings->value("DataBase").toString());
    ui->LineEditUser->setText(settings->value("User").toString());
    ui->LineEditPassword->setText(settings->value("Password").toString());

    QSqlQuery q;
    if(!q.exec("SELECT option_id, value FROM options")) qInfo(logInfo()) << "Select Options" << q.lastError().text();
    while(q.next()){
        switch (q.value(0).toInt()) {
        case 1000:
            ui->checkBoxShowUser->setChecked(q.value(1).toBool());
//            qInfo(logInfo()) << "1000" << q.value(1).toBool();
            break;
        default:
            break;
        }
    }

}

void OptionsDialog::optionChanged()
{
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
}



void OptionsDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    switch (ui->buttonBox->standardButton(button)) {
    case QDialogButtonBox::Close:
        this->reject();
        break;
    case QDialogButtonBox::Apply:
        saveOptions();
        ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);
        changedOptions=true;
        break;
    default:
        break;
    }
}

void OptionsDialog::saveOptions()
{
    settings->beginGroup("MYSQL");
    settings->setValue("HostName",ui->LineEditServer->text().trimmed());
    settings->setValue("DataBase",ui->LineEditDataBase->text().trimmed());
    settings->setValue("User",ui->LineEditUser->text().trimmed());
    settings->setValue("Password",ui->LineEditPassword->text().trimmed());
    settings->endGroup();
    if(m_connected){
        QSqlQuery q;
        q.prepare("UPDATE options SET value = :value WHERE option_id = :optionID");
        q.bindValue(":value", (ui->checkBoxShowUser->isChecked()) ? "true" : "false");
        q.bindValue(":optionID", 1000);
        q.exec();
    }
}
