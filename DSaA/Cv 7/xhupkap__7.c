#include <stdlib.h>
#include <stdio.h>

typedef unsigned short EdgeType;

#define INF 0b1111111111111111

void print2DArr(EdgeType** arr, int w, int h, int asMatrix)
{
	if (asMatrix)
	{
		for (int i = 0; i < w; i++)
			printf("%i\t", i);
		printf("\n");
	}
	else
		printf("%i %i\n", w, h);

	for (int y = 0; y < h; y++)
	{
		if (asMatrix)
			printf("%i: ", y);
		for (int x = 0; x < w; x++)
			printf("%i%s", !asMatrix && x == y ? 0 : arr[y][x], asMatrix ? "\t" : " ");

		printf("\n");
	}
}

// int findMinEdgeIndex(EdgeType* arr, int diag, int size) // Find index of min weight in 2D matrix graph
// {
// 	int iMin = diag == 0 ? 1 : 0;
// 	for (int i = 1; i < size; i++)
// 		if (arr[i] > 0 && i != diag && (arr[iMin] < 1 || arr[i] < arr[iMin]))
// 			iMin = i;
	
// 	return iMin;
// }

int minDistance(int* dists, short* visited, int size)
{
	int iMin = -1;
	for (int i = 0; i < size; i++) 
	{
		if (!visited[i] && (iMin == -1 || dists[i] < dists[iMin]))
			iMin = i;
	}

	return iMin;
}

EdgeType** createSquareMatrix(int vertCount, int defaultWeights)
{
	EdgeType** graph = malloc(vertCount * sizeof(EdgeType*));
	for (int y = 0; y < vertCount; y++)
	{
		graph[y] = malloc(vertCount * sizeof(EdgeType));

		for (int vi = 0; vi < vertCount; vi++)
			graph[y][vi] = defaultWeights;
	}

	return graph;
}

void insert(EdgeType** graph, int size, int vert1, int vert2, int weight, int* countOfPrints);
void search(EdgeType** graph, int size, int vert1, int vert2, int* countOfPrints);
void update(EdgeType** graph, int size, int vert1, int vert2, int addW, int* countOfPrints);
void delete(EdgeType** graph, int size, int vert1, int vert2, int* countOfPrints);

void printPath(int*, int, int);

int scanf3int(void*, void*, void*);

void failBasic(char*, int*);
void fail(char*, int, int, int*);

void free2DArr(EdgeType**, int);

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	EdgeType** graph;

	int countOfPrints = 0;

	int vertCount, edgeCount;
	scanf("%i %i", &vertCount, &edgeCount);
	getchar();

	graph = createSquareMatrix(vertCount, 0);
	for (int i = 0; i < edgeCount; i++)
	{
		int vert1, vert2, weight;

		char str[32] = {0};
		fgets(str, sizeof(str), stdin);

		if (sscanf(str, "(%i, %i, %i)", &vert1, &vert2, &weight) != 3)
		{
			failBasic("insert", &countOfPrints);
			continue;
		}

		insert(graph, vertCount, vert1, vert2, weight, &countOfPrints);
	}

	for (char option; (option = getchar()) != EOF; ) 
	{
 		if (option == 'i' || option == 'u')
		{
			int vert1 = -1, vert2 = -1, weight = -1;
			if (scanf3int(&vert1, &vert2, &weight) != 3)
			{
				failBasic(option == 'i' ? "insert" : "update", &countOfPrints);
				continue;
			}

			if (option == 'i')
				insert(graph, vertCount, vert1, vert2, weight, &countOfPrints);
			else
				update(graph, vertCount, vert1, vert2, weight, &countOfPrints);
		}
		else if (option == 's' || option == 'd')
		{
			int vert1 = -1, vert2 = -1, _;
			if (scanf3int(&vert1, &vert2, &_) != 2)
			{
				failBasic(option == 's' ? "search" : "delete", &countOfPrints);
				continue;
			}

			if (option == 's')
				search(graph, vertCount, vert1, vert2, &countOfPrints);
			else
				delete(graph, vertCount, vert1, vert2, &countOfPrints);
		}
		else if (option == 'p' || option == 'f')
		{
			print2DArr(graph, vertCount, vertCount, option == 'p');
		}
		else if (option == 'q')
			break;
	}

	free2DArr(graph, vertCount);
}

