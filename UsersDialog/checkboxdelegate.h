#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QItemDelegate>

class CheckBoxDelegate : public QItemDelegate
{
    Q_OBJECT

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        QStyleOptionViewItem op(option);

        QPalette palette;
        op.palette.setColor(QPalette::Text, palette.color(QPalette::Base));
        op.palette.setColor(QPalette::Window, palette.color(QPalette::Base));
        op.palette.setColor(QPalette::Highlight, palette.color(QPalette::Base));
        op.palette.setColor(QPalette::HighlightedText, palette.color(QPalette::Base));

        QItemDelegate::paint(painter, op, index);
    }
};

#endif // CHECKBOXDELEGATE_H
