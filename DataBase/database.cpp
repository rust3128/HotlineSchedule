#include "database.h"
#include "LoggingCategories/loggingcategories.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSettings>
#include <QFile>

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

bool DataBase::connectToDatabase()
{

    QSettings settings("HotlineSchedule.cfg", QSettings::IniFormat);
    QFile cfgfile("HotlineSchedule.cfg");
    if (!cfgfile.exists()){

        return false;
    }


    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");


    settings.beginGroup("MYSQL");
    db.setHostName(settings.value("HostName").toString());
    db.setDatabaseName(settings.value("DataBase").toString());
    db.setUserName(settings.value("User").toString());
    db.setPassword(settings.value("Password").toString());
    settings.endGroup();

    if(!db.open()) {
        qCritical(logCritical()) <<  "Не возможно подключиться к базе данных." << endl << "Причина:" << db.lastError().text();
        QMessageBox::critical(nullptr, QObject::tr("Не могу открыть базу данных"),
                              QString("Не могу установить соединение с базой данных\nПричина: %1\n Проверьте настройки подключения.").arg(db.lastError().text()),
                              QMessageBox::Cancel);
        return false;
    }
    QSqlQuery q;
    q.exec("SET lc_time_names = ru_RU");
    return true;
}
