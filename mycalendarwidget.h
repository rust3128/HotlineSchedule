#ifndef MYCALENDARWIDGET_H
#define MYCALENDARWIDGET_H

#include <QObject>
#include <QCalendarWidget>
#include <QDate>
#include <QPen>
#include <QBrush>
 

class MyCalendarWidget : public QCalendarWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ getColor WRITE setColor)
    
public:
    MyCalendarWidget(QWidget *parent = nullptr);
    
    void setColor(QColor& color);
    QColor getColor();
     
private:
   QDate m_currentDate;
   QPen m_outlinePen;
   QBrush m_transparentBrush;
   QBrush m_backgraund;
   
   // QCalendarWidget interface
protected:
   virtual void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const;
};

#endif // MYCALENDARWIDGET_H
