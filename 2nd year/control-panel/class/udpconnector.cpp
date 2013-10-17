#include "udpconnector.h"

UdpConnector::UdpConnector(int portname, QObject *parent) :
    QObject(parent),
    port(portname)
{
    connect(&socket, SIGNAL(readyRead()), this, SLOT(readData()));
}

UdpConnector::~UdpConnector()
{
    setDisconnection();
}

void UdpConnector::setConnection()
{
    socket.bind(QHostAddress::Broadcast, port);
    if (socket.state() == QUdpSocket::UnconnectedState)
    {
        qDebug() << "UdpConnector can't connect to Broadcast port" << port;
    }
}

void UdpConnector::setDisconnection()
{
    socket.abort();
}

void UdpConnector::readData()
{
    QVector<int> vector;
    while( socket.hasPendingDatagrams() )
    {
        QByteArray buffer( socket.pendingDatagramSize(), 0 );
        socket.readDatagram( buffer.data(), buffer.size() );
        QDataStream stream( buffer );
        stream.setVersion( QDataStream::Qt_4_0 );
        int res;
        stream >> res;
        vector << res;
    }
    emit dataReady(vector);
}
