#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost, 7755);
    //connect(udpSocket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(ui->pushButton, SIGNAL(ui->pushButton->isChecked()), this, SLOT(send()));
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
//    out << qint64(0);
//    out << qint8(type);
    out << "aaa";
    out.device()->seek(qint64(0));
    out << qint64(data.size() - sizeof(qint64));
    udpSocket->writeDatagram(data, QHostAddress::Broadcast, 7755);
}
