#pragma once
#include "stdio.h"

///Класс вывода массива по спирали
class Printer
{
public:
    ///В конструкторе массив считывается из файла in.txt и инициализируется массив pArray
    Printer(int **array, int size);
    ///В деструкторе чистится память под массив
    virtual ~Printer();
    ///Вывод матрицы
    void printMatrix();
    ///Вывод по спирали
    void printSpiral();
    ///Вывод элемента матрицы в позиции [i,j]
    virtual void printOne(int i, int j) = 0;
    ///Перенос строки
    virtual void printEndl() = 0;
    ///Разделяющая линия
    virtual void printLine() = 0;
protected:
    ///Матрица
    int **pArray;
    ///Размерность матрицы
    int pSize;
};
