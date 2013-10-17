#pragma once

#include <QObject>
#include <QTcpSocket>

class TcpConnector : public QObject
{
    Q_OBJECT
public:
    explicit TcpConnector(QString ipname, int portname, QObject *parent = 0);
    ~TcpConnector();

protected:
    QVector<int> parseMessage(QString message);
    QString getTcpLog();

private:
    QString     ip;
    quint16     port;
    quint16     nextBlockSize;
    QTcpSocket  socket;

signals:
    void dataReady(QVector<int>);

public slots:
    void setConnection();
    void setDisconnection();

private slots:
    void readData();
};
