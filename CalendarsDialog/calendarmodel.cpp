#include "calendarmodel.h"
#include <QColor>
#include <QDate>
#include <QLocale>

CalendarModel::CalendarModel()
{

}

QVariant CalendarModel::data(const QModelIndex &idx, int role) const
{
    switch (role) {
    case Qt::BackgroundColorRole:
        if(QSqlTableModel::data(this->index(idx.row(), 3)).toInt() == 0){
            return QColor("#F08080");
        } else
            return QColor("#90EE90");
    case Qt::DisplayRole:
        switch (idx.column()) {
        case 2:
            return QSqlTableModel::data(idx).toString()+", "+QSqlTableModel::data(this->index(idx.row(), 2)).toDate().toString("ddd");
        case 3:
            if(QSqlTableModel::data(this->index(idx.row(), 3)).toInt() == 0)
                return "Выходной";
            else
                return "Рабочий";
        default:
            return QSqlTableModel::data(idx);
        }
    default:
        break;
    }
    return QVariant();
}
