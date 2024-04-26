// Uloha 3.7

#include <stdio.h>
#include <math.h>

void mocnina(double, int);

int main()
{
	double num;
	int count;
	printf("Zadaj 1 realne a 1 cele cislo cislo: ");
	scanf("%lf %i", &num, &count);

	mocnina(num, count);
}

void mocnina(double num, int count) 
{
	for (int i = 1; i <= count; i++)
	{
		printf("%.2f^%i = %.2f\n", num, i, pow(num, i));
	}
}