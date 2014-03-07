#pragma once
#include <stdio.h>

struct Node
{
	char value;
	Node *leftChild;
	Node *rightChild;
};
struct Tree
{
	Node *root;
};

Node *createNode();
Tree *create();
void destroyTree(Node *&node);
void printTree(Node *node);
float calculateTree(Node *node);
void workout(FILE *in, Node *&node, char *str, int &pos);
