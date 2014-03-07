#pragma once
#include "stacktype.h"

///Класс стека с реализацией через массив
class Array: public StackType {
public:
    ///Конструктор создает массив int* array
    Array();
    ~Array();
    void add(int value);
    int pop();
    bool isEmpty();
protected:
    int* array;
    ///Количество элементов в массиве
    int size;
};
