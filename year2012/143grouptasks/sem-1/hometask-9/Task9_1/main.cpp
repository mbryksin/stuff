#include "hash.h"
#include <iostream>

void workHard(int hashSize)
{
	FILE *input1 = fopen("input1.txt", "r");
	HashTable *table = createTable(hashSize);
	int counter = 0;
	while (!feof(input1))
	{
		char string[1000] = {};
		fgets(string, 1000, input1);
		if (strlen(string) < 1)
			break;
		if (counter > 0.7 * hashSize)
		{
			destroyHashTable(table);
			delete table;
			fclose(input1);
			//printf("REBUILD!\n");
			workHard(2 * hashSize);
			return;
		}
		buildTable(table, string);
		memset(string, '\0', 1000);
		counter++;
	}
	fclose(input1);
	//printTable(table);
	FILE *input2 = fopen("input2.txt", "r");
	FILE *output = fopen("output.txt", "w");
	while (!feof(input2))
	{
		char string[1000] = {};
		fgets(string, 1000, input1);
		if (strlen(string) < 1)
			break;
		if (isExists(table, string))
		{
			fputs(string, output);
		}
		memset(string, '\0', 1000);
	}

	destroyHashTable(table);
	delete table;
	fclose(input2);
	fclose(output);
}

int main()
{
	printf("Start finding similar strings...\n");
	workHard(10);
	printf("Completed sucsessfully!\n");
	return 0;
}
