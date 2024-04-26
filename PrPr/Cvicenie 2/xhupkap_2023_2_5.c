// Uloha 2.5

#include <stdio.h>

int main()
{
	printf("Napis 2 cisla odelene medzerov: ");

	int c1, c2;
	scanf("%i %i", &c1, &c2);

	if (c1 == c2)
		printf("Cislo c1=%i je rovne c2=%i\n", c1, c2);
	else
		printf(c1 > c2 ? "Cislo c1=%i je vacsie ako c2=%i\n" : "Cislo c1=%i je mensie ako c2=%i\n", c1, c2);
}