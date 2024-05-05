// C program for Dijkstra's single source shortest path
// algorithm. The program is for adjacency matrix
// representation of the graph

#include <stdio.h>

#define INF 0b1111111111111111

// Number of vertices in the graph
#define V 9

int minDistance(int* dists, short* visited, int size)
{
	int iMin = -1;
	for (int i = 0; i < size; i++) {
		if (!visited[i] && (iMin == -1 || dists[i] < dists[iMin])) {
			iMin = i;
		}
	}

	return iMin;
}

// A utility function to print the constructed distance
// array
void printSolution(int dist[])
{
	printf("Vertex \t\t Distance from Source\n");
	for (int i = 0; i < V; i++)
		printf("%d \t\t\t\t %d\n", i, dist[i]);
}

// Function that implements Dijkstra's single source
// shortest path algorithm for a graph represented using
// adjacency matrix representation
void dijkstra(int graph[V][V], int src)
{
	int dist[V];
	short visited[V];

	for (int i = 0; i < V; i++)
	{
		dist[i] = INF;
		visited[i] = 0;
	}

	dist[src] = 0;

	for (int count = 0; count < V - 1; count++) 
	{
		int u = minDistance(dist, visited, V);
		visited[u] = 1;

		for (int v = 0; v < V; v++)
			if (!visited[v] && graph[u][v]
				&& dist[u] != INF
				&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

	// print the constructed distance array
	printSolution(dist);
}

// driver's code
int main()
{
	unsigned char uint32 = 0;
	for (int i = 0; i < 500; i++)
	{
		printf("%i\n", uint32);
		uint32++;
	}
	

	/* Let us create the example graph discussed above */
	int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
						{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
						{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
						{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
						{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
						{ 0, 0, 4, 14, 10, 0, 2, 0, 0 },
						{ 0, 0, 0, 0, 0, 2, 0, 1, 6 },
						{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
						{ 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

	// Function call
	// dijkstra(graph, 0);

	return 0;
}
