#ifndef PANEL_H
#define PANEL_H

#include <QtGui/QMainWindow>
#include <class/accelerometer.h>
#include <class/gyroscope.h>
#include <class/motor.h>

class Panel : public QMainWindow
{
    Q_OBJECT
    
public:
    Panel(QWidget *parent = 0);
    ~Panel();
protected:

private:
    Accelerometer accel;
    Gyroscope     gyro;
    Motor         motor;
};

#endif // PANEL_H
