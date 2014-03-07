#include "printer.h"
#include "stdio.h"

Printer::Printer(int **array, int size)
    :pArray(array), pSize(size)
{
}

Printer::~Printer()
{
    for (int i = 0; i < pSize; i++)
        delete[] pArray[i];
}

void Printer::printMatrix()
{
    printLine();
    for (int i = 0; i < pSize; i++)
    {
        for (int j = 0; j < pSize; j++)
            printOne(i, j);
        printEndl();
    }
}

void Printer::printSpiral()
{
    printLine();
    int i = (pSize - 1) / 2;
    int j = i;
    int step = 1;
    while ((i != 0) && (j != 0))
    {
        for (int h = 0; h < step; j++, h++)
            printOne(i, j);
        for (int h = 0; h < step; i++, h++)
            printOne(i, j);
        step++;
        for (int h = 0; h < step; j--, h++)
            printOne(i, j);
        for (int h = 0; h < step; i--, h++)
            printOne(i, j);
        step++;
    }
    for (j = 0; j < pSize; j++)
        printOne(0, j);
    printEndl();
}
