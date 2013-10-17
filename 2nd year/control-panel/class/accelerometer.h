#pragma once

#include <QObject>
#include "tcpconnector.h"

class Accelerometer : public QObject
{
    Q_OBJECT
public:
    Accelerometer();
    ~Accelerometer();

protected:

private:
    QVector<int>    originalData;
    TcpConnector*   connector;

signals:
    void newOriginalData(QVector<int>);

public slots:
    void getOriginalData(QVector<int> xyz);

};
