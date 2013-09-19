#include "bubblesorter.h"

BubbleSorter::BubbleSorter(int array[], int size)
    :Sorter(array, size)
{
}

void BubbleSorter::sort()
{
    for (int j = 0; j < sorterSize; j++)
        for (int i = 0; i < sorterSize - 1; i++)
            if (sorterArray[i] > sorterArray[i + 1])
            {
                int x = sorterArray[i];
                sorterArray[i] = sorterArray[i + 1];
                sorterArray[i + 1] = x;
            }
}
