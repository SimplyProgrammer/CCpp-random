// Uloha 5.2

#include <stdio.h>

int* maximum(int a, int b);

float main()
{
	printf("Zadaj 2 cele cisla: ");

	int a, b;
	scanf("%i %i", &a, &b);

	printf("Cislo %i je vacsie.\n", *maximum(a, b));
}

int* maximum(int a, int b)
{
	return a > b ? &a : &b;
}