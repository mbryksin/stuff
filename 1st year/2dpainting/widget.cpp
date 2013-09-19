#include <QtGui>
#include "widget.h"
#include "helper.h"

Widget::Widget(Helper *helper, QWidget *parent)
    : QWidget(parent), helper(helper)
{
    f = 1;
    elapsed = 0;
    setFixedSize(200, 200);
}

void Widget::animate()
{
    if ((elapsed < 15000) && (f))
    {
        elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval());
    } else
        f = 0;

    if ((!f) && (elapsed > -15000))
    {
        elapsed = (elapsed - qobject_cast<QTimer*>(sender())->interval());
    } else
        f = 1;
    repaint();
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event, elapsed);
    painter.end();
}
