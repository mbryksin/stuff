#include "widget.h"
#include <QDebug>

QString const& ip = "192.168.0.125";

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    layout.addWidget(&lineEdit);
    layout.addWidget(&pushButton);
    setLayout(&layout);

    pushButton.setText("send");
    connect(&pushButton, SIGNAL(clicked(bool)), this, SLOT(sendFactor()));

    infoSocket.connectToHost(ip, 1234);
}

Widget::~Widget()
{
    
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
    out << lineEdit.text().toLatin1().data();
    infoSocket.write(datagram);
}
