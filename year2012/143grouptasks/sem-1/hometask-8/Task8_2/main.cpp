#include "graph.h"

struct Pair
{
	int len;
	int city;
};

Pair *findWays(int *ways, int n, int &cities)
{
	Pair *founded = new Pair[n];
	int count = 0;
	for (int i = 0; i < n; ++i)
		if (ways[i] > 0)
		{
			founded[count].city = i;
			founded[count].len = ways[i];
			count++;
		}
	cities = count;
	return founded;
}

void Deikstra(Graph *graph, bool *&isChecked, int row)
{
	isChecked[row] = true;
	int cities = 0;
	Pair *founded = findWays(graph->a[row], graph->size, cities);
	bool noWay = true;
	Pair *min = new Pair;
	for (int i = 0; i < cities; ++i)
	{
		if (graph->minPath[founded[i].city] > founded[i].len + graph->minPath[row])
		{
			graph->minPath[founded[i].city] = founded[i].len + graph->minPath[row];
			delete[] graph->paths[founded[i].city];
			graph->paths[founded[i].city] = new char[1000];
			memset(graph->paths[founded[i].city], '\0', 1000);
			for (unsigned int h = 0; h < strlen(graph->paths[row]); h++)
			{
				graph->paths[founded[i].city][h] = graph->paths[row][h];
			}
			graph->paths[founded[i].city][strlen(graph->paths[founded[i].city])] = '-';
			char buffer[5] = {};
			sprintf(buffer, "%d", founded[i].city + 1);
			strcat(graph->paths[founded[i].city], buffer);
			isChecked[founded[i].city] = false;
		}
		if (!isChecked[founded[i].city])
		{
			min->city = founded[i].city;
			min->len = founded[i].len;
			noWay = false;
		}
	}
	if (noWay)
	{
		delete(min);
		delete[] founded;
		return;
	}
	for (int i = 0; i < cities; ++i)
		if (graph->minPath[min->city] > graph->minPath[founded[i].city] && !isChecked[founded[i].city])
		{
			min->city = founded[i].city;
			min->len = founded[i].len;
		}
	Deikstra(graph, isChecked, min->city);
	delete(min);
	for (int i = 0; i < cities; ++i)
	{
		if (!isChecked[founded[i].city])
		{
			Deikstra(graph, isChecked, founded[i].city);
		}
	}
	delete[] founded;
}

void test(Graph *graph)
{
	bool *isChecked = new bool[graph->size];
	memset(isChecked, false, graph->size);
	graph->minPath[0] = 0;
	delete[] graph->paths[0];
	graph->paths[0] = strdup("1");
	Deikstra(graph, isChecked, 0);
	memset(isChecked, false, graph->size);
	graph->minPath[0] = INT_MAX;
	isChecked[0] = true;
	for (int h = 1; h < graph->size; ++h)
	{
		int min = 0;
		for (int i = 1; i < graph->size; ++i)
		{
			if ((!isChecked[i]) && (graph->minPath[i] <= graph->minPath[min]))
				min = i;
		}
		if (graph->minPath[min] == INT_MAX)
			printf("To %d can't find a path\n", min + 1);
		else
			printf("To %d min length = %d; path: \"%s\"\n", min + 1, graph->minPath[min], graph->paths[min]);
		isChecked[min] = true;
	}
	delete[] isChecked;
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
	test(graph);
	deleteGraph(graph);
	delete graph;
	fclose(in);
	return 0;
}
