#pragma once

struct BinaryTreeNode
{
	int value;
	BinaryTreeNode *rightChild;
	BinaryTreeNode *leftChild;
};

struct BinaryTree
{
	BinaryTreeNode *root;
};

BinaryTree *createTree();
bool exists(BinaryTree *tree, int value);
void add(BinaryTree *tree, int value);
void remove(BinaryTree *tree, int value);
void printUp(BinaryTree *tree);
void printDown(BinaryTree *tree);
void destroyTree(BinaryTree *tree);
//delete
//print >
//print <
