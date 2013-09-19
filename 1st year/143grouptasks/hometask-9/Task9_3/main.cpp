#include <stdio.h>
#include "stack.h"
#include "graph.h"

using namespace std;

void DFS(Graph *graph, bool *&visited, Stack *stack, int i)
{
	visited[i] = true;
	for (int j = 0; j < graph->size; j++)
	{
		if ((graph->a[i][j] != 0) && (!visited[j]))
		{
			push(stack, j);
		}
	}
	if (! isEmpty(stack))
	{
		DFS(graph, visited, stack, pop(stack));
	}
}

int connectedComponents(Graph *graph)
{
	bool *visited = new bool[graph->size];
	for (int i = 0; i < graph->size; i++)
	{
		visited[i] = false;
	}
	int connections = 0;
	for (int i = 0; i < graph->size; i++)
	{
		if (! visited[i])
		{
			connections++;
			Stack *stack = createStack();
			DFS(graph, visited, stack, i);
			destroy(stack);
			delete stack;
		}
	}
	delete []visited;
	return connections;
}

int main()
{
	FILE *in = fopen("input2.txt", "r");
	int n = 0;
	fscanf(in, "%d", &n);
	Graph *graph = createGraph(n);
	while (!feof(in))
	{
		int i = 0;
		int j = 0;
		int len = 0;
		fscanf(in, "%d %d %d\n", &i, &j, &len);
		addToGraph(graph, i - 1, j - 1, len);
	}
	printf("%d connected components\n", connectedComponents(graph));
	deleteGraph(graph);
	delete graph;
	fclose(in);
	return 0;
}

