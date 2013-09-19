#pragma once

#include <stdio.h>
#include <string.h>
#include <limits.h>

struct Graph
{
	int size;
	int **a;
};

Graph *createGraph(int n);
void printGraph(Graph *graph);
void addToGraph(Graph *graph, int const i, int const j, int const len);
void deleteGraph(Graph *graph);
#ifndef GRAPH_G
#define GRAPH_G

#endif // GRAPH_G
