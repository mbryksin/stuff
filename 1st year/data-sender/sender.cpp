#include "sender.h"
#include "ui_sender.h"
#include <QDebug>
#include "math.h"
#include <QTimer>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

Sender::Sender(int phase, int nPort, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sender),
    m_tcpSocket(new QTcpSocket(this)),
    m_port(nPort),
    m_phase(phase)
{
    ui->setupUi(this);
    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(slotConnected()));

    connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,         SLOT(slotError(QAbstractSocket::SocketError)));

    connect(ui->button, SIGNAL(clicked()), SLOT(setConnection()));

    connect(this, SIGNAL(dataReady(float,double)), this, SLOT(slotSendToServer(float,double)));
}

void Sender::setConnection()
{
    m_tcpSocket->connectToHost(QHostAddress::Any, m_port);
}

void Sender::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(m_tcpSocket->errorString())
                    );
    qDebug(strError.toLatin1());
}


void Sender::slotSendToServer(float value, double key)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << quint16(0) << value << key;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    m_tcpSocket->write(arrBlock);
    //qDebug("sent: %g %g!", value, key);
}

void Sender::slotConnected()
{
    qDebug("Received the connected() signal");

    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

void Sender::realtimeDataSlot()
{
    // calculate new data:
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    static double lastPointKey = 0;

    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {

        double value = sin(key*1.6+cos(key*1.7+m_phase)*2+m_phase)*10 + sin(key*1.2+0.56+m_phase)*20 + 26;
        // add data to lines:
        emit dataReady(value, key);
        lastPointKey = key;
    }
}


Sender::~Sender()
{
    delete m_tcpSocket;
    delete ui;
}
