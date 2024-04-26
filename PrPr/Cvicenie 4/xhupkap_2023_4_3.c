// Uloha 4.3

#include <stdio.h>
#include <stdlib.h>

long reverzne_cislo(long);

int main()
{
	printf("Zadaj cisla: ");

	long x;
	while (scanf("%li", &x) > 0)
	{
		long reversedX = reverzne_cislo(x);
		printf("Otocene cislo od %i je %li\n", x, reversedX);
		printf("Cislo %i %s palindromom!\n", x, x == reversedX ? "je" : "nie je");
	}
}

long reverzne_cislo(long x)
{
	char str[32];
	int len = sprintf(str, "%li" , x);

	for (int i = 0; i < len/2; i++) //Reverse pola/strnigu
	{
		char tempCh = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = tempCh;
	}

	return atol(str);
}