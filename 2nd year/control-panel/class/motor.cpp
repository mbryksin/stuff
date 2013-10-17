#include "motor.h"

Motor::Motor(QObject *parent) :
    QObject(parent)
{
    connector = new UdpConnector(4141);
    connect(connector, SIGNAL(dataReady(QVector<int>)), this, SLOT(getOriginalData(QVector<int>)));
}

Motor::~Motor()
{
    delete(connector);
}

void Motor::getOriginalData(QVector<int> value)
{
    originalValue = value[0];
    emit newOriginalData(originalValue);
}
