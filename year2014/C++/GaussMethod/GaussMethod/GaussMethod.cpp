// GaussMethod.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "matrix.h"
#include <conio.h>
#include <stdlib.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	ofstream out("output.txt");
	int size = 0;
	ifstream in("input.txt");
	in >> size;

	Matrix* m = new Matrix(size, size);
	Vector* b = new Vector(size);
	m->read(in);
	b->read(in);

	m->GaussMethod(b)->print(out);

	in.close();
	out.close();
	delete m;
	delete b;
	return 0;
}