#include <stdlib.h>
#include "treeLib.h"
#include <iostream>


BinaryTreeNode *createNode(int value)
{
	BinaryTreeNode *node = new BinaryTreeNode;
	node->value = value;
	node->leftChild = NULL;
	node->rightChild = NULL;
	return node;
}

BinaryTree *createTree()
{
	BinaryTree *tree = new BinaryTree;
	tree->root = NULL;
	return tree;
}

bool isLeaf(BinaryTreeNode *node)
{
	return (node->leftChild == NULL && node->rightChild == NULL);
}

bool exists(BinaryTreeNode *node, int value)
{
	if (node == NULL)
		return false;
	if (node->value == value)
		return true;
	if (node->value > value)
		return exists(node->leftChild, value);
	else
		return exists(node->rightChild, value);
}

bool exists(BinaryTree *tree, int value)
{
	return exists(tree->root, value);
}

void add(BinaryTreeNode *&node, int value)
{
	if (node == NULL)
	{
		node = createNode(value);
		return;
	}

	if (value < node->value)
		add(node->leftChild, value);
	else
		add(node->rightChild, value);
}

void add(BinaryTree *tree, int value)
{
	add(tree->root, value);
}

BinaryTreeNode *leftmostChild(BinaryTreeNode *node)
{
	if (node->leftChild != NULL)
		return leftmostChild(node->leftChild);
	else
		return node;
}

BinaryTreeNode *rightmostChild(BinaryTreeNode *node)
{
	if (node->rightChild != NULL)
		return rightmostChild(node->rightChild);
	else
		return node;
}

void destroyTree(BinaryTreeNode *&node)
{
	if (node->leftChild != NULL)
	{
		destroyTree(node->leftChild);
	}
	if (node->rightChild != NULL)
	{
		destroyTree(node->rightChild);
	}
	if (isLeaf(node))
	{
		delete node;
		node = NULL;
	}
}

void destroyTree(BinaryTree *tree)
{
	return destroyTree(tree->root);
}

void printUp(BinaryTreeNode *node)
{
	if (node->leftChild == leftmostChild(node) && node->leftChild != NULL)
	{
		std::cout << node->leftChild->value << " ";
		if (node->leftChild->rightChild != NULL)
		{
			printUp(node->leftChild->rightChild);
		}
	}
	else if (node->leftChild != NULL)
	{
		printUp(node->leftChild);
	}
	std::cout << node->value << " ";
	if (node->rightChild != NULL)
	{
		printUp(node->rightChild);
	}
}

void printUp(BinaryTree *tree)
{
	printUp(tree->root);
	std::cout << "\n";
	return;
}

void printDown(BinaryTreeNode *node)
{
	if (node->rightChild == rightmostChild(node) && node->rightChild != NULL)
	{
		std::cout << node->rightChild->value << " ";
		if (node->rightChild->leftChild != NULL)
		{
			printDown(node->rightChild->leftChild);
		}
	}
	else if (node->rightChild != NULL)
	{
		printDown(node->rightChild);
	}
	std::cout << node->value << " ";
	if (node->leftChild != NULL)
	{
		printDown(node->leftChild);
	}
}

void printDown(BinaryTree *tree)
{
	printDown(tree->root);
	std::cout << "\n";
	return;
}

bool hasOneChild(BinaryTreeNode *node)
{
	return ((node->leftChild != NULL && node->rightChild == NULL)
			|| (node->leftChild == NULL && node->rightChild != NULL));
}

int deleteMin(BinaryTreeNode *&node)
{
	if (node->leftChild == NULL)
	{
		int result = node->value;
		BinaryTreeNode *temp = node;
		node = node->rightChild;
		delete temp;
		return result;
	}
	else
		return deleteMin(node->leftChild);
}

void remove(BinaryTreeNode *&node, int value)
{
	//std::cout << "Node: " << node->value << "\n";
	if (node->value != value)
	{
		if (node->value > value)
		{
			remove(node->leftChild, value);
		}
		else if (node->value < value)
		{
			remove(node->rightChild, value);
		}
	}
	else
	{
		if (isLeaf(node))
		{
			delete node;
			node = NULL;
		}
		else if (hasOneChild(node))
		{
			if (node->leftChild != NULL)
			{
				BinaryTreeNode *temp = node;
				node = node->leftChild;
				delete temp;
			}
			else if (node->rightChild != NULL)
			{
				BinaryTreeNode *temp = node;
				node = node->rightChild;
				delete temp;
			}
		}
		else if (node->leftChild != NULL && node->rightChild != NULL)
		{
			node->value = deleteMin(node->rightChild);
		}
	}
}

void remove(BinaryTree *tree, int value)
{
	if (!exists(tree, value))
	   return;
	remove(tree->root, value);
}
