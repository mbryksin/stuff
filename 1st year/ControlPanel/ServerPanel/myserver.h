#ifndef MYSERVER_H
#define MYSERVER_H

#include <QWidget>

#include <QTcpServer>
#include <QTcpSocket>
#include <QTextEdit>


class MyServer : public QWidget {
Q_OBJECT

public:
    MyServer(int nPort, QWidget* pwgt = 0);

public slots:
    virtual void slotNewConnection();
            void slotReadClient   ();

private:
    QTcpServer* m_ptcpServer;
    QTextEdit*  m_ptxt;
    quint16     m_nNextBlockSize;
};
#endif // MYSERVER_H
