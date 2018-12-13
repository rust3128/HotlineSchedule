#include "tableusersmodel.h"
#include <QColor>
TableUsersModel::TableUsersModel(QObject *parent) : QSqlTableModel (parent)
{

}

QVariant TableUsersModel::data(const QModelIndex &idx, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        switch (idx.column()) {
        case 4:
            if(QSqlTableModel::data(this->index(idx.row(), 4)).toInt()==1){
                return "Да";
            } else {
                return "Нет";
            }
            break;
        default:
            return QSqlTableModel::data(idx);
            break;
        }
        break;
    case Qt::BackgroundColorRole:
        if(!QSqlTableModel::data(this->index(idx.row(), 4)).toBool()){
            return QColor(Qt::darkGray);
        }
        break;
    case Qt::TextAlignmentRole:
        if(idx.column() == 4) return Qt::AlignCenter;
        break;
    default:
        break;
    }


    return QVariant();
}
