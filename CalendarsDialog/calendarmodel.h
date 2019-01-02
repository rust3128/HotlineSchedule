#ifndef CALENDARMODEL_H
#define CALENDARMODEL_H

#include <QObject>
#include <QSqlTableModel>

class CalendarModel : public QSqlTableModel
{
public:
    CalendarModel();

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &idx, int role) const;
};

#endif // CALENDARMODEL_H
