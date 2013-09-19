#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTcpSocket>

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void sendFactor();

private:
    QLineEdit lineEdit;
    QPushButton pushButton;
    QHBoxLayout layout;
    QTcpSocket infoSocket;
};

#endif // WIDGET_H
