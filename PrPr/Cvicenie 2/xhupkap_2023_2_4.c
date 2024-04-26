// Uloha 2.4

#include <stdio.h>

int main()
{
	char ch1, ch2;

	printf("Napis 2 pismena: ");
	scanf("%c %c", &ch1, &ch2);
	ch1 &= '_';
	ch2 &= '_';

	printf("%C %i\n%C %i\n", ch1, ch1, ch2, ch2);
}