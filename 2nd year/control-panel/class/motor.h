#pragma once

#include <QObject>
#include "udpconnector.h"

class Motor : public QObject
{
    Q_OBJECT
public:
    Motor();
    ~Motor();

protected:

private:
    double          rpm;
    int             originalValue;
    UdpConnector*   connector;

signals:
    void newOriginalValue(int value);

public slots:    
    void getOriginalData(QVector<int> value);
};
