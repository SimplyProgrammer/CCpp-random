// Uloha 3.8

#include <stdio.h>

void nasobok(double, int);
double multiply(double num, int multiple);

int main()
{
	double num;
	int count;
	printf("Zadaj 1 realne a 1 cele cislo cislo: ");
	scanf("%lf %i", &num, &count);

	nasobok(num, count);
}

void nasobok(double num, int count) 
{
	for (int i = 1; i <= count; i++)
	{
		printf("%.2f * %i = %.2f\n", num, i, multiply(num, i));
	}
}

double multiply(double num, int multiple) 
{
	double multiplied = 0;
	for (; multiple > 0; multiple--)
		multiplied += num;
	return multiplied;
}