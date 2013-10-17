#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      ip("192.168.0.124")
{
    layout.addWidget(&lineIp, 0, 0);
    layout.addWidget(&connectButton, 0, 1);
    layout.addWidget(&lineEdit, 1, 0);
    layout.addWidget(&sendButton, 1, 1);
    setLayout(&layout);

    sendButton.setText("send");
    lineIp.setText("192.168.0.124");
    lineEdit.setText("K_F[0] K_F[1] K_F[2] K_F[3] K_I");
    connectButton.setText("connect");
    connect(&connectButton, SIGNAL(clicked()), this, SLOT(connectToIp()));
    connect(&sendButton, SIGNAL(clicked()), this, SLOT(sendFactor()));
}

Widget::~Widget()
{
    
}

void Widget::connectToIp()
{
    infoSocket.abort();
    ip = lineIp.text().toAscii().data();
    infoSocket.connectToHost(ip, 1234);
}

void Widget::sendFactor()
{
    if (infoSocket.state() != QTcpSocket::ConnectedState)
    {
        qDebug() << "no connection";
        return;
    }
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << lineEdit.text();
    infoSocket.write(datagram);
}
