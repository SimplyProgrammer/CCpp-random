// Uloha 3.6

#include <stdio.h>

void printFactorialSequence(int);

int main()
{
	int num;
	printf("Zadaj cele cislo z intervalu <1, 15>: ");
	scanf("%i", &num);

	if (num < 1 || num > 15)
	{
		printf("Cislo nie je z daneho intervalu!\n");
		return 0;
	}

	for (int i = num; i >= 1; i--) 
	{
		printf("%i: ", i);
		printFactorialSequence(i);
		printf("\n");
	}
}

void printFactorialSequence(int num) 
{
	for (; num >= 1; num--)
		printf("%i ", num);
}