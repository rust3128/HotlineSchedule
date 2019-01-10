#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    ui->label->setText(ui->calendarWidget->selectedDate().toString("dd MMMM yyyy, dddd"));
}

void MainWindow::on_actionCalendar_triggered()
{
    CalendarsDialog *calDld = new CalendarsDialog();
    calDld->move(this->geometry().center().x() - calDld->geometry().center().x(), this->geometry().center().y() - calDld->geometry().center().y() );
    calDld->exec();
}
