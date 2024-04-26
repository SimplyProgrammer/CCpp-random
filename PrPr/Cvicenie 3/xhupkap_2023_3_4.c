// Uloha 3.4

#include <stdio.h>

int factorial(int);

int main()
{
	float num;

	while (1) 
	{
		printf("Zadaj cele cislo vacsie ako 0: ");
		
		scanf("%f", &num);
		if (num > 0 && num / (int) num == 1)
			break;
	}

	printf("Factorial zadaneho cisla je %i!\n", factorial(num));

}

int factorial(int num) {
	for (int i = num; --i > 1;)
		num *= i;
	return num;
}