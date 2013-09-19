#include <QtGui>
#include "widget.h"
#include "window.h"

Window::Window()
    : QWidget(),
      helperYaw("Yaw"),     //рыскание
      helperPitch("Pitch"), //тангаж
      helperRoll("Roll")    //крен
{
    Widget *widgetXoY = new Widget(&helperYaw, this);
    Widget *widgetXoZ = new Widget(&helperPitch, this);
    Widget *widgetYoZ = new Widget(&helperRoll, this);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(widgetXoY, 0, 0);
    layout->addWidget(widgetXoZ, 0, 1);
    layout->addWidget(widgetYoZ, 0, 2);
    setLayout(layout);

    QTimer *timer1 = new QTimer(this);
    QTimer *timer2 = new QTimer(this);
    QTimer *timer3 = new QTimer(this);
    connect(timer1, SIGNAL(timeout()), widgetXoY, SLOT(animate()));
    connect(timer2, SIGNAL(timeout()), widgetXoZ, SLOT(animate()));
    connect(timer3, SIGNAL(timeout()), widgetYoZ, SLOT(animate()));
    timer1->start(50);

    timer2->start(50);
    timer3->start(50);

    setWindowTitle(tr("2D Painting on Native and OpenGL Widgets"));
}
