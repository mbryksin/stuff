#include <iostream>
#include <stdio.h>
#include "list.h"

using namespace std;

bool List::isEmpty()
{
    return head == NULL;
}

List::List(): head(NULL), tail(NULL)
{
}

List::~List()
{
    ListElement *temp = head;
    while (!isEmpty())
    {
        head = temp->next;
        delete temp;
        temp = head;
    }
}

void List::add(int value)
{
    ListElement *element = new ListElement;
    element->value = value;
    element->next = NULL;
    if (isEmpty())
    {
        head = element;
        tail = element;
    } else
    {
        tail->next = element;
        tail = element;
    }
}

void List::remove(int value)
{
    if (isEmpty())
    {
        cout << "No element\n";
        return;
    }
    ListElement *temp = head;
    if (head->value == value)
    {
        head = head->next;
        delete temp;
        return;
    }
    while ((temp->next != NULL) && (temp->next->value != value))
    {
        temp = temp->next;
    }
    if ((temp->next != NULL))
    {
        ListElement *toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        if (temp->next == NULL)
        {
            tail = temp;
        }
    }
    else
    {
        cout << "No element\n";
    }
}

void List::print()
{
    if (isEmpty())
    {
        cout << "ERROR: No elements\n";
        return;
    }
    ListElement *temp = head;
    while (temp != NULL)
    {
        cout << temp->value << " ";
        temp = temp->next;
    }
    cout << endl;
}
