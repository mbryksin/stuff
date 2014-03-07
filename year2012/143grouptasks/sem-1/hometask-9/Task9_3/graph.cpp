#include "graph.h"

Graph *createGraph(int n)
{
	Graph *graph = new Graph;
	graph->size = n;
	graph->a = new int*[n];
	for (int i = 0; i < n; ++i)
	{
		graph->a[i] = new int[n];
		for (int j = 0; j < n; ++j)
		{
			graph->a[i][j] = 0;
		}
	}
	return graph;
}

void printGraph(Graph *graph)
{
	for (int i = 0; i < graph->size; ++i)
	{
		for (int j = 0; j < graph->size; ++j)
			printf("%d ", graph->a[i][j]);
		printf("\n");
	}
}

void deleteGraph(Graph *graph)
{
	for (int i = 0; i < graph->size; ++i)
	{
		delete[] graph->a[i];
	}
	delete[] graph->a;
}

void addToGraph(Graph *graph, int const i, int const j, int const len)
{
	graph->a[i][j] = len;
	graph->a[j][i] = len;
}