void insert(EdgeType** graph, int size, int vert1, int vert2, int weight, int* countOfPrints)
{
	if (weight < 1)
		goto fail;

	if (vert1 == vert2 || vert1 >= size || vert2 >= size || vert1 < 0 || vert2 < 0) // Bounds check
	{
		fail: fail("insert", vert1, vert2, countOfPrints);
		return;
	}

	if (graph[vert1][vert2] > 1 || graph[vert2][vert1] > 1) // Edge was already inserted...
		goto fail;

	graph[vert1][vert2] = (graph[vert2][vert1] += weight);

	// EdgeType minI = graph[vert1][vert1]; // Update index of min at diagonals
	// if (minI < 1 || weight < graph[vert1][minI])
	// 	graph[vert1][vert1] = vert2;

	// if ((minI = graph[vert2][vert2]) < 1 || weight < graph[vert2][minI])
	// 	graph[vert2][vert2] = vert1;
}

void search(EdgeType** graph, int size, int vert1, int vert2, int* countOfPrints) // Dijkstra
{
	int* dists = malloc(size * sizeof(int));
	int* shortestPath = malloc(size * sizeof(int));
	short* visited = calloc(size, sizeof(short));
	unsigned short destReachedCount = 0;

	for (int i = 0; i < size; i++)
	{
		shortestPath[i] = -1;
		dists[i] = INF;
	}

	dists[vert1] = 0;

	for (int y = 0; y < size - 1; y++)
	{
		int vert = minDistance(dists, visited, size); // Pick the mini dist vertex
		visited[vert] = 1;

		for (int x = 0; x < size; x++) // Update dists
		{
			if (!visited[x] && 
				graph[vert][x] && 
				dists[vert] != INF && 
				dists[vert] + graph[vert][x] < dists[x])
			{
				shortestPath[x] = vert;
				dists[x] = dists[vert] + graph[vert][x];

				if (x == vert2 &&  ++destReachedCount > 1)
					break;
			}
		}
	}

	if (!destReachedCount)
	{
		fail("search", vert1, vert2, countOfPrints);
		goto fr;
	}

	if ((*countOfPrints)++)
		printf("\n");
	printf("%i: [", vert2);
	printPath(shortestPath, vert1, vert2);
	printf("]");

	fr:
	free(dists);
	free(shortestPath);
	free(visited);
}

void update(EdgeType** graph, int size, int vert1, int vert2, int addW, int* countOfPrints)
{
	if (vert1 == vert2 || vert1 >= size || vert2 >= size || vert1 < 0 || vert2 < 0) // Bounds check
	{
		fail: fail("update", vert1, vert2, countOfPrints);
		return;
	}

	if (graph[vert1][vert2] < 1 || graph[vert2][vert1] < 1 || // Edge does not exist
		graph[vert1][vert2]+addW < 0) // Invalid update
		goto fail;

	EdgeType weight = graph[vert1][vert2] = (graph[vert2][vert1] += addW);

	// EdgeType minI = graph[vert1][vert1]; // Update index of min at diagonals
	// if (weight < graph[vert1][minI])
	// 	graph[vert1][vert1] = vert2;

	// minI = graph[vert2][vert2];
	// if (weight < graph[vert2][minI])
	// 	graph[vert2][vert2] = vert1;
}

void delete(EdgeType** graph, int size, int vert1, int vert2, int* countOfPrints)
{
	if (vert1 == vert2 || vert1 >= size || vert2 >= size || vert1 < 0 || vert2 < 0) // Bounds check
	{
		fail: fail("delete", vert1, vert2, countOfPrints);
		return;
	}

	if (graph[vert1][vert2] < 1 || graph[vert2][vert1] < 1) // Edge does not exist
		goto fail;

	graph[vert1][vert2] = graph[vert2][vert1] = 0;

	// EdgeType minI = graph[vert1][vert1]; // Update index of min at diagonals
	// if (vert2 == minI)
	// 	graph[vert1][vert1] = findMinEdgeIndex(graph[vert1], vert1, size);

	// minI = graph[vert2][vert2];
	// if (vert1 == minI)
	// 	graph[vert2][vert2] = findMinEdgeIndex(graph[vert2], vert2, size);
}

void printPath(int* shortestPath, int vert1, int vert2) 
{
	if (vert1 == vert2)
		printf("%d", vert1);
	else
	{
		printPath(shortestPath, vert1, shortestPath[vert2]);
		printf(", %d", vert2);
	}
}

int scanf3int(void* arg1, void* arg2, void* arg3) //No blocking, not biased scanf that returns count of tokens
{
	char line[32] = {0}, _[8];
	fgets(line, sizeof(line), stdin);

	return sscanf(line, "%i %i %i %s", arg1, arg2, arg3, _);
}

void failBasic(char* str, int* countOfPrints)
{
	if ((*countOfPrints)++)
		printf("\n");
	printf("%s failed", str);
}

void fail(char* str, int vert1, int vert2, int* countOfPrints)
{
	if ((*countOfPrints)++)
		printf("\n");
	printf("%s %i %i failed", str, vert1, vert2);
}

void free2DArr(EdgeType** arr, int h)
{
	for (int y = 0; y < h; y++)
		free(arr[y]);
	free(arr);
}