#ifndef CALENDARSDIALOG_H
#define CALENDARSDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlError>


namespace Ui {
class CalendarsDialog;
}

class CalendarsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalendarsDialog(QWidget *parent = nullptr);
    ~CalendarsDialog();

private:
    Ui::CalendarsDialog *ui;
    QSqlTableModel *modelCalendar;
    QSqlQueryModel *modelMonth;
private:
    void createModels();
    void createUI();
};

#endif // CALENDARSDIALOG_H
