#include "calc.h"

Calc::Calc()
    :value1(0), value2(0), op(ADD), result(0)
{
}

void Calc::changeValue1(int newValue)
{
    //qDebug("Value 1 = %d", newValue);
    if (value1 != newValue)
    {
        value1 = newValue;
        calculate();
    }
}

void Calc::changeValue2(int newValue)
{
    //qDebug("Value 2 = %d", newValue);
    if (value2 != newValue)
    {
        value2 = newValue;
        calculate();
    }
}

void Calc::changeOperation(int operation)
{
    //qDebug("%d", operation);
    op = (Operation) operation;
    calculate();
}

void Calc::calculate()
{
    switch (op)
    {
    case ADD:
        result = value1 + value2;
        break;
    case SUB:
        result = value1 - value2;
        break;
    case MUL:
        result = value1 * value2;
        break;
    case DIV:
        if (value2 == 0)
        {
            emit resultCalculated("ERROR");
            return;
        }
        result = value1 / value2;
        break;
    }
    toQString();
}

void Calc::toQString()
{
    char string[100];
    memset(string, '\0', 100);
    int digits[100];
    int res = (result > 0) ? result : -result;
    int n = 0;
    do
    {
        digits[n] = res % 10;
        res /= 10;
        n++;
    } while (res > 0);
    int sh = 0;
    if (result < 0)
    {
        string[0] = '-';
        sh = 1;
    }
    for (int i = 0; i < n; i++)
    {
        string[i + sh] = digits[n - i - 1] + '0';
    }
    //qDebug("result = {%s}", string);
    emit resultCalculated(string);
}
