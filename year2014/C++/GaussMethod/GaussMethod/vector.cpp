#include "stdafx.h"
#include "vector.h"

Vector::Vector(int m):
size(m)
{
	array = new double[size];
}

Vector::~Vector()
{
	delete array;
}

void Vector::print(ostream& out)
{
	for (int i = 0; i < size; i++)
		out << array[i] << " ";
}

double Vector::elem(int i)
{
	return array[i];
}

void Vector::set(int i, double x)
{
	array[i] = x;
}

void Vector::read(istream &in)
{
	for (int i = 0; i < size; i++)
		in >> array[i];
}