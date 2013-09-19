#pragma once

struct List
{
	int value;
	List *next;
};

void createList(List *head, int const n);
void createCircleList(List *head, int const n);
void printList(List *head);
void printCircleList(List *head);
void addElement(List *head, int x);
void destroyElement(List *head, int x);
void destroyList(List *head);
void destroyCircleList(List *head);
bool destroyTargetElement(List *target);
