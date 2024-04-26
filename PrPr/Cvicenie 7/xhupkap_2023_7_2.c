// Uloha 7.2

#include <stdio.h>
#include <stdlib.h>

int** calloc2D(int, int);
void printSnake(int**, int, int);
void reverse(int*, int);
void free2DArr(int**, int);

int main()
{
	printf("Zadaj stranu stvorca z hadikom: ");

	int side;
	scanf("%i", &side);

	int** snakeMatrix = calloc2D(side, side);
	for (int y = 0; y < side; y++)
	{
		for (int x = 0; x < side; x++)
			snakeMatrix[y][x] = ('a' + (x+y*side) % ('z'-'a'+1));

		if (y % 2 != 0)
			reverse(snakeMatrix[y], side);
	}

	printSnake(snakeMatrix, side, side);

	free2DArr(snakeMatrix, side);
}

int** calloc2D(int w, int h)
{
	int** arr = calloc(h, sizeof(int*));
	for (int i = 0; i < h; i++)
		arr[i] = calloc(w, sizeof(int));
	return arr;
}

void printSnake(int** arr, int w, int h)
{
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
			printf("%c ", (char) arr[y][x]);

		printf("\n");
	}
}

void reverse(int* arr, int len)
{
	for (int i = 0; i < len/2; i++)
	{
		int tempCh = arr[i];
		arr[i] = arr[len - i - 1];
		arr[len - i - 1] = tempCh;
	}
}

void free2DArr(int** arr, int h)
{
	for (int y = 0; y < h; y++)
		free(arr[y]);
	free(arr);
}
