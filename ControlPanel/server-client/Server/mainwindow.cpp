#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost, 7755);
    connect(ui->pushButton, SIGNAL(pressed()), this, SLOT(send()));
    qDebug("Created");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::send()
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << qint64(0);
    out << qint8(0);
    qint32 x = rand() % 10;
    out << x;
    qDebug("sended: %d", x);
    out.device()->seek(qint64(0));
    out << qint64(data.size() - sizeof(qint64));
    udpSocket->writeDatagram(data, QHostAddress::Broadcast, 7755);
}
