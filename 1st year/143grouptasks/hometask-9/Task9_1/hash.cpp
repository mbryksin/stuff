#include "hash.h"
#include <stdlib.h>

List *createList()
{
	List *list = new List;
	list->head = NULL;
	return list;
}

HashTable *createTable(int sizeofHash)
{
	HashTable *hash = new HashTable;
	hash->table = new List*[sizeofHash];
	for (int i = 0; i < sizeofHash; ++i)
	{
		hash->table[i] = createList();
	}
	hash->size = sizeofHash;
	return hash;
}

void destroyHashTable(HashTable *hash)
{
	for (int i = 0; i < hash->size; ++i)
	{
		destroyList(hash->table[i]);
		delete(hash->table[i]);
	}
	delete[] hash->table;
}

bool isEmpty(List *list)
{
	return list->head == NULL;
}

void destroyList(List *list)
{
	while (!isEmpty(list))
	{
		ListElement *temp = list->head;
		delete temp->value;
		list->head = temp->next;
		delete temp;
	}
}

void addListElement(List *list, char *string)
{
	if (isEmpty(list))
	{
		ListElement *temp = new ListElement;
		temp->value = strdup(string);
		temp->next = NULL;
		list->head = temp;
	}
	else
	{
		ListElement *current = list->head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		ListElement *temp = new ListElement;
		temp->next = current->next;
		current->next = temp;
		temp->value = strdup(string);
	}
}

void buildTable(HashTable *hash, char *string)
{
	int index = hashFunction(string, hash->size);
	addListElement(hash->table[index], string);
}

int hashFunction(char *string, int value)
{
	int result = 0;
	int step = 71;
	for (unsigned int i = 0; i < strlen(string); i++)
	{
		result = (result + string[i] * step) % value;
		step = step * step;
	}
	return (result >=0 ? result : -1 * result);
}

void printList(List *list)
{
	ListElement *current = list->head;
	while (current != NULL)
	{
		printf("%s\n", current->value);
		current = current->next;
	}
}

void printTable(HashTable *hash)
{
	for (int i = 0; i < hash->size; ++i)
	{
		if (!isEmpty(hash->table[i]))
		{
			printf("hash()=%d\n", i);
			printList(hash->table[i]);
		}
	}
}

bool isExists(HashTable *hash, char *string)
{
	//!strcmp(string, blah);
	int index = hashFunction(string, hash->size);
	if (isEmpty(hash->table[index]))
		return false;
	ListElement *temp = hash->table[index]->head;
	while (temp != NULL)
	{
		if (!strcmp(string, temp->value))
			return true;
		else
		{
			temp = temp->next;
		}
	}
	return false;
}
