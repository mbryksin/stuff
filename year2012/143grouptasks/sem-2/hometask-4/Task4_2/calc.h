#pragma once

#include <QObject>

enum Operation {
    ADD = 0,
    SUB = 1,
    MUL = 2,
    DIV = 3
};

class Calc : public QObject
{
Q_OBJECT

public:
    Calc();
    void calculate();

public slots:
    void changeValue1(int newValue);
    void changeValue2(int newValue);
    void changeOperation(int operation);

signals:
    void resultCalculated(QString);

private:
    void toQString();
    int value1;
    int value2;
    Operation op;
    int result;
};
