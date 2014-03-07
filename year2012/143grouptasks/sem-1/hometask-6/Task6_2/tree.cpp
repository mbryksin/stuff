#include "tree.h"
#include <stdlib.h>

Node *createNode()
{
	Node *temp = new Node;
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	return temp;
}

void printTree(Node *node)
{
	printf("%c", node->value);
	if (node->leftChild != NULL)
	{
		printTree(node->leftChild);
	}
	if (node->rightChild != NULL)
	{
		printTree(node->rightChild);
	}
}

Tree *create()
{
	Tree *tree = new Tree;
	tree->root = createNode();
	return tree;
}

void destroyTree(Node *&node)
{
	if (node->leftChild != NULL)
	{
		destroyTree(node->leftChild);
	}
	if (node->rightChild != NULL)
	{
		destroyTree(node->rightChild);
	}
	if ((node->rightChild == NULL) && (node->leftChild == NULL))
	{
		delete node;
		node = NULL;
	}
}

float calculateTree(Node *node)
{
	if (node->value == '*')
	{
		return calculateTree(node->leftChild) * calculateTree(node->rightChild);
	}
	else if (node->value == '+')
	{
		return calculateTree(node->leftChild) + calculateTree(node->rightChild);
	}
	else if (node->value == '-')
	{
		return calculateTree(node->leftChild) - calculateTree(node->rightChild);
	}
	else if (node->value == '/')
	{
		return calculateTree(node->leftChild) / calculateTree(node->rightChild);
	}
	else if ((node->value <= '9') && (node->value >='0'))
	{
		return node->value - '0';
	}
	return 0.0;
}

void workout(FILE *in, Node *&node, char *str, int &pos)
{
	if (str[pos] != '\n')
	{
		while ((str[pos] == ' ') || (str[pos] == ')') || (str[pos] == '('))
		{
			pos++;
		}
		if ((str[pos] == '+') || (str[pos] == '*') || (str[pos] == '/') || (str[pos] == '-'))
		{
			node->value = str[pos];
			node->leftChild = createNode();
			node->rightChild = createNode();
			pos++;
			workout(in, node->leftChild, str, pos);
			workout(in, node->rightChild, str, pos);
		}
		else if (str[pos] >= '0' && str[pos] <= '9')
		{
			node->value = str[pos];
			pos++;
		}
	}
}
