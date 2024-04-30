#include <stdlib.h>
#include <stdio.h>

typedef unsigned int EdgeType;
typedef char byte;

struct Node
{
	EdgeType weight; // Weight to dest vert from begining
	int dest;

	struct Node* next;
};
typedef struct Node Node;

struct Dist
{
	int weight, vert;
};
typedef struct Dist Dist;

struct DistMinHeap {
	Dist* arr;

	unsigned int size, capacity;
};
typedef struct DistMinHeap DistMinHeap;

#define parent(i) ((i) - 1) / 2
#define left(i) (2*(i) + 1)
#define right(i) (2*(i) + 2)

#define INF 0xffffffff

#define CHECK_AND_FAIL(type, size, vert1, vert2, countOfPrints) if (vert1 == vert2 /*|| vert1 >= size || vert2 >= size || vert1 < 0 || vert2 < 0*/)\
	{\
		fail: fail(type, vert1, vert2, countOfPrints);\
		return;\
	}\

#define CHECK_AND_FAIL_BASIC(type, size, vert1, vert2, countOfPrints) if (vert1 == vert2 /*|| vert1 >= size || vert2 >= size || vert1 < 0 || vert2 < 0*/)\
	{\
		fail: failBasic(type, countOfPrints);\
		return;\
	}\

void printListGraph(Node** graph, int size, byte minimal) 
{
	int edgeCount = 0;
	for (int v = 0; v < size; v++) 
	{
		printf(minimal ? "%i " : "> %i", v);
		for (Node* temp = graph[v]; temp; temp = temp->next)
		{
			printf(minimal ? "%i $i" : "|-%i->%i", temp->weight, temp->dest);
			edgeCount++;
		}

		printf("\n");
	}

	printf("%i\n", edgeCount);
}

// void printMinHeap(DistMinHeap heap)
// {
// 	printf("%i/%i:\n", heap.size, heap.capacity);
// 	for (int i = 0; i < heap.size; i++)
// 		printf("%i ", heap.arr[i].dist);
// 	printf("\n");
// }

void swap(Dist* a, Dist* b) 
{
	Dist temp = *a;
	*a = *b;
	*b = temp;
}

int scanf3int(void* arg1, void* arg2, void* arg3);
void failBasic(char* str, int* countOfPrints);
void fail(char* str, int vert1, int vert2, int* countOfPrints);
void freeGraph(Node** graph, int size);

void printPath(int* shortestPath, int vert1, int vert2);

Node* newNode(EdgeType weight, int dest);
// Dist* unshiftQ(Dist* head, Dist* node);
Node* deleteAndReorderLinks(Node** head, Node* curr, Node* prevNode);

void insertDist(DistMinHeap*, Dist);
void reheapify(DistMinHeap*, int);
Dist popMin(DistMinHeap*);

byte findAndDelete(Node** graph, int vert1, int vert2);
byte findAndUpdate(Node** graph, int vert1, int vert2, int addW);

void insert(Node** graph, int size, int vert1, int vert2, int weight, int* countOfPrints, byte checkForDups);
void search(Node** graph, int size, int startVert, int* countOfPrints);
void delete(Node** graph, int size, int vert1, int vert2, int* countOfPrints);
void update(Node** graph, int size, int vert1, int vert2, int addW, int* countOfPrints);

