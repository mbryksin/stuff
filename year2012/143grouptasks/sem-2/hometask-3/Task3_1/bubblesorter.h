#pragma once
#include "sorter.h"

///Класс реализующий сортировку пузырьком
class BubbleSorter : public Sorter
{
public:
    BubbleSorter(int array[], int size);
    void sort();
};
