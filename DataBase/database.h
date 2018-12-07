#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    bool connectToDatabase();

signals:

public slots:
private:
    QSqlDatabase db;
};

#endif // DATABASE_H
