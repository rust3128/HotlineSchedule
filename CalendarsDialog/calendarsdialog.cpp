#include "calendarsdialog.h"
#include "ui_calendarsdialog.h"
#include "LoggingCategories/loggingcategories.h"

CalendarsDialog::CalendarsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalendarsDialog)
{
    ui->setupUi(this);
    createModels();
    createUI();
}

CalendarsDialog::~CalendarsDialog()
{
    delete ui;
}

void CalendarsDialog::createModels()
{
    modelMonth = new QSqlQueryModel();
    modelCalendar = new QSqlTableModel();
    modelMonth->setQuery("select @i := @i +1 AS id, monthID, DATE_FORMAT(date, '%M %Y') as dat from calendar, (select @i:=0) as z  "
                         "group by monthID "
                         "order by monthID DESC");
    modelCalendar->setTable("calendar");
    modelCalendar->select();

}

void CalendarsDialog::createUI()
{
    ui->comboBox->setModel(modelMonth);
    ui->comboBox->setModelColumn(2);
    ui->comboBox->setCurrentIndex(-1);

    ui->tableView->setModel(modelCalendar);
}