#pragma once

///Класс сортировщика матрицы по первым элементам столбцов
class MatrixSorter
{
public:
    /*
      Конструктор принимает матрицу, кол-во строк и кол-во столбцов
      */
    MatrixSorter(int **array, int rows, int cols);
    ///Деструктор чистит память, выделенную под матрицу
    ~MatrixSorter();
    ///Функция, меняющая местами столбцы a и b
    void swapCols(int a, int b);
    ///Функция вывода матрицы
    void print();
    ///Функция сортировки пузырьком
    void sort();
protected:
    int **sArray;
    int sRows;
    int sCols;
};
