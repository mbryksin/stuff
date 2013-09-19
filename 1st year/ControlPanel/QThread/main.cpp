#include <QtGui/QApplication>
#include <QLCDNumber>
#include "mythread.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QLCDNumber lcd;
    MyThread thread;

    QObject::connect(&thread, SIGNAL(currentValue(int)), &lcd, SLOT(display(int)));
    QObject::connect(&thread, SIGNAL(finished()), &app, SLOT(quit()));

    lcd.setSegmentStyle(QLCDNumber::Filled);
    lcd.display(10);
    lcd.resize(220, 90);
    lcd.show();
    thread.start();

    return app.exec();
}
