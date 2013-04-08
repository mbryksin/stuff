#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    port(4444)
{
    ui->setupUi(this);
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, port);
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
    qDebug("Created");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::read()
{
    qDebug("Start reading");
//    QByteArray datagram;
//    datagram.resize(socket->pendingDatagramSize());
//    QHostAddress *address = new QHostAddress();
//    socket->readDatagram(datagram.data(), datagram.size(), address);

//    QDataStream in(&datagram, QIODevice::ReadOnly);
/*
    qint64 size = -1;
    if(in.device()->size() > sizeof(qint64))
    {
      in >> size;
    } else return;
    if (in.device()->size() - sizeof(qint64) < size) return;
*/
//    qint8 type = 0;
//    in >> type;
//    qint32 number;
//    in >> number;

//    qDebug("num = %d", number);
}

















/*

void send(QString str, qint8 type) {
  QByteArray data;
  QDataStream out(&data, QIODevice::WriteOnly);
  out << qint64(0);
  out << qint8(type);
  out << str;
  out.device()->seek(qint64(0));
  out << qint64(data.size() - sizeof(qint64));
  socket->writeDatagram(data, QHostAddress::Broadcast, _port);
}

void MainWindow::read() {
  QByteArray datagram;
  datagram.resize(socket->pendingDatagramSize());
  QHostAddress *address = new QHostAddress();
  socket->readDatagram(datagram.data(), datagram.size(), address);

  QDataStream in(&datagram, QIODevice::ReadOnly);

  qint64 size = -1;
  if(in.device()->size() > sizeof(qint64)) {
    in >> size;
  } else return;
  if (in.device()->size() - sizeof(qint64) < size) return;

  qint8 type = 0;
  in >> type;

  if (type == USUAL_MESSAGE) {
    QString str;
    in >> str;
    // код по перенаправке сообщения в классы выше //
  } else if (type == PERSON_ONLINE) {
    // Добавление пользователя с считанным QHostAddress //
  } else if (type == WHO_IS_ONLINE) {
    sending(nickname, qint8(PERSON_ONLINE));
  }
}

*/

