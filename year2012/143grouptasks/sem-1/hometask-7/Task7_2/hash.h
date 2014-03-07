#pragma once

#include <string.h>
#include <stdio.h>

struct ListElement
{
	char *value;
	ListElement *next;
};

struct List
{
	ListElement *head;
};

struct HashTable
{
	int size;
	List **table;
};

HashTable *createTable(int sizeofHash);
bool isEmpty(List *list);
void destroyList(List *list);
void addListElement(List *list, char *string);
void destroyHashTable(HashTable *hash);
void buildTable(HashTable *hash, char *string);
void printList(List *list);
int hashFunction(char *string, int value);
