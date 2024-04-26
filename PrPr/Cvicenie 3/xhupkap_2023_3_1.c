// Uloha 3.1

#include <stdio.h>

int main()
{
	int num; //Pocet nacitanych cisel N

	printf("Zadaj pocet nacitanych cisel: ");
	scanf("%i", &num);

	float min = num, max = num;
	for (int i = 1; i <= num; i++)
	{
		printf("Zadaj %i. cislo: ", i);

		float currentValue;
		scanf("%f", &currentValue);

		if (currentValue < min)
			min = currentValue;

		if (currentValue > max)
			max = currentValue;
	}

	printf("Minimum: %.2f\n", min);
	printf("Maximum: %.2f\n", max);
}