#pragma once
#include "class.h"

///Класс списка с реализацией через массив
class Array: public ListType
{
public:
    ///Конструктор инициализирует int *array
    Array();
    ///Деструктор удаляет массив из памяти
    ~Array();
    void add(int value);
    void remove(int value);
    void print();
protected:
    ///Массив, на котором реализуется список
    int* array;
    ///Количество элементов в списке
    int size;
};
