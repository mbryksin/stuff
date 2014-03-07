#include <stdio.h>
#include <stdlib.h>
#include "bubblesorter.h"
#include "insertsorter.h"

void checkSort(Sorter *object)
{
    printf("Before sort:\n");
    object->print();
    printf("After sort:\n");
    object->sort();
    object->print();
}

void fillArray(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = (rand() % 18) - 9;
    }
}

int main()
{
    int size = 0;
    printf("Write number of elements:\n");
    scanf("%d", &size);
    int *array = new int[size];
    fillArray(array, size);

    printf("--------------------------\n");
    printf("Bubble Sort!!!\n");
    Sorter *bubbleSorter = new BubbleSorter(array, size);
    checkSort(bubbleSorter);
    delete bubbleSorter;
    printf("--------------------------\n");
    printf("Insert Sort!!!\n");
    Sorter *insertSorter = new InsertSorter(array, size);
    checkSort(insertSorter);

    delete[] array;
    delete insertSorter;
    return 0;
}

