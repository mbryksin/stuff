#pragma once
#include <limits.h>

struct ListElement
{
	int degree;
	int factor;
	ListElement *next;
};

struct List
{
	ListElement *head;
};

bool isEmpty(List *list);
List *createList();
void addListElement(List *list, int degree, int factor);
void destroyList(List *list);
void printList(List *list);
bool equals(List *p, List *q);
int value(List *list, int x);
void addLists(List *p, List *q, List *r);
