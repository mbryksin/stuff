#include "insertsorter.h"

InsertSorter::InsertSorter(int array[], int size)
    :Sorter(array, size)
{
}

void InsertSorter::sort()
{
    for (int i = 1; i < sorterSize; i++)
    {
        int key = sorterArray[i];
        int j = 0;
        for (j = i - 1; (j > -1) && (sorterArray[j] > key); j--)
        {
            sorterArray[j + 1] = sorterArray[j];
        }
        sorterArray[j + 1] = key;
    }
}
