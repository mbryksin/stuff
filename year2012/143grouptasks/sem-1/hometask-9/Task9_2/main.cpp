#include <stdio.h>
#include <string.h>

int const max = 1000;

int hashFunction(char *string, int size)
{
	int result = string[size - 1] % 103;
	int degree = 1;
	for (int i = size - 2; i >= 0; i--)
	{
		int tempHash = string[i];
		for (int j = 0; j < degree; j++)
		{
			tempHash = (tempHash * 101) % 103;
		}
		result = (result + tempHash) % 103;
		degree++;
	}
	return result;
}

void RabinKarp(int hashPattern, char *pattern, char *text, int &countRK)
{
	int const m = strlen(pattern);
	int const n = strlen(text);
	int hashText = hashFunction(text, m);
	for (int i = 0; i < n - m + 1; ++i)
	{
		if (hashPattern == hashText)
		{
			bool isSimilar = true;
			for (int j = 0; j < m; j++)
			{
				if (pattern[j] != text[i + j])
				{
					isSimilar = false;
					break;
				}
			}
			if (isSimilar)
			{
				countRK++;
			}
		}
		int tempHash = text[i];
		for (int h = 1; h < m; h++)
		{
			tempHash = (tempHash * 101) % 103;
		}
		hashText = ((hashText - tempHash) * 101 + text[i + m] ) % 103;
		if (hashText < 0)
		{
			hashText += 103;
		}
	}
}

int main()
{
	FILE *input = fopen("input.txt", "r");
	char pattern[max] = {};
	printf("Write pattern:\n");
	scanf("%s", &pattern);
	int countRK = 0;
	int hashPattern = hashFunction(pattern, strlen(pattern));
	while (!feof(input))
	{
		char text[max] = {};
		fgets(text, max, input);
		if (strlen(text) < 1)
			break;
		RabinKarp(hashPattern, pattern, text, countRK);
	}
	printf("String \"%s\" appears %d times in text\n", pattern, countRK);
	fclose(input);
	return 0;
}
