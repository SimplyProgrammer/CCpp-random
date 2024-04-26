// Uloha 3.3

#include <stdio.h>

int main()
{
	int num; //Pocet nacitanych cisel N

	printf("Zadaj pocet nacitanych cisel: ");
	scanf("%i", &num);

	int validCount = 0; //Pocet nacitanych cisel ktore vspadaju do (0, 100>
	for (int i = 1; i <= num; i++)
	{
		printf("Zadaj %i. cislo: ", i);

		int currentValue;
		scanf("%i", &currentValue);

		if (currentValue > 0 && currentValue <= 100)
			validCount++;
	}

	printf("Pocet cisel v danom intervale: %i\n", validCount);
}