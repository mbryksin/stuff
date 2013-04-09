#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any, 7755);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(read()));
    qDebug("Created");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::read()
{
    qDebug("Start reading");
    ui->label->setText("Number detected!");

    QByteArray datagram;
    datagram.resize(udpSocket->pendingDatagramSize());
    QHostAddress *address = new QHostAddress();
    udpSocket->readDatagram(datagram.data(), datagram.size(), address);

    QDataStream in(&datagram, QIODevice::ReadOnly);

    qint64 size = -1;
    if(in.device()->size() > sizeof(qint64))
    {
      in >> size;
    } else return;
    if (in.device()->size() - sizeof(qint64) < size) return;

    qint8 type = 0;
    in >> type;
    qint32 number;
    in >> number;
    qDebug("num = %d", number);
}
