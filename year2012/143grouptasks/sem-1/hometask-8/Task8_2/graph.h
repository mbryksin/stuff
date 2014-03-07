#pragma once

#include <stdio.h>
#include <string.h>
#include <limits.h>

struct Graph
{
	int size;
	int **a;
	int *minPath;
	char **paths;
};

Graph *createGraph(int n);
void printGraph(Graph *graph);
void addToGraph(Graph *graph, int const i, int const j, int const len);
void deleteGraph(Graph *graph);
