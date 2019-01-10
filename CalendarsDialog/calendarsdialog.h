#ifndef CALENDARSDIALOG_H
#define CALENDARSDIALOG_H

#include "calendarmodel.h"

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlQuery>



namespace Ui {
class CalendarsDialog;
}

class CalendarsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalendarsDialog(QWidget *parent = nullptr);
    ~CalendarsDialog();
signals:
    void signalsMonthIDCorrect(int);
private slots:
    void on_comboBox_activated(int index);

    void on_tableView_doubleClicked(const QModelIndex &index);
    void on_pushButtonClose_clicked();
    void on_comboBoxNewMonth_activated(int index);
    void slotCheckMonthID(int ID);

    void on_dateEdit_userDateChanged(const QDate &date);

    void on_pushButtonNewCalendar_clicked();

private:
    Ui::CalendarsDialog *ui;
    CalendarModel *modelCalendar;
    QSqlQueryModel *modelMonth;
    QString strFilter;
    int monthNew;
    int yearNew;
private:
    void createModels();
    void createUI();
};

#endif // CALENDARSDIALOG_H
