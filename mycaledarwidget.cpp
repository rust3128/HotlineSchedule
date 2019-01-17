#include <QPainter>
#include "mycalendarwidget.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

MyCalendarWidget::MyCalendarWidget(QWidget *parent)
    : QCalendarWidget (parent)
{
    m_currentDate = QDate::currentDate();
    m_outlinePen.setColor(Qt::red);

    m_transparentBrush.setColor(Qt::red);
    m_backgraund.setColor(Qt::green);
    QCalendarWidget::setMinimumDate(QDate(2018,10,01));



}

void MyCalendarWidget::setColor(QColor& color)
{
   m_outlinePen.setColor(color);
}

QColor MyCalendarWidget::getColor()
{
   return (m_outlinePen.color());
}

void MyCalendarWidget::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
    QCalendarWidget::paintCell(painter, rect, date);
    QSqlQuery q;
    QString strSQL, strMessage;
    int iswork;
    strSQL = QString("SELECT count(*), iswork FROM calendar WHERE date = '%1'")
            .arg(date.toString("yyyy-MM-dd"));
    if(!q.exec(strSQL)) qDebug() << "CalendarError" << q.lastError().text();
    q.next();
    iswork = q.value(1).toInt();
    if (q.value(0).toInt()==1)
    {
        q.finish();
        strMessage.clear();
        strSQL = QString("SELECT c.date, u.fio, w.worktypeID, c.iswork FROM shedule s "
                         "LEFT JOIN calendar c ON c.calendarID = s.calendarID "
                         "LEFT JOIN users u ON u.userid = s.userID "
                         "LEFT JOIN worktype w ON w.worktypeID = s.worktypeID "
                         "where c.date='%1' AND w.worktypeID IN (1,2)")
                .arg(date.toString("yyyy-MM-dd"));

        if(!q.exec(strSQL)) qDebug() << "Не возможно получить данные о дежурствах" << q.lastError().text();
        while (q.next()) {

            if(q.value(2).toInt()==2) strMessage="\nДень\n"+q.value(1).toString();
            if(q.value(2).toInt()==1) strMessage=strMessage+"\nНочь\n"+q.value(1).toString();
        }

        if(iswork == 0){
            painter->save();
            painter->setBrush(QColor("#CD5C5C"));
            painter->drawRect(rect);
            painter->drawText(rect, Qt::AlignCenter, QString::number(date.day())+strMessage);
            painter->restore();
        }  else {
            painter->save();
            painter->setBrush(QColor("#ADFF2F"));
            painter->drawRect(rect);
            painter->drawText(rect, Qt::AlignCenter, QString::number(date.day())+strMessage);
            painter->restore();
        }


    }


}
