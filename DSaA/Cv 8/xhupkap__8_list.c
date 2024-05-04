#include <stdlib.h>
#include <stdio.h>

typedef long long EdgeType;
typedef char byte;

struct Node
{
	EdgeType weight; // Weight to dest vert from begining
	int dest;

	struct Node* next;
};
typedef struct Node Node;

struct Edge
{
	int vert1; // From
	EdgeType weight;
	int vert2; // To
};
typedef struct Edge Edge;

struct EdgeHeap {
	Edge* arr;

	unsigned int size, capacity;
};
typedef struct EdgeHeap EdgeHeap;

#define parent(i) ((i) - 1) / 2
#define left(i) (2*(i) + 1)
#define right(i) (2*(i) + 2)

#define numComparator(a, b) (a > b ? 1 : (a == b ? 0 : -1))

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

void swap(Edge* a, Edge* b) 
{
	Edge temp = *a;
	*a = *b;
	*b = temp;
}

#define normalizeEdge(edge) (edge.vert1 > edge.vert2 ? ((Edge) { edge.vert2, edge.weight, edge.vert1 }) : edge)

int scanf3int(void* arg1, void* arg2, void* arg3);
void failBasic(char* str, int* countOfPrints);
void fail(char* str, int vert1, int vert2, int* countOfPrints);
void freeGraph(Node** graph, int size);

int edgeWeightComparator(Edge, Edge);
int edgeVertComparator(Edge, Edge);
// int negEdgeVertComparator(Edge, Edge);

Node* newNode(EdgeType weight, int dest);
// Edge* unshiftQ(Edge* head, Edge* node);
Node* deleteAndReorderLinks(Node** head, Node* curr, Node* prevNode);

void insertEdge(EdgeHeap*, Edge, int (*comparator)(Edge, Edge));
void reheapify(EdgeHeap*, int, int, int (*comparator)(Edge, Edge));
Edge popMin(EdgeHeap*, int (*comparator)(Edge, Edge));

// void sortEdges(Edge*, int, int (*comparator)(Edge, Edge));
void sortEdges(Edge*, int, int, int (*comparator)(Edge, Edge));

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
		// else if (option == 'p' || option == 'f')
		// {
		// 	printListGraph(graph, vertCount, option == 'f');
		// }
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

void insertEdge(EdgeHeap* distHeap, Edge dist, int (*comparator)(Edge, Edge)) 
{
	if (distHeap->size >= distHeap->capacity)
		distHeap->arr = realloc(distHeap->arr, (distHeap->capacity *= 2) * sizeof(Edge));

	int i = distHeap->size++;
	distHeap->arr[i] = (Edge) { dist.vert1, dist.weight, dist.vert2 };

	// Keep min heap ordered...
	for (int par; i && comparator(distHeap->arr[par = parent(i)], distHeap->arr[i]) > 0; i = parent(i)) 
		swap(&distHeap->arr[i], &distHeap->arr[par]);
}

void reheapify(EdgeHeap* distHeap, int i, int size, int (*comparator)(Edge, Edge))
{
	int min = i, left = left(i), right = right(i);
	if (size < 0)
		size = distHeap->size;

	if (left < size && comparator(distHeap->arr[left], distHeap->arr[min]) < 0)
		min = left;

	if (right < size && comparator(distHeap->arr[right], distHeap->arr[min]) < 0)
		min = right;

	if (min == i) 
		return;
	swap(&distHeap->arr[i], &distHeap->arr[min]);
	reheapify(distHeap, min, size, comparator);
}

Edge popMin(EdgeHeap* distHeap, int (*comparator)(Edge, Edge)) 
{
	if (!distHeap->size)
		return (Edge) {-1, -1, -1};

	if (distHeap->size == 1)
		return distHeap->arr[--distHeap->size];

	Edge min = distHeap->arr[0];
	distHeap->arr[0] = distHeap->arr[--distHeap->size];
	reheapify(distHeap, 0, -1, comparator);

	return min;
}

// void sortEdges(Edge* arr, int size, int (*comparator)(Edge, Edge)) // Heap sort
// {
// 	EdgeHeap maxHeap = { arr, size };
// 	for (int i = size / 2 - 1; i >= 0; i--)
// 		reheapify(&maxHeap, i, size, comparator);

// 	for (int i = size - 1; i >= 0; i--) 
// 	{
// 		swap(&maxHeap.arr[0], &maxHeap.arr[i]);

// 		reheapify(&maxHeap, 0, i, comparator);
// 	}
// }

void sortEdges(Edge* arr, int from, int to, int (*comparator)(Edge, Edge)) // Qsort
{
	if (from >= to)
		return;

	Edge pivot = arr[to];

	int left = from, right = to - 1; // Partitioning
	while (left < right) // Move everything smaller than pivot to left and everything grater to the right...
	{
		for (; left < right && comparator(arr[left], pivot) < 0; left++);

		for (; left < right && comparator(arr[right], pivot) > 0; right--);

		swap(&arr[left], &arr[right]);
	}

	if (comparator(arr[left], arr[to]) > 0) // Edge case when first and last elm are not sorted...
		swap(&arr[left], &arr[to]);
	else
		left = to;

	sortEdges(arr, from, left-1, comparator);
	sortEdges(arr, left+1, to, comparator);
}

void search(Node** graph, int size, int startVert, int* countOfPrints) 
{
	unsigned long long totalWeight = 0;

	EdgeHeap minEdges = {0};
	minEdges.arr = malloc((minEdges.capacity = size) * sizeof(Edge));

	int mstSize = 0;
	Edge* mst = malloc(size * sizeof(Edge));

	byte* visited = calloc(size, sizeof(byte));

	minEdges.arr[minEdges.size++] = (Edge) { -1, 0, startVert };

	for (; minEdges.size && mstSize < size-1; )
	{
		Edge min = popMin(&minEdges, edgeWeightComparator);

		if (visited[min.vert2]) // Was visited
			continue;

		visited[min.vert2] = 1;
		if (min.vert1 != -1)
		{
			totalWeight += min.weight;
			mst[mstSize++] = normalizeEdge(min);
		}

		for (Node* curr = graph[min.vert2]; curr; curr = curr->next) // Find next unvisited verts from graph
		{
			int dest = curr->dest;
			if (!visited[dest]) // Wasnt visited
				insertEdge(&minEdges, (Edge) { min.vert2, curr->weight, dest }, edgeWeightComparator);
		}
	}

	if (!mstSize)
	{
		fail("search", startVert, -2, countOfPrints);
		goto end;
	}

	sortEdges(mst, 0, mstSize-1, edgeVertComparator);

	if ((*countOfPrints)++)
		printf("\n");
	printf("%llu: [", totalWeight);
	for (int i = 0, count = 0; i < mstSize; i++)
	{
		if (count++)
			printf(", ");
		printf("(%d, %d)", mst[i].vert1, mst[i].vert2);
	}
	printf("]");

	end:
	free(visited);
	free(mst);
	free(minEdges.arr);
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
			{
				return 0;
			}
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

int edgeWeightComparator(Edge e1, Edge e2)
{
	return numComparator(e1.weight, e2.weight);
}

int edgeVertComparator(Edge e1, Edge e2)
{
	if (e1.vert1 > e2.vert1)
		return 1;
	if (e1.vert1 < e2.vert1)
		return -1;
	return numComparator(e1.vert2, e2.vert2);
}

// int negEdgeVertComparator(Edge e1, Edge e2)
// {
// 	return -edgeVertComparator(e1, e2);
// }

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
	printf(vert2 < -1 ? "%s %i failed" : "%s %i %i failed", str, vert1, vert2);
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