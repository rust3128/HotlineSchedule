#include "database.h"
#include "LoggingCategories/loggingcategories.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSettings>
#include <QFile>

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

bool DataBase::connectToDatabase()
{

    QSettings settings("HotlineSchedule.cfg", QSettings::IniFormat);
    QFile cfgfile("HotlineDesktop.cfg");
    if (!cfgfile.exists()){

        return false;
    }


    db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("10.28.8.78");
    db.setDatabaseName("glsheduler");
    db.setUserName("htuser");
    db.setPassword("SecretPassword");


    if(!db.open()) {
        qCritical(logCritical()) <<  "Не возможно подключиться к базе данных." << endl << "Причина:" << db.lastError().text();
        QMessageBox::critical(nullptr, QObject::tr("Не могу открыть базу данных"),
                              QString("Не могу установить соединение с базой данных\nПричина: %1\n Проверьте настройки подключения.").arg(db.lastError().text()),
                              QMessageBox::Cancel);
        return false;
    }
    return true;
}
