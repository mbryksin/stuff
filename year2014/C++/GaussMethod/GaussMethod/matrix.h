#include "stdafx.h"
#include "vector.h"
#include <iostream>
#include <fstream>

using namespace std;

class Matrix {
public:
	Matrix(int d1, int d2);
	~Matrix();
	void read(istream &in);
	void print(ostream& out);
	Vector* GaussMethod(Vector* b);
	int n;
	int m;
private:
	void swapColumns(int c1, int c2);
	void swapLines(Vector* x, int r1, int r2);
	void destroy(Vector* x, int d);
	double** array;
};