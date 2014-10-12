#include "stdafx.h"
#include "matrix.h"

Matrix::Matrix(int d1, int d2) :
	n(d1),
	m(d2)
{
	array = new double*[n];
	for (int i = 0; i < n; i++)
	{
		array[i] = new double[m];
	}
}

Matrix::~Matrix()
{
	for (int i = 0; i < n; i++)
	{
		delete[] array[i];
	}
	delete array;
}

void Matrix::read(istream &in)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			in >> array[i][j];
		}
	}
}

void Matrix::print(ostream& out)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			out << array[i][j] << " ";
		}
		out << "\n";
	}
}

void Matrix::swapColumns(int c1, int c2)
{
	double temp;
	for (int j = 0; j < n; j++)
	{
		temp = array[j][c1];
		array[j][c1] = array[j][c2];
		array[j][c2] = temp;
	}
}

void Matrix::swapLines(Vector* x, int r1, int r2)
{
	double temp;
	for (int j = 0; j < m; j++)
	{
		temp = array[r1][j];
		array[r1][j] = array[r2][j];
		array[r2][j] = temp;			
	}
	temp = x->elem(r1);
	x->set(r1, x->elem(r2));
	x->set(r2, temp);
}

void Matrix::destroy(Vector* x, int d)
{
	for (int i = d + 1; i < n; i++)
	{
		double v = - array[i][d] / array[d][d];
		for (int k = d; k < m; k++)
		{
			array[i][k] = array[i][k] + v*array[d][k];
		}
		x->set(i, x->elem(i) + v*x->elem(d));
	}
}

Vector* Matrix::GaussMethod(Vector* b)
{
	Vector* x = new Vector(b->size);
	int* memory = new int[b->size];
	double* y = new double[b->size];

	double max;
	int k, l;

	for (int i = 0; i < b->size; i++)
		memory[i] = i;

	for (int i = 0; i < b->size; i++)
	{
		max = 0.0;
		k = i;
		l = i;

		for (int s = i; s < b->size; s++)
		{
			for (int m = i; m < b->size; m++)
			if (fabs(array[s][m]) > max)
			{
				max = fabs(array[s][m]);
				k = s;
				l = m;
			}
		}

		swapLines(b, i, k);
		swapColumns(i, l);

		int temp = memory[i];
		memory[i] = memory[l];
		memory[l] = temp;

		destroy(b, i);
	}
	for (int i = b->size - 1; i > -1; i--)
	{
		double v = 0.0;
		for (int j = b->size - 1; j > i; j--)
			v += array[i][j] * y[j];
		y[i] = (b->elem(i) - v) / array[i][i];
	}
	
	for (int i = 0; i < b->size; i++)
		x->set(memory[i], y[i]);
	
	return x;
}

