#include <stdlib.h>
#include "list.h"
#include <stdio.h>

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

void addListElement(List *list, int degree, int factor)
{
	if (isEmpty(list))
	{
		ListElement *temp = new ListElement;
		temp->degree = degree;
		temp->factor = factor;
		temp->next = NULL;
		list->head = temp;
	}
	else if (degree < list->head->degree)
	{
		ListElement *temp = new ListElement;
		temp->next = list->head;
		temp->degree = degree;
		temp->factor = factor;
		list->head = temp;
	}
	else
	{
		ListElement *current = list->head;
		while ((current->next != NULL) && (current->next->degree <= degree))
		{
			current = current->next;
		}
		if (current->degree == degree)
		{
			printf("%dth degree's already exist\n", degree);
			return;
		}
		ListElement *temp = new ListElement;
		temp->next = current->next;
		current->next = temp;
		temp->degree = degree;
		temp->factor = factor;
	}
}

void printList(List *list)
{
	if (isEmpty(list))
	{
		printf("No elements\n");
		return;
	}
	ListElement *current = list->head;
	while (current != NULL)
	{
		printf("%d*x^%d ", current->factor, current->degree);
		current = current->next;
	}
	printf("\n");
}

bool equals(List *p, List *q)
{
	ListElement *tempP = p->head;
	ListElement *tempQ = q->head;
	while ((tempP != NULL) && (tempQ != NULL))
	{
		if ((tempP->degree == tempQ->degree) && (tempP->factor == tempQ->factor))
		{
			tempP = tempP->next;
			tempQ = tempQ->next;
		}
		else
			return false;
	}
	return (tempP == NULL) && (tempQ == NULL);
}

int value(List *list, int x)
{
	if (isEmpty(list))
	{
		return INT_MAX;
	}
	ListElement *current = list->head;
	int result = 0;
	while (current != NULL)
	{
		int temp = 1;
		for (int i = 0; i < current->degree; i++)
		{
			temp *= x;
		}
		result += temp * current->factor;
		current = current->next;
	}
	return result;
}

void addLists(List *p, List *q, List *r)
{
	ListElement *tempP = p->head;
	ListElement *tempQ = q->head;
	while ((tempP != NULL) && (tempQ != NULL))
	{
		if (tempP->degree < tempQ->degree)
		{
			addListElement(r, tempP->degree, tempP->factor);
			tempP = tempP->next;
		}
		else if (tempP->degree > tempQ->degree)
		{
			addListElement(r, tempQ->degree, tempQ->factor);
			tempQ = tempQ->next;
		}
		else
		{
			addListElement(r, tempQ->degree, tempP->factor + tempQ->factor);
			tempP = tempP->next;
			tempQ = tempQ->next;
		}
	}
	if (tempP == NULL)
	{
		while (tempQ != NULL)
		{
			addListElement(r, tempQ->degree, tempQ->factor);
			tempQ = tempQ->next;
		}
	}
	else
	{
		while (tempP != NULL)
		{
			addListElement(r, tempP->degree, tempP->factor);
			tempP = tempP->next;
		}
	}
}
