#pragma once
#include "stacktype.h"

///Класс стека с реализацией через список
class Stack: public StackType {
public:
    ///Создается пустой список
    Stack();
    ~Stack();
    void add(int value);
    int pop();
    bool isEmpty();
protected:
    ///Структура списка с указателем на голову
    struct stackElement
    {
        int value;
        stackElement *next;
    };
    stackElement *head;
};
