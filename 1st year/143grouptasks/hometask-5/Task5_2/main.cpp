#include <iostream>
#include <stdio.h>

using namespace std;

int const doubleSize = 64;

long long doubleToLongLong(double numberDouble)
{
	return *((long long *)&numberDouble);
}

int calculateExponent(long long const numberLongLong)
{
	return (numberLongLong >> 52) & 0x7FF;
}

double calculateMantisse(long long const numberLongLong)
{
	double result = 1.0;
	double degree = 0.5;
	for (int i = doubleSize - 13; i >= 0; i--)
	{
		if (numberLongLong & (1LL << i))
		{
			result += degree;
		}
		degree *= 0.5;
	}
	return result;
}

void graphicPrint(double numberDouble)
{
	long long numberLongLong = doubleToLongLong(numberDouble);
	int exponent = calculateExponent(numberLongLong);
	if (numberLongLong & (1LL << (doubleSize - 1)))
	{
		cout << "-";
	}
	else
	{
		cout << "+";
	}
	double mantisse = calculateMantisse(numberLongLong);
	if (mantisse == 1.0 && exponent == 0)
	{
		cout << "0.0*2^(0)\n";
	}
	else
	{
		printf("%.52g", mantisse);
		cout << "*2^(" << exponent - 1023 << ")\n";
	}
}

void binaryPrint(long long const numberLongLong)
{
	cout << "Binary result:\n";
	for (int i = doubleSize - 1; i >= 0; i--)
	{
		if ((i == doubleSize - 2) || (i == doubleSize - 13))
		{
			cout << "|";
		}
		if (numberLongLong & (1LL << i))
		{
			cout << "1";
		}
		else
		{
			cout << "0";
		}
	}
	cout << "\n";
}

int main()
{
	double numberDouble = 0.0;
	cout << "Write Double\n";
	cin >> numberDouble;
	binaryPrint(doubleToLongLong(numberDouble));
	cout << "Double Graphic" << endl;
	graphicPrint(numberDouble);
	return 0;
}

