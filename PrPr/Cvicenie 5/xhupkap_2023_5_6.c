// Uloha 5.6

#include <stdio.h>
#include <stdlib.h>

int* allocate1DArr(int*); // Alokuj 1d pole z klavesnice
void print1DArr(int*, int); // Vypis 1d pole

// Indexy pre max a min
int indexOfMax(int*, int);
int indexOfMin(int*, int);

float main()
{
	int size;
	int* arr = allocate1DArr(&size);

	print1DArr(arr, size);

	int maxIndex = indexOfMax(arr, size), minIndex = indexOfMin(arr, size);
	printf("Najvacsi prvok %i je na indexe %i\n", arr[maxIndex], maxIndex);
	printf("Najmensi prvok %i je na indexe %i\n", arr[minIndex], minIndex);

	free(arr);
}

int* allocate1DArr(int* size)
{
	printf("Zadaj velkost pola (1 a viac): ");

	scanf("%i", size);

	int* arr = malloc(*size * sizeof(int));

	for (int i = 0; i < *size; i++)
	{
		printf("Zadaj %i. prvok: ", i + 1);

		scanf("%i", &arr[i]);
	}
	return arr;
}

void print1DArr(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (i > 0)
			printf(",");
		printf("%i", arr[i]);
	}
	printf("\n");
}

int indexOfMax(int* arr, int size)
{
	int max = arr[0], iMax;
	for (int i = 1; i < size; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
			iMax = i;
		}
	}
	return iMax;
}

int indexOfMin(int* arr, int size)
{
	int min = arr[0], iMin;
	for (int i = 1; i < size; i++)
	{
		if (arr[i] < min)
		{
			min = arr[i];
			iMin = i;
		}
	}
	return iMin;
}