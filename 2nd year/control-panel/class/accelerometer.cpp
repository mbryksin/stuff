#include "accelerometer.h"

Accelerometer::Accelerometer()
{

    connector = new TcpConnector("192.168.0.0", 3232);
    connector->setConnection();

    connect(connector, SIGNAL(dataReady(QVector<int>)), this, SLOT(getOriginalData(QVector<int>)));
}

Accelerometer::~Accelerometer()
{
    delete connector;
}

void Accelerometer::getOriginalData(QVector<int> xyz)
{
    originalData = xyz;
    emit newOriginalData(originalData);
}
