#pragma once

///Класс сортировщика
class Sorter
{
public:
    /*
     *Конструктор сортировщика
     *@param array  принимает массив
     *@param size   размер массива
    */
    Sorter(int array[], int size);
    ///Деструктор
    virtual ~Sorter();
    ///Виртуальная сортировка
    virtual void sort() = 0;
    ///Вывод массива
    void print();
protected:
    int *sorterArray;
    int sorterSize;
};