int main()
{
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);

	Node** graph;

	int countOfPrints = 0;

	int vertCount;
	scanf("%i", &vertCount);
	getchar();

	graph = calloc(vertCount, sizeof(Node*));

	for (char option; (option = getchar()) != EOF; ) 
	{
		if (option == '(')
		{
			int vert1 = -1, vert2 = -1, weight = -1;

			char str[32] = {0};
			fgets(str, sizeof(str), stdin);

			if (sscanf(str, "%i, %i, %i)", &vert1, &vert2, &weight) != 3)
			{
				failBasic("insert", &countOfPrints);
				continue;
			}

			insert(graph, vertCount, vert1, vert2, weight, &countOfPrints, 0);
		}
 		else if (option == 'i' || option == 'u')
		{
			int vert1 = -1, vert2 = -1, weight = -1;
			if (scanf3int(&vert1, &vert2, &weight) != 3)
			{
				failBasic(option == 'i' ? "insert" : "update", &countOfPrints);
				continue;
			}

			if (option == 'i')
				insert(graph, vertCount, vert1, vert2, weight, &countOfPrints, 1);
			else
				update(graph, vertCount, vert1, vert2, weight, &countOfPrints);
		}
		else if (option == 's')
		{
			int startVert = -1, _;
			if (scanf3int(&startVert, &_, &_) != 1)
			{
				failBasic("search", &countOfPrints);
				continue;
			}

			search(graph, vertCount, startVert, &countOfPrints);
		}
		else if (option == 'd')
		{
			int vert1 = -1, vert2 = -1, _;
			if (scanf3int(&vert1, &vert2, &_) != 2)
			{
				failBasic("delete", &countOfPrints);
				continue;
			}

			delete(graph, vertCount, vert1, vert2, &countOfPrints);
		}
		else if (option == 'p' || option == 'f')
		{
			printListGraph(graph, vertCount, option == 'f');
		}
	}

	freeGraph(graph, vertCount);
}

Node* newNode(EdgeType weight, int dest)
{
	Node* newNode = malloc(sizeof(Node));
	newNode->weight = weight;
	newNode->dest = dest;
	newNode->next = NULL;
	return newNode;
}

void insert(Node** graph, int size, int vert1, int vert2, int weight, int* countOfPrints, byte checkForDups)
{
	if (weight < 0)
		goto fail;

	CHECK_AND_FAIL("insert", size, vert1, vert2, countOfPrints);

	if (checkForDups)
		for (Node* curr = graph[vert1]; curr; curr = curr->next)
			if (curr->dest == vert2)
				goto fail;

	Node* node = newNode(weight, vert2);
	node->next = graph[vert1];
	graph[vert1] = node;

	node = newNode(weight, vert1); // Its undr graph so we need to update both...
	node->next = graph[vert2];
	graph[vert2] = node; 
}

Node* unshiftQ(Node* head, Node* node) // Add elm, keep smlst at the beginning
{
	if (!head || node->weight < head->weight)
	{
		node->next = head; 
		return node; // DO NOT FORGET TO SET HEAD AFTER CALLING!!
	}

	Node* curr = head;
	for (; curr->next && curr->next->weight < node->weight; curr = curr->next); // Find the suitable spot...

	node->next = curr->next;
	curr->next = node;
	return head;
}

void insertDist(DistMinHeap* distHeap, Dist dist) 
{
	if (distHeap->size >= distHeap->capacity)
		distHeap->arr = realloc(distHeap->arr, (distHeap->capacity *= 2) * sizeof(Dist));

	int i = distHeap->size++;
	distHeap->arr[i] = (Dist) { dist.weight, dist.vert };

	// Keep min heap ordered...
	for (int par; i && distHeap->arr[par = parent(i)].weight > distHeap->arr[i].weight; i = parent(i)) 
		swap(&distHeap->arr[i], &distHeap->arr[par]);
}

void reheapify(DistMinHeap* distHeap, int i)
{
	int min = i, left = left(i), right = right(i);

	if (left < distHeap->size && distHeap->arr[left].weight < distHeap->arr[min].weight)
		min = left;

	if (right < distHeap->size && distHeap->arr[right].weight < distHeap->arr[min].weight)
		min = right;

	if (min == i) 
		return;
	swap(&distHeap->arr[i], &distHeap->arr[min]);
	reheapify(distHeap, min);
}

Dist popMin(DistMinHeap* distHeap) 
{
	if (!distHeap->size)
		return (Dist) {-1, -1};

	if (distHeap->size == 1)
		return distHeap->arr[--distHeap->size];

	Dist min = distHeap->arr[0];
	distHeap->arr[0] = distHeap->arr[--distHeap->size];
	reheapify(distHeap, 0);

	return min;
}

