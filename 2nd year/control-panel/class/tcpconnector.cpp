#include "tcpconnector.h"
#include <QStringList>

TcpConnector::TcpConnector(QString ipname, int portname, QObject *parent) :
    QObject(parent),
    ip(ipname),
    port(portname),
    nextBlockSize(0)
{
    connect(&socket, SIGNAL(readyRead()), this, SLOT(readData()));
}

TcpConnector::~TcpConnector()
{
    setDisconnection();
}

void TcpConnector::setConnection()
{
    socket.connectToHost(ip, port);
    if (socket.state() == QTcpSocket::UnconnectedState)
    {
        qDebug() << "TcpConnector can't connect to ip" << ip.toAscii().data() << "port" << port;
    }
}

void TcpConnector::setDisconnection()
{
    socket.abort();
}

void TcpConnector::readData()
{
    QString str = getTcpLog();
    QVector<int> args = parseMessage(str);
    emit dataReady(args);
}

QVector<int> TcpConnector::parseMessage(QString message)
{
    QVector<int> args;
    QStringList arguments = message.split(" ");
    foreach (QString arg, arguments)
    {
        args << arg.toInt();
    }
    return args;
}

QString TcpConnector::getTcpLog()
{
    QDataStream in(&socket);
    in.setVersion(QDataStream::Qt_4_2);
    QString text;
    for (;;)
    {
        if (!nextBlockSize)
        {
            if (socket.bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            in >> nextBlockSize;
        }
        if (socket.bytesAvailable() < nextBlockSize)
        {
            break;
        }
        in >> text;
        nextBlockSize = 0;
    }
    return text;
}
