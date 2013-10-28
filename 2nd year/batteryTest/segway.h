#pragma once

#include <QObject>
#include <QTimer>
#include <trikControl/brick.h>

using namespace trikControl;

class Segway : public QObject
{
    Q_OBJECT
public:
    explicit Segway(QThread *guiThread);

protected:

signals:

private slots:
    void getInfo();
    void getRpm();
    void getVoltage();
    void print();

private:
    Brick brick;
    float mv;
    float rpm;
    int counter;
    QTimer mainTimer;
    QTimer batteryTimer;
    QTimer averageTimer;
    QTimer rpmTimer;
};
