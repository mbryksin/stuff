#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QTcpSocket>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void sendFactor();
    void connectToIp();
private:
    QLineEdit lineEdit;
    QLineEdit lineIp;
    QPushButton sendButton;
    QPushButton connectButton;
    QGridLayout layout;
    QTcpSocket infoSocket;
    QString ip;
};

#endif // WIDGET_H
