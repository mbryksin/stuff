#pragma once
#include "printer.h"

///Класс вывода в файл
class PrinterToFile : public Printer
{
public:
    ///Конструктор считывает в какой файл будет выводиться матрица
    PrinterToFile(int **array, int size);
    ///Деструктор закрывает файл вывода
    ~PrinterToFile();
    void printOne(int i, int j);
    void printEndl();
    void printLine();
protected:
    ///Файл для вывода
    FILE *pOut;
};
