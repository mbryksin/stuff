#include "hash.h"

bool existsKey(char **keys, char *key, int counter, int &x)
{
	for (int i = 0; i < counter; i++)
	{
		if (!strcmp(keys[i], key))
		{
			x = i;
			return true;
		}
	}
	return false;
}

void findWords(HashTable *hash, int counter)
{
	int *wordsNumbers = new int[counter];
	for (int i = 0; i < counter; ++i)
	{
		wordsNumbers[i] = 0;
	}
	char **keys = new char*[counter];
	for (int i = 0; i < counter; ++i)
	{
		keys[i] = new char[100];
		memset(keys[i], '\0', 100);
	}
	int keysCount = 0;
	for (int i = 0; i < hash->size; ++i)
	{
		if (hash->table[i]->head != NULL)
		{
			ListElement *temp = hash->table[i]->head;
			while (temp != NULL)
			{
				int position = 0;
				if (keysCount > 0 && existsKey(keys, temp->value, counter, position))
				{
					wordsNumbers[position]++;
				}
				else
				{
					keys[keysCount] = temp->value;
					wordsNumbers[keysCount] = 1;
					keysCount ++;
				}
				temp = temp->next;
			}
		}
	}
	for (int i = 0; i < counter; ++i)
	{
		if (wordsNumbers[i] != 0)
		{
			printf("%s %d\n", keys[i], wordsNumbers[i]);
		}
	}
	for (int i = 0; i < counter; ++i)
	{
		delete[] keys[i];
	}
	delete[] keys;
	delete[] wordsNumbers;
}

void doWell(int hashSize)
{
	FILE *in = fopen("input.txt","r");
	HashTable *table = createTable(hashSize);
	int counter = 0;
	while (!feof(in))
	{
		char string[1000] = {};
		fgets(string, 1000, in);
		if (strlen(string) < 1)
			break;
		char word[100] = {};
		int j = 0;
		for (unsigned int i = 0; i < strlen(string) - 1; i++)
		{
			if (string[i] != ' ')
			{
				word[j] = string[i];
				j++;
			}
			if (string[i] == ' ' || i == strlen(string) - 2)
			{
				if (strlen(word) > 0)
				{
					if (counter > 0.7 * hashSize)
					{
						destroyHashTable(table);
						delete table;
						fclose(in);
						//printf("REBUILD!\n");
						doWell(2 * hashSize);
						return;
					}
					buildTable(table, word);
					memset(word, '\0', 100);
					j = 0;
					counter++;
				}
			}
		}
	}
	findWords(table, counter);
	destroyHashTable(table);
	delete table;
	fclose(in);
}

int main()
{
//	cout << "Hello World!" << endl;
	doWell(7);
	return 0;
}
