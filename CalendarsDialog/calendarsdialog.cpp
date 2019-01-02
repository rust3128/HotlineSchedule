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
    modelCalendar = new CalendarModel();
    modelMonth->setQuery("select @i := @i +1 AS id, monthID, DATE_FORMAT(date, '%b %Y') as dat from calendar, (select @i:=0) as z  "
                         "group by monthID "
                         "order by monthID DESC");
    modelCalendar->setTable("calendar");
    modelCalendar->setHeaderData(2,Qt::Horizontal,"Дата");
    modelCalendar->setHeaderData(3,Qt::Horizontal,"Тип");
    modelCalendar->setFilter("monthID=-1");
    modelCalendar->select();

}

void CalendarsDialog::createUI()
{
    ui->comboBox->setModel(modelMonth);
    ui->comboBox->setModelColumn(2);
    ui->comboBox->setCurrentIndex(-1);

    ui->tableView->setModel(modelCalendar);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(1);
    ui->tableView->verticalHeader()->hide();
}

void CalendarsDialog::on_comboBox_activated(int idx)
{
    int monthID = modelMonth->data(modelMonth->index(idx,1)).toInt();
    strFilter = QString("monthID=%1")
            .arg(monthID);
    modelCalendar->setFilter(strFilter);
    modelCalendar->select();

}

void CalendarsDialog::on_tableView_doubleClicked(const QModelIndex &idx)
{
    QSqlQuery q;
    int dd;
    QString dayStatus = modelCalendar->data(modelCalendar->index(idx.row(),3),Qt::DisplayRole).toString();
    int dayID = modelCalendar->data(modelCalendar->index(idx.row(),0),Qt::DisplayRole).toInt();
    qInfo(logInfo()) << "dayID" << dayID  << "DayStatus" << dayStatus;
    if(dayStatus == "Рабочий")
        dd = 0;
    else
        dd = 1;

    q.prepare("UPDATE calendar SET iswork = :dayStat WHERE calendarID=:dayID");
    q.bindValue(":dayStat", dd);
    q.bindValue(":dayID", dayID);

    if(!q.exec()) qCritical(logCritical()) << "Не возможно установить статус дня" << q.lastError().text();

    modelCalendar->select();

}
