#pragma once

struct ListElement
{
	int value;
	ListElement *next;
};

struct List
{
	ListElement *head;
};

bool isEmpty(List *list);
List *createList();
void addListElement(List *list, int x);
void destroyList(List *list);
void printList(List *list);
void removeValue(List *list, int x);
