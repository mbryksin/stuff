
#include <iostream>
#include "treeLib.h"
#include <stdio.h>

enum Situation {exit, addEl, existsEl, removeEl, printU, printD, nothing};

using namespace std;
/*
void testPrint()
{
	BinaryTree *tree = createTree();
	FILE *in = fopen("input.txt", "r");
	int x = 0;
	while (x!= 89)
	{
		fscanf(in, "%d", &x);
		add(tree, x);
	}
	printUp(tree);
	cout << "Remove: ";
	cin >> x;
	remove(tree, x);
	printDown(tree);
	destroyTree(tree);
	delete tree;
	fclose(in);
}
*/

void communicate()
{
	BinaryTree *tree = createTree();
	Situation x = nothing;
	while (x != exit)
	{
		int value = 0;
		cout << "0 - exit\n";
		cout << "1 - add\n";
		cout << "2 - exists\n";
		cout << "3 - remove\n";
		cout << "4 - print up\n";
		cout << "5 - print down\n";
		cin >> value;
		x = (Situation)value;
		switch (x)
		{
			case nothing: break;
			case exit: break;
			case addEl:
				cout << "Write element:\n";
				cin >> value;
				add(tree, value);
				cout << "Done successfully\n";
				break;
			case existsEl:
				cout << "Write element:\n";
				cin >> value;
				(exists(tree, value) ? cout << "Yes, exists\n" : cout << "No, doesn't exist\n");
				break;
			case removeEl:
				cout << "Write element:\n";
				cin >> value;
				(exists(tree, value) ? remove(tree, value), cout << "Done successfully\n" : cout << "Can't remove. Doesn't exist\n");
				break;
			case printU:
				if (tree->root != NULL)
				{
					cout << "Output to high: ";
					printUp(tree);
				}
				else
				{
					cout << "Tree is empty\n";
				}
				break;
			case printD:
				if (tree->root != NULL)
				{
					cout << "Output to down: ";
					printDown(tree);
				}
				else
				{
					cout << "Tree is empty\n";
				}
				break;
		}
	}
	if (tree->root != NULL)
		destroyTree(tree);
	delete tree;
}

int main()
{
	cout << "Hello World!" << endl;
	communicate();
//	testPrint();
	return 0;
}

