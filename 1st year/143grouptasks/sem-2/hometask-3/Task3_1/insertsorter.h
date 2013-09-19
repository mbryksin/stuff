#pragma once
#include "sorter.h"

///Класс реализующий сортировку вставкой
class InsertSorter : public Sorter
{
public:
    InsertSorter(int array[], int size);
    void sort();
};
