#include <iostream>
#define maximum 100

using namespace std;

void print(int x)
{
	cout << x << " ";
}

void init(int array[][maximum], int n)
{
	int k = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			array[i][j] = k++;
			cout.width(2);
			cout << array[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "-------------------------------\n";
}

void printSpiral(int array[][maximum], int n)
{
	int k = 1;
	int i = n / 2;
	int j = n / 2;
	while (i != 0)
	{
		for (int step = 0; step < k; step++)
		{
			print(array[i][j]);
			j++;
		}
		for (int step = 0; step < k; step++)
		{
			print(array[i][j]);
			i++;
		}
		k++;
		for (int step = 0; step < k; step++)
		{
			print(array[i][j]);
			j--;
		}
		for (int step = 0; step < k; step++)
		{
			print(array[i][j]);
			i--;
		}
		k++;
	}
	for (j = 0; j < n; j++)
	{
		print(array[i][j]);
	}

}

int main()
{
	int n = 0;
	int array[maximum][maximum] = {};
	cout << "Write N: ";
	cin >> n;
	if (n % 2 == 0)
	{
		cout << "I cannot do this!\n";
	}
	else
	{
		cout << "-------------------------------\n";
		init(array, n);
		printSpiral(array, n);
		cout << "\n";
	}
	return 0;
}

