#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QtCore/QThread>

class MyThread : public QThread
{
    Q_OBJECT
private:
    int m_nValue;

public:
    MyThread();
    void run();
    ~MyThread();

signals:
    void finished();
    void currentValue(int);

public slots:
    void slotNextValue();
};

#endif // MYTHREAD_H
