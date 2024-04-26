//1.7

#include <stdio.h>

int main()
{
	printf("Zadaj cenu: ");

	int value;
	scanf("%i", &value);

	printf("Cena bez dane: %i\nCena z danou 20%: %.2f\n", value, value * 1.2);
}