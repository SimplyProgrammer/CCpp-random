// Uloha 5.5

#include <stdio.h>

int delitele(int x[], int pocetx, int y[], int k);

float main()
{
	const int k = 24;

	int x[] = {4, 7, 10, 2, 3, 9, 6, 5, 8, 12};
	int y[99]; // Should be enough

	int pocetx = 10;
	int pocety = delitele(x, pocetx, y, k);

	printf("pocety: %i\n", pocety);

	for (int i = 0; i < pocety; i++) // test vypis
	{
		printf("%i\n", y[i]);
	}
}

int delitele(int x[], int pocetx, int y[], int k) 
{
	int j = 0;
	for (int i = 0; i < pocetx; i++)
	{
		if (k % x[i] == 0)
			y[j++] = x[i];
	}
	return j;
}