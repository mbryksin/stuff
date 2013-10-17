#pragma once

#include <QObject>
#include <QUdpSocket>

class UdpConnector : public QObject
{
    Q_OBJECT
public:
    explicit UdpConnector(int portname, QObject *parent = 0);
    ~UdpConnector();
protected:

private:
    quint16      port;
    QUdpSocket   socket;

signals:
    void dataReady(QVector<int>);
    
public slots:
    void setConnection();
    void setDisconnection();

private slots:
    void readData();

};
