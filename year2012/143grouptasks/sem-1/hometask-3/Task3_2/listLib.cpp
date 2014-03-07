#include <stdlib.h>
#include <iostream>
#include "listLib.h"

void create(List *head, int const n, List *temp)
{
	int i = 0;
	List *current = head;
	for (i = 1; i < n; i++)
	{
		current->value = i;
		current->next = new List;
		current = current->next;
	}
	current->value = i;
	current->next = temp;
}

void createList(List *head, int const n)
{
	create(head, n, NULL);
}

void createCircleList(List *head, int const n)
{
	create(head, n, head);
}

void printList(List *head)
{
	List *current = head;
	while (current != NULL)
	{
		std::cout << current->value << " ";
		current = current->next;
	}
	std::cout << "\n";
}


void printCircleList(List *head)
{
	List *current = head;
	while (current->next != head)
	{
		std::cout << current->value << " ";
		current = current->next;
	}
	std::cout << current->value << " ";
	std::cout << "\n";
}

void destroyList(List *head)
{
	List *current1 = head;
	List *current2 = current1->next;
	while (current2 != NULL)
	{
		delete current1;
		current1 = current2;
		current2 = current2->next;
	}
	delete current1;
}

void destroyCircleList(List *head)
{
	List *current1 = head;
	List *current2 = current1->next;
	while (current2->next != current2)
	{
		delete current1;
		current1 = current2;
		current2 = current2->next;
	}
	delete current2;
	delete current1;
}


void addElement(List *head, int x)
{
	List *current = head;
	while ((current->next != NULL) && (current->next->value < x))
	{
		current = current->next;
	}
	List *newList = new List;
	newList->next = current->next;
	current->next = newList;
	newList->value = x;

}

bool destroyTargetElement(List *target)
{
	if (target->next != target)
	{
		List *temp = target->next;
		target -> next = target -> next -> next;
		delete temp;
		return true;
	}
	else return false;
}

