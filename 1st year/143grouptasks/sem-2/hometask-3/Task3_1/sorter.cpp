#include "sorter.h"
#include "stdio.h"

Sorter::Sorter(int array[], int size)
{
    sorterArray = new int[size];
    for (int i = 0; i < size; i++)
    {
        sorterArray[i] = array[i];
    }
    sorterSize = size;
}

Sorter::~Sorter()
{
    delete[] sorterArray;
}

void Sorter::print()
{
    for (int i = 0; i < sorterSize; i++)
    {
        printf("%d ", sorterArray[i]);
    }
    printf("\n");
}
