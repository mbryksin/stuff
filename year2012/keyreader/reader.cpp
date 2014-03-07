#include "reader.h"
#include <QtGui>

#include <QDataStream>
#include <QDebug>
#include <QByteArray>

Reader::Reader()
{
    label = new QLabel;
    layout = new QHBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

void Reader::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Return:
        label->setText("Enter Pressed");
        break;
    case Qt::Key_F2:
        label->setText("F2");
        break;
    case Qt::Key_F3:
        label->setText("F3");
        break;
    case Qt::Key_F4:
        label->setText("F4");
        break;
    case Qt::Key_F5:
        label->setText("F5");
        break;
    case Qt::Key_F6:
        label->setText("F6");
        break;
    case Qt::Key_F7:
        label->setText("F7");
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}
