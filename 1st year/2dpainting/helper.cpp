#include <QtGui>
#include "helper.h"
#define pi 3.14159265

Helper::Helper(QString text)
{
    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));


    widgetText = text;
    background = QBrush(QColor(64, 32, 64));
    circleBrush = QBrush(Qt::gray);
    circlePen = QPen(Qt::black);
    circlePen.setWidth(1);
    textPen = QPen(Qt::white);
    textFont.setPixelSize(15);

    if (!strcmp("Roll", widgetText.toLatin1().data()))
    {
        pixmap = QPixmap("img/YoZ.png");
    } else if (!strcmp("Pitch", widgetText.toLatin1().data()))
    {
        pixmap = QPixmap("img/XoZ.png");
    } else if (!strcmp("Yaw", widgetText.toLatin1().data()))
    {
        pixmap = QPixmap("img/XoY.png");
    }
}

void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    qreal alpha = elapsed * 0.030;
//pseudorandom alpha
    if (!strcmp("Pitch", widgetText.toLatin1().data()))
    {
        alpha = (4*(alpha*5 + 12.5))/172.3 +10.2;
    } else if (!strcmp("Roll", widgetText.toLatin1().data()))
    {
        alpha = (10*(alpha*10 + 135))/602.4 - 12.83;
    } else if (!strcmp("Yaw", widgetText.toLatin1().data() ))
    {
        alpha = (7*(alpha*19 + 78.34))/893.7;
    }

    //TO DO <-360 BAG

    if (alpha > 361)
        alpha -= 360;
    if (alpha < -361)
        alpha += 360;
//-------
    painter->fillRect(event->rect(), background);
    painter->translate(100, 100);

    painter->save();
//angle
    painter->setBrush(circleBrush);
    painter->setPen(circlePen);
    QRectF rectangle(-100.0, -100.0, 200.0, 200.0);
    int startAngle = 0 * 16;
    int spanAngle = -alpha * 16;
    painter->drawPie(rectangle, startAngle, spanAngle);
//-------
//axis
    painter->drawLine(0.0, 0.0,
                      200*cos(alpha*pi/180), 200*sin(alpha*pi/180));
    painter->drawLine(0.0, 0.0,
                      200*cos((90+alpha)*pi/180), 200*sin((90+alpha)*pi/180));
    painter->drawLine(0.0, 0.0,
                      -200*cos(alpha*pi/180), -200*sin(alpha*pi/180));
    painter->drawLine(0.0, 0.0,
                      -200*cos((90+alpha)*pi/180), -200*sin((90+alpha)*pi/180));
//-------
//pixmap
    painter->rotate(alpha);
    if (!strcmp("Pitch", widgetText.toLatin1().data()))
    {
         painter->drawPixmap(-95, -38, 190, 65, pixmap);
    } else if (!strcmp("Roll", widgetText.toLatin1().data()))
    {
        painter->drawPixmap(-95, -44, 200, 75, pixmap);
    } else if (!strcmp("Yaw", widgetText.toLatin1().data() ))
    {
        painter->drawPixmap(-95, -88, 190, 180, pixmap);
    }
//-------
    painter->restore();

//static picture
    painter->setPen(textPen);
    painter->setFont(textFont);
    painter->drawLine(0, -100, 0, 100);
    painter->drawLine(-100, 0, 100, 0);
    QString buf;

    int degree = -static_cast<int>(round(static_cast<double>(alpha))) % 360;
    buf.sprintf("%d", degree);
    painter->drawText(-99, -100, 100, 25, Qt::AlignLeft, widgetText);
    painter->drawText(0, -100, 100, 25, Qt::AlignRight, buf);
//
}
