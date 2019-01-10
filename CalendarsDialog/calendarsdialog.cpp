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
    yearNew = ui->dateEdit->date().year();

    connect(this,&CalendarsDialog::signalsMonthIDCorrect,this,&CalendarsDialog::slotCheckMonthID);
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

    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setMinimumDate(QDate(QDate::currentDate().year()-1,1,1));
    ui->comboBoxNewMonth->setCurrentIndex(-1);
}

void CalendarsDialog::on_comboBox_activated(int idx)
{


    int monthID = modelMonth->data(modelMonth->index(idx,1)).toInt();
    strFilter = QString("monthID=%1")
            .arg(monthID);
    modelCalendar->setFilter(strFilter);
    modelCalendar->select();

    qInfo(logInfo()) << "First day" << modelCalendar->index(0,2).data().toString();

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

void CalendarsDialog::on_pushButtonClose_clicked()
{
    this->reject();
}



void CalendarsDialog::on_comboBoxNewMonth_activated(int idx)
{
    monthNew = idx+1;
    emit signalsMonthIDCorrect(yearNew*100+monthNew);

}

void CalendarsDialog::slotCheckMonthID(int ID)
{
    QSqlQuery q;
    q.prepare("SELECT EXISTS (SELECT * FROM calendar WHERE monthID = :id )");
    q.bindValue(":id",ID);
    if(!q.exec()) qCritical(logCritical()) << Q_FUNC_INFO  << "Невозможно получить ID месяца" << q.lastError().text();
    q.next();
    if(q.value(0).toInt()==1) {
        ui->pushButtonNewCalendar->setDisabled(true);
        ui->pushButtonNewCalendar->setText("Календарь существует");
    } else {
        ui->pushButtonNewCalendar->setDisabled(false);
        ui->pushButtonNewCalendar->setText("Создать");
    }
}



void CalendarsDialog::on_dateEdit_userDateChanged(const QDate &date)
{
    yearNew = date.year();
    emit signalsMonthIDCorrect(yearNew*100+monthNew);
}

void CalendarsDialog::on_pushButtonNewCalendar_clicked()
{
    QSqlQuery q;
    q.prepare("call filling_the_calendar(:month,:year)");
    q.bindValue(":month", monthNew);
    q.bindValue(":year", yearNew);
    if(!q.exec()){
        qCritical(logCritical()) << Q_FUNC_INFO  << "Невозможно календарь." << q.lastError().text();
    }
    else {
        ui->pushButtonNewCalendar->setText("Календарь добавлен");
        ui->pushButtonNewCalendar->setEnabled(false);
    }

}
