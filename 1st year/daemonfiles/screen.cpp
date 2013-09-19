#include "screen.h"

#include <QApplication>
#include "qdesktopwidget.h"

Screen::Screen(int port, QWidget *parent)
    : QWidget(parent),
      my_port(port),
      my_tcpServer(this),
      my_tcpSocket(),
      connectionIsNull(true)
{
    connect(&screenRefreshTimer, SIGNAL(timeout()), this, SLOT(makeScreenshot()));
}

void Screen::setConnection()
{
    if (!my_tcpServer.listen(QHostAddress::Any, my_port))
    {
        qDebug()<<"keys: unable to start the server:"<<my_tcpServer.errorString();
        my_tcpServer.close();
        return;
    }
    connect(&my_tcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
}

void Screen::tcpDisconnected()
{
    qDebug()<<"screen: disconnected";
    connectionIsNull = true;
    qDebug()<<"screen: waiting for connection...";
    my_tcpSocket->waitForConnected(-1);
}

void Screen::slotNewConnection()
{
    my_tcpSocket = my_tcpServer.nextPendingConnection();
    screenRefreshTimer.start(10); //1sec = 1000ms
    qDebug()<<"keys: set new connection";
    connectionIsNull = false;
    connect(my_tcpSocket, SIGNAL(disconnected()), my_tcpSocket, SLOT(deleteLater()));
    connect(my_tcpSocket, SIGNAL(disconnected()), this, SLOT(tcpDisconnected()));
}

void Screen::makeScreenshot()
{
    shotScreen();
}

void Screen::shotScreen()
{
    my_pixmap = QPixmap(); // clear image for low memory situations
                                // on embedded devices.
    my_pixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
    if (!connectionIsNull)
    {
        qDebug() << "send screen";
        QByteArray datagram;
        QDataStream out(&datagram, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_2);
        out << quint16(0) << my_pixmap;
        out.device()->seek(0);
        out << quint16(datagram.size() - sizeof(quint16));
        my_tcpSocket->write(datagram);
    }
}
