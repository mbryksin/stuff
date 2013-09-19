#include <stdlib.h>
#include "listLib.h"
#include <iostream>

List *createList()
{
	List *list = new List;
	list->head = NULL;
	return list;
}

bool isEmpty(List *list)
{
	return list->head == NULL;
}

void destroyList(List *list)
{
	while (! isEmpty(list))
	{
		ListElement *temp = list->head;
		list->head = temp->next;
		delete temp;
	}
}

void printList(List *list)
{
	if (isEmpty(list))
	{
		std::cout << "I cannot do this! The list is empty.\n";
	}
	else
	{
		ListElement *current = list->head;
		while (current != NULL)
		{
			std::cout << current->value << " ";
			current = current->next;
		}
		std::cout << "\n";
	}
}

void addListElement(List *list, int x)
{
	if (isEmpty(list))
	{
		ListElement *temp = new ListElement;
		temp->value = x;
		temp->next = NULL;
		list->head = temp;
	}
	else if (x < list->head->value)
	{
		ListElement *temp = new ListElement;
		temp->next = list->head;
		temp->value = x;
		list->head = temp;
	}
	else
	{
		ListElement *current = list->head;
		while ((current->next != NULL) && (current->next->value < x))
		{
			current = current->next;
		}
		ListElement *temp = new ListElement;
		temp->next = current->next;
		current->next = temp;
		temp->value = x;
	}
}

void removeValue(List *list, int x)
{
	if (isEmpty(list))
	{
		std::cout << "I cannot do this. The list is empty.\n";
	}
	else if (list->head->value == x)
	{
		ListElement *current = list->head;
		list->head = current->next;
		delete current;
	}
	else if (list->head->value > x)
	{
		std::cout << "I cannot do this. No element.\n";
	}
	else
	{
		ListElement *current = list->head;
		while ((current->next != NULL) && (current->next->value != x))
		{
			current = current->next;
		}
		if (current->next != NULL)
		{
			ListElement *temp = current->next;
			current->next = current->next->next;
			delete temp;
		}
		else
		{
			std::cout << "I cannot do this. No element.\n";
		}
	}
}
