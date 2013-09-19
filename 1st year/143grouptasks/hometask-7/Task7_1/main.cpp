#include <stdio.h>

using namespace std;

int const maximum = 100;

void input(FILE *in, int *a)
{
	a[1] = 1;
	a[2] = 2;
	a[3] = 3;
	int x = 0;
	int y = 0;
	while (!feof(in))
	{
		fscanf(in, "%d", &x);
		fscanf(in, "%d", &y);
		a[x] = y;
	}
}

int find(int *a, int value)
{
	if (a[value] != value)
	{
		find(a, a[value]);
	}
	else
		return value;
}

void print(int *a, int value)
{
	for (int i = 1; i <= value; i++)
	{
		printf("%d - %d\n", i, a[i]);
	}
	printf("---------------------------\n");
}

int main()
{
	int a[maximum];
	for (int i = 0; i < maximum; i++)
		a[i] = 0;
	FILE *in = fopen("input.txt","r");
	int students = 0;
	fscanf(in, "%d", &students);
	input(in, a);
	for (int i = 1; i <= students; i++)
	{
		if (a[i] == 0)
		{
			printf("%d - Remove him!\n", i);
		}
		else
		{
			a[i] = find(a, a[i]);
			printf("%d - %d\n", i, a[i]);
		}
	}
	fclose(in);
	return 0;
}

