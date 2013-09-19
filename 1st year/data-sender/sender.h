#ifndef SENDER_H
#define SENDER_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QtNetwork> //for qhostaddress

namespace Ui {
class Sender;
}

class Sender : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Sender(int phase, int nPort, QWidget *parent = 0);
    ~Sender();

signals:
    void dataReady(float data, double key);

private slots:
    void slotError(QAbstractSocket::SocketError);
    void slotSendToServer(float data, double key);
    void realtimeDataSlot();
    void slotConnected();
    void setConnection();

private:
    Ui::Sender *ui;
    QTcpSocket* m_tcpSocket;
    int m_port;
    float m_phase;
    quint16 m_nextBlockSize;
    QTimer dataTimer;
};

#endif // SENDER_H
