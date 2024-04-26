// Uloha 2.1

#include <stdio.h>

int main()
{
	printf("Zadaj 3 cisla odelene medzerami: ");

	float x, y, z, p;
	scanf("%f %f %f", &x, &y, &z);
	p = (x + y + z) / 3;

	printf("Priemer cisel: %g\n", p);
}