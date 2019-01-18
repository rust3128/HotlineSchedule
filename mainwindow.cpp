#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "LoggingCategories/loggingcategories.h"
#include "UsersDialog/usersdialog.h"
#include "CalendarsDialog/calendarsdialog.h"
#include <QTextCharFormat>

MainWindow::MainWindow(bool isConnect, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    m_isConnectDB=isConnect;

//    QTextCharFormat format;
//    QBrush brush;
//    QColor color;

//    int r=200,g=145,b=234,a=120;
//    color.setRgb(r,g,b,a);;
//    brush.setColor(color);
//    format.setBackground(brush);

//    QDate date = QDate::currentDate();
//    ui->calendarWidget->setDateTextFormat(date,format);

    createModels();
    createUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show()
{
    QMainWindow::show();
    if(!m_isConnectDB){
        showOptionsDlg();
    }

}

void MainWindow::showOptionsDlg()
{
    OptionsDialog *optionsDlg = new OptionsDialog(m_isConnectDB);
    optionsDlg->move(this->geometry().center().x() - optionsDlg->geometry().center().x(), this->geometry().center().y() - optionsDlg->geometry().center().y());
    optionsDlg->exec();
    if(optionsDlg->isOptionChanged())
        this->close();
}

void MainWindow::createModels()
{
    modelUsers = new QSqlQueryModel();
    modelUsers->setQuery("SELECT userid, fio FROM users WHERE isactive = 1");


}

void MainWindow::createUI()
{
//    ui->calendarWidget->setSelectedDate(QDate::currentDate());
    ui->pushButtonNew->setEnabled(false);

    ui->comboBoxDay->setModel(modelUsers);
    ui->comboBoxDay->setModelColumn(1);
    ui->comboBoxNight->setModel(modelUsers);
    ui->comboBoxNight->setModelColumn(1);
    on_calendarWidget_selectionChanged();
}



void MainWindow::on_actionOptions_triggered()
{
    showOptionsDlg();
}

void MainWindow::on_actionUsers_triggered()
{
    UsersDialog *usersDlg = new UsersDialog();
    usersDlg->move(this->geometry().center().x() - usersDlg->geometry().center().x(), this->geometry().center().y() - usersDlg->geometry().center().y());
    usersDlg->exec();
}

void MainWindow::on_calendarWidget_selectionChanged()
{
    selDay.dat = ui->calendarWidget->selectedDate();
    ui->labelCurrendDay->setText(selDay.dat.toString("dd MMMM yyyy, dddd"));

    QSqlQuery q;
    q.prepare("select calendarID, iswork from calendar where date = :dat");
    q.bindValue(":dat",selDay.dat.toString("yyyy-MM-dd"));
    if(!q.exec()) qCritical(logCritical()) << "Не удалось получить данные из календаря" << q.lastError().text();
    q.next();
    selDay.calendarID=q.value(0).toInt();
    selDay.iswork=q.value(1).toInt();
    if(selDay.iswork==1){
        ui->labelDay->hide();
        ui->comboBoxDay->hide();
    } else {
        ui->labelDay->show();
        ui->comboBoxDay->show();
    }


    setCurrentWorker();
}

void MainWindow::setCurrentWorker()
{
    QSqlQuery q;
    ui->comboBoxDay->setCurrentIndex(-1);
    ui->comboBoxNight->setCurrentIndex(-1);
    sheduleIDDay = sheduleIDNight = userIDDay = 0 ;
    q.prepare("select userID, worktypeID, sheID from shedule where calendarID=:id");
    q.bindValue(":id", selDay.calendarID);
    q.exec();
    while(q.next()){
        switch (q.value(1).toInt()) {
        case 1:
            userIDNight = q.value(0).toInt();
            sheduleIDNight=q.value(2).toInt();
            ui->comboBoxNight->setCurrentIndex(userIDNight-1);
            break;
        case 2:
            userIDDay = q.value(0).toInt();
            sheduleIDDay = q.value(2).toInt();
            ui->comboBoxDay->setCurrentIndex(userIDDay-1);
            break;
        default:
            break;
        }
    }


}


void MainWindow::on_actionCalendar_triggered()
{
    CalendarsDialog *calDld = new CalendarsDialog();
    calDld->move(this->geometry().center().x() - calDld->geometry().center().x(), this->geometry().center().y() - calDld->geometry().center().y() );
    calDld->exec();
}

void MainWindow::on_comboBoxNight_activated(int idx)
{
    int userID = modelUsers->data(modelUsers->index(idx,0)).toInt();

    if(userID != userIDNight) {
        userIDNight = userID;
        ui->pushButtonNew->setEnabled(true);
    }
}

void MainWindow::on_comboBoxDay_activated(int idx)
{
    int userID = modelUsers->data(modelUsers->index(idx,0)).toInt();

    if(userID != userIDDay) {
        userIDDay = userID;
        ui->pushButtonNew->setEnabled(true);
    }
}


void MainWindow::on_pushButtonNew_clicked()
{
    QSqlQuery q;

    qInfo(logInfo()) << "sheduleIDNight" << sheduleIDNight << "selDay.calendarID" << selDay.calendarID << "userIDNight" << selDay.calendarID;

    q.prepare("call upset_shedule(:m_sheID, :m_calendarID, :m_userID, :m_worktypeID)");
    q.bindValue(":m_sheID", sheduleIDNight);
    q.bindValue(":m_calendarID", selDay.calendarID);
    q.bindValue(":m_userID", userIDNight);
    q.bindValue(":m_worktypeID", 1);
    if(!q.exec()) qInfo(logInfo()) << "Не удалось обновить ночного дежурного" << q.lastError().text();
    q.finish();
    if(ui->comboBoxDay->isVisible() && (userIDDay > 0) ) {
        qInfo(logInfo()) << "ui->comboBoxDay->currentIndex()" << ui->comboBoxDay->currentIndex();
        q.prepare("call upset_shedule(:m_sheID, :m_calendarID, :m_userID, :m_worktypeID)");
        q.bindValue(":m_sheID", sheduleIDDay);
        q.bindValue(":m_calendarID", selDay.calendarID);
        q.bindValue(":m_userID", userIDDay);
        q.bindValue(":m_worktypeID", 2);
        if(!q.exec()) qInfo(logInfo()) << "Не удалось обновить дневного дежурного" << q.lastError().text();
        q.finish();
    }




    ui->calendarWidget->update();
    ui->calendarWidget->repaint();
    ui->pushButtonNew->setEnabled(false);

}

