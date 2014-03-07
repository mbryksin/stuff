#include "segway.h"
#include <QTime>
#include <QDebug>

const double Pi = 3.1415926535897932384626433832795;
const int min = 60000;

Segway::Segway(QThread *guiThread) :
    brick(*guiThread),
    mv(0.0),
    rpm(0.0),
    counter(0)
{
    brick.stop();
    brick.encoder("3")->reset();
    brick.powerMotor("3")->setPower(100);
    brick.powerMotor("4")->setPower(100);
    connect(&mainTimer, SIGNAL(timeout()), this, SLOT(getInfo()));
    connect(&averageTimer, SIGNAL(timeout()), this, SLOT(getVoltage()));
    connect(&batteryTimer, SIGNAL(timeout()), this, SLOT(print()));
    mainTimer.start(5*min); //min
}

void Segway::getInfo()
{
    rpmTimer.singleShot(1000, this, SLOT(getRpm()));
    batteryTimer.singleShot(6000, this, SLOT(print()));
    averageTimer.start(100);

    brick.encoder("3")->reset();
}

void Segway::print()
{
    averageTimer.stop();
    QTime time = QTime::currentTime();
    mv = mv * 1000.0 / counter;
    qDebug("%s mV: %f, rmp: %f", time.toString().toAscii().data(), mv, rpm);
    mv = 0.0;
    counter = 0;
}

void Segway::getRpm()
{
    rpm = brick.encoder("3")->read() / (2.0 * Pi) * 60.0;
}

void Segway::getVoltage()
{
    counter++;
    mv += brick.battery()->readVoltage();
}
