#ifndef TABLEUSERSMODEL_H
#define TABLEUSERSMODEL_H

#include <QObject>
#include <QSqlTableModel>

class TableUsersModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit TableUsersModel(QObject *parent = nullptr);

signals:

public slots:

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &idx, int role) const;
};

#endif // TABLEUSERSMODEL_H
