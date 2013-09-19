#include "mythread.h"
#include "QTimer"

MyThread::MyThread()
    : m_nValue(10)
{
}

MyThread::~MyThread()
{
    
}

void MyThread::run()
{
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), SLOT(slotNextValue()));
    timer.start(1000);
    exec();
}

void MyThread::slotNextValue()
{
    emit currentValue(--m_nValue);
    if (!m_nValue)
    {
        emit finished();
    }
}
