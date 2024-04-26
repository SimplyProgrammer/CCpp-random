// Uloha 3.9

#include <stdio.h>

int parne(int x[], int, int y[]);

int main()
{
	int x[] = {4, 7, 1, 3, 2, 5, 6};
	int y[99];

	int pocetx = 7;
	int pocety = parne(x, pocetx, y); // volanie funkcie

	printf("pocety: %i\n", pocety);

	for (int i = 0; i < pocety; i++) // test vypis
	{
		printf("%i\n", y[i]);
	}
}

int parne(int x[], int pocetx, int y[]) 
{
	int j = 0;
	for (int i = 0; i < pocetx; i++)
	{
		if (x[i] % 2 == 0)
			y[j++] = x[i];
	}
	return j;
}