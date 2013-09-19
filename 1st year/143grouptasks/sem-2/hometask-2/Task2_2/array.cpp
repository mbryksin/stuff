#include "array.h"

Array::Array()
{
    array = new int[1000];
    size = -1;
}

Array::~Array()
{
    delete[] array;
}

bool Array::isEmpty()
{
    return (size == -1);
}

void Array::add(int value)
{
    size++;
    array[size] = value;
}

int Array::pop()
{
    int result = array[size];
    size--;
    return result;
}
