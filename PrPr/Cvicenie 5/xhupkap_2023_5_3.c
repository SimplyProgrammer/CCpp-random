// Uloha 5.3

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float* kvadraticka_rovnica(float, float, float, int*);

float main()
{
	printf("Zadaj 3 cisla: ");

	float a, b, c;
	scanf("%f %f %f", &a, &b, &c);

	int countOfResults;
	float* results = kvadraticka_rovnica(a, b, c, &countOfResults);
	printf("Pocet rieseni: %i\n", countOfResults);
	if (countOfResults > 0)
		printf("1. riesenie: %f\n", results[0]);
	else
		printf("Nema realne riesenia alebo nie je kvadraticka!\n");
	if (countOfResults > 1)
		printf("2. riesenie: %f\n", results[1]);
}

float* kvadraticka_rovnica(float a, float b, float c, int* countOfResults)
{
	double discriminant = b*b - 4*a*c;

	if (discriminant < 0 || a == 0)
	{
		*countOfResults = 0;
		return 0;
	}

	float* results = malloc(sizeof(float));
	if (discriminant == 0)
	{
		*countOfResults = 1;

		results[0] = -b / 2*a;
		return results;
	}

	*countOfResults = 2;

	results = malloc(sizeof(float) * 2);
	for (int i = 0; i < 2; i++)
		results[i] = (i ? -b - sqrt(discriminant) : -b + sqrt(discriminant))/(2*a);
	return results;
}