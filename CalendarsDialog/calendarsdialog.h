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

private slots:
    void on_comboBox_activated(int index);

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::CalendarsDialog *ui;
    CalendarModel *modelCalendar;
    QSqlQueryModel *modelMonth;
    QString strFilter;
private:
    void createModels();
    void createUI();
};

#endif // CALENDARSDIALOG_H
