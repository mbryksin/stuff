#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

class Vector {
public:
	Vector(int m);
	~Vector();
	double elem(int i);
	void set(int i, double x);
	void read(istream &in);
	void print(ostream& out);
	int size;
private:
	double* array;
};