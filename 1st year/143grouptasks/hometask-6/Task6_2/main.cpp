#include "tree.h"
#include <iostream>

int const maximum = 150;

using namespace std;

int main()
{
	FILE *in = fopen("input.txt", "r");
	Tree *tree = create();
	char str[maximum] = {};
	fgets(str, maximum, in);
	int pos = 0;
	while (str[pos] != '(')
	{
		pos++;
	}
	pos++;
	workout(in, tree->root, str, pos);
	printTree(tree->root);
	cout << endl;
	printf("%g\n", calculateTree(tree->root));
	destroyTree(tree->root);
	delete tree;
	fclose(in);
	return 0;
}
