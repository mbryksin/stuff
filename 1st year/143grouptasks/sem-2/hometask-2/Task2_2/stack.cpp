#include "stack.h"
#include <stdio.h>

Stack::Stack(): head(NULL)
{
}

Stack::~Stack()
{
    while (!isEmpty())
    {
        pop();
    }
}

bool Stack::isEmpty()
{
    return head == NULL;
}

void Stack::add(int value)
{
    stackElement *temp = new stackElement;
    temp->value = value;
    temp->next = head;
    head = temp;
}

int Stack::pop()
{
    int result = 0;
    result = head->value;
    stackElement *temp = head->next;
    delete head;
    head = temp;
    return result;
}
