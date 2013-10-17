#include "gyroscope.h"

Gyroscope::Gyroscope()
{
    connector = new TcpConnector("192.168.0.0", 1010);
    connect(connector, SIGNAL(dataReady(QVector<int>)), this, SLOT(getOriginalData(QVector<int>)));
    connector->setConnection();
}

Gyroscope::~Gyroscope()
{
    delete connector;
}

void Gyroscope::getOriginalData(QVector<int> xyz)
{
    originalData = xyz;
    emit newOriginalData(originalData);
}
