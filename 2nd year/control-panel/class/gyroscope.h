#pragma once

#include <QObject>
#include "tcpconnector.h"

class Gyroscope : public QObject
{
    Q_OBJECT
public:
    Gyroscope();
    ~Gyroscope();

protected:

private:
    QVector<int>    originalData;
    TcpConnector*   connector;

signals:
    void newOriginalData(QVector<int>);

public slots:
    void getOriginalData(QVector<int> xyz);
    
};
