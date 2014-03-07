#pragma once
#include "printer.h"

///Класс вывода в консоль
class PrinterToConsole : public Printer
{
public:
    PrinterToConsole(int **array, int size);
    void printOne(int i, int j);
    void printEndl();
    void printLine();
};