void search(Node** graph, int size, int startVert, int* countOfPrints) 
{
	int totalWeight = 0;

	DistMinHeap minDist = {0};
	minDist.arr = malloc((minDist.capacity = size) * sizeof(Dist));

	byte* visited = malloc(size * sizeof(byte));
	int* parent = malloc(size * sizeof(int));

	for (int i = 0; i < size; ++i)
	{
		visited[i] = 0;
		parent[i] = -1;
	}

	minDist.arr[minDist.size++] = (Dist) { 0, startVert };

	for (; minDist.size; )
	{
		Dist min = popMin(&minDist);

		if (visited[min.vert]) // Was visited
			continue;

		visited[min.vert] = 1;
		totalWeight += min.weight;

		for (Node* curr = graph[min.vert]; curr; curr = curr->next) // Find next unvisited verts from graph
		{
			int dest = curr->dest;
			if (!visited[dest]) // Wasnt visited
			{
				parent[dest] = min.vert;
				insertDist(&minDist, (Dist) { curr->weight, dest });
			}
		}
	}

	if ((*countOfPrints)++)
		printf("\n");
	printf("%i: [", totalWeight);
	for (int i = 0, count = 0; i < size; i++)
	{
		if (parent[i] != -1)
		{
			if (count++)
				printf(", ");
			printf("(%i, %i)", parent[i], i);
		}
	}
	printf("]");

	free(visited);
	free(parent);
	free(minDist.arr);
}

Node* deleteAndReorderLinks(Node** head, Node* curr, Node* prevNode)
{
	if (curr == *head)
		*head = curr->next;
	else
		prevNode->next = curr->next;
	return curr;
}

byte findAndDelete(Node** graph, int vert1, int vert2) // Find and del edge
{
	for (Node* curr = graph[vert1], *prevNode = NULL; curr; curr = curr->next)
	{
		if (curr->dest == vert2)
		{
			free(deleteAndReorderLinks(&graph[vert1], curr, prevNode));
			return 1;
		}
		prevNode = curr;
	}

	return 0;
}

void delete(Node** graph, int size, int vert1, int vert2, int* countOfPrints)
{
	CHECK_AND_FAIL("delete", size, vert1, vert2, countOfPrints);

	if (!findAndDelete(graph, vert1, vert2) || !findAndDelete(graph, vert2, vert1))
		goto fail;
}

byte findAndUpdate(Node** graph, int vert1, int vert2, int addW) // Find and update edge
{
	for (Node* curr = graph[vert1], *prevNode = NULL; curr; curr = curr->next)
	{
		if (curr->dest == vert2)
		{
			if (curr->weight + addW < 0)
				return 0;
			curr->weight += addW;

			// graph[vert1] = unshiftQ(graph[vert1], deleteAndReorderLinks(&graph[vert1], curr, prevNode), 0);
			return 1;
		}
		prevNode = curr;
	}

	return 0;
}

void update(Node** graph, int size, int vert1, int vert2, int addW, int* countOfPrints)
{
	CHECK_AND_FAIL("update", size, vert1, vert2, countOfPrints);

	if (!findAndUpdate(graph, vert1, vert2, addW) || !findAndUpdate(graph, vert2, vert1, addW))
		goto fail;
}

void printPath(int* shortestPath, int vert1, int vert2) 
{
	if (vert1 == vert2)
		printf("%i", vert1);
	else
	{
		printPath(shortestPath, vert1, shortestPath[vert2]);
		printf(", %i", vert2);
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

void freeGraph(Node** graph, int size)
{
	for (int i = 0; i < size; i++) 
	{
		for (Node* curr = graph[i]; curr; ) 
		{
			Node* temp = curr;
			curr = curr->next;
			free(temp);
		}
	}

	free(graph);
}