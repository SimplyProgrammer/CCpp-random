// Uloha 6.3

#include <stdio.h>
#include <stdlib.h>

int** calloc2D(int, int);

int** allocate2DArr(int*, int*); // Alokuj 2d pole z klavesnice
void print2DArr(int**, int, int); // Vypis 2d pole

void free2DArr(int**, int);

int main()
{
	int w, h;
	int** arr = allocate2DArr(&w, &h);

	print2DArr(arr, w, h);

	free2DArr(arr, h);
}

int** calloc2D(int w, int h)
{
	int** arr = calloc(h, sizeof(int*));
	for (int i = 0; i < h; i++)
		arr[i] = calloc(w, sizeof(int));
	return arr;
}

void print2DArr(int** arr, int w, int h)
{
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			printf("%i ", arr[y][x]);
		}
		printf("\n");
	}
}

void free2DArr(int** arr, int h)
{
	for (int y = 0; y < h; y++)
		free(arr[y]);
	free(arr);
}


int** allocate2DArr(int* w, int* h)
{
	printf("Zadaj velkosti 2D pola (w, h): ");
	scanf("%i %i", w, h);

	int** arr = calloc2D(*w, *h);

	for (int y = 0; y < *h; y++)
		for (int x = 0; x < *w; x++)
		{
			printf("Zadaj (%i %i) prvok: ", x, y);
			scanf("%i", &arr[y][x]);
		}

	return arr;
}