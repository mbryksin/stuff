#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include <QTimer>

class Screen : public QWidget
{
    Q_OBJECT
public:
    Screen(int port, QWidget *parent = 0);

signals:
    
public slots:
    virtual void slotNewConnection();
    void tcpDisconnected();
    void makeScreenshot();
    void setConnection();

protected:
    void shotScreen();

private:
    int         my_port;
    bool        connectionIsNull;
    QPixmap     my_pixmap;
    QTcpServer        my_tcpServer;
    QTcpSocket        *my_tcpSocket;
    QTimer      screenRefreshTimer;
};

#endif // SCREEN_H
