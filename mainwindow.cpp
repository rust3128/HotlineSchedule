#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "UsersDialog/usersdialog.h"
#include "CalendarsDialog/calendarsdialog.h"

MainWindow::MainWindow(bool isConnect, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    m_isConnectDB=isConnect;
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
    calDld->exec();
}
