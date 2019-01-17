#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "OptionsDialog/optionsdialog.h"

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>

struct selectedDay
{
    QDate dat;
    int calendarID;
    int iswork;
};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(bool isConnect, QWidget *parent = nullptr);
    ~MainWindow();
    void show();
private slots:
    void on_actionOptions_triggered();
    void on_actionUsers_triggered();
    void on_calendarWidget_selectionChanged();
    void on_actionCalendar_triggered();
    void on_comboBoxNight_activated(int idx);

    void on_pushButtonNew_clicked();

private:
    Ui::MainWindow *ui;
    bool m_isConnectDB;
    selectedDay selDay;
    QSqlQueryModel *modelUsers;
    int userIDDay;
    int sheduleIDDay;
    int userIDNight;
    int SheduleIDNight;
private:
    void showOptionsDlg();
    void createModels();
    void createUI();
    void setCurrentWorker();
};

#endif // MAINWINDOW_H
