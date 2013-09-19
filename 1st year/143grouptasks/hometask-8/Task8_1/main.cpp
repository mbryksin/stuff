#include <iostream>

using namespace std;

void swap(int &a, int &b)
{
	int x = a;
	a = b;
	b = x;
}

int main()
{
	cout << "Bubble sort. Write number of elements:" << endl;
	int size = 0;
	cin >> size;
	int *array = new int[size];
	for (int i = 0; i < size; ++i)
	{
		cout << "[" << i + 1 << "] = ";
		cin >> array[i];
	}
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size - i - 1; ++j)
		{
			if (array[j] > array[j + 1])
			{
				swap(array[j], array[j + 1]);
			}
		}
	}
	for (int i = 0; i < size; ++i)
	{
		cout << array[i] << " ";
	}
	cout << endl;
	delete(array);
	return 0;
}

