#-------------------------------------------------
#
# Project created by QtCreator 2018-11-26T14:23:48
#
#-------------------------------------------------

QT       += core gui sql concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HotlineSchedule
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    LoggingCategories/loggingcategories.cpp \
    OptionsDialog/optionsdialog.cpp \
    DataBase/database.cpp \
    UsersDialog/usersdialog.cpp \
    tableusersmodel.cpp \
    UsersDialog/edituserdialog.cpp \
    CalendarsDialog/calendarsdialog.cpp \
    CalendarsDialog/calendarmodel.cpp \
    mycaledarwidget.cpp

HEADERS += \
        mainwindow.h \
    LoggingCategories/loggingcategories.h \
    OptionsDialog/optionsdialog.h \
    DataBase/database.h \
    UsersDialog/usersdialog.h \
    tableusersmodel.h \
    UsersDialog/edituserdialog.h \
    CalendarsDialog/calendarsdialog.h \
    CalendarsDialog/calendarmodel.h \
    mycalendarwidget.h

FORMS += \
        mainwindow.ui \
    OptionsDialog/optionsdialog.ui \
    UsersDialog/usersdialog.ui \
    UsersDialog/edituserdialog.ui \
    CalendarsDialog/calendarsdialog.ui

DISTFILES += \
    SQL/database.sql \
    icons/bolezn.png \
    icons/day.png \
    icons/moon.png \
    icons/office.png \
    icons/otpusk.png \
    icons/sleep.png
