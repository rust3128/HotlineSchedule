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
    QString strSQL;
    strSQL = QString("SELECT count(*), iswork FROM calendar WHERE date = '%1'")
            .arg(date.toString("yyyy-MM-dd"));
    if(!q.exec(strSQL)) qDebug() << "CalendarError" << q.lastError().text();
    q.next();

    if (q.value(0).toInt()==1)
    {
//        QFont font=painter->font();
//        font.setPointSize(14);
//        painter->setFont(font);
        if(q.value(1).toInt()==0){
            painter->save();
            painter->setBrush(QColor("#CD5C5C"));
            painter->drawRect(rect);
            painter->drawText(rect, Qt::AlignCenter, QString::number(date.day())+"\nДень:\nМещеряков\nНочь\nАлфелди");
            painter->restore();
        }  else {
            painter->save();
            painter->setBrush(QColor("#ADFF2F"));
            painter->drawRect(rect);
            painter->drawText(rect, Qt::AlignCenter, QString::number(date.day())+"\nНочь:\nПанченко");
            painter->restore();
        }


    }


}
