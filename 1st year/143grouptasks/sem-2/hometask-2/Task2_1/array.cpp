#include <iostream>
#include "array.h"

using namespace std;

Array::Array()
{
    array = new int[1000];
    size = 0;
}

Array::~Array()
{
    delete array;
}

void Array::add(int value)
{
    array[size] = value;
    size++;
}

void Array::remove(int value)
{
    if (size == 0)
    {
        cout << "ERROR: No elements\n";
        return;
    }

    int pos = -1;
    for (int i = 0; i < size; i++)
    {
        if (array[i] == value)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        cout << "ERROR: No such value\n";
    } else if (pos == size)
    {
        size--;
    } else
    {
        for (int i = pos; i < size - 1; i++)
        {
            array[i] = array[i + 1];
        }
        size--;
    }
}

void Array::print()
{
    if (size == 0)
    {
        cout << "ERROR: No elements\n";
        return;
    }
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}
