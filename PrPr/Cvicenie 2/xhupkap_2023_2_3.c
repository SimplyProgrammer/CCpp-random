// Uloha 2.3

#include <stdio.h>

int main()
{
	printf("Zadaj cislo: ");

	float num;
	scanf("%f", &num);

	int inum = num;
	int inumCeil = num / inum > 1 ? inum + 1 : inum;

	printf("%i %i\n", inum, inumCeil);
}