// Uloha 3.2

#include <stdio.h>
#include <stdbool.h>

#define COUNT 11 //Pocet naciatnych cisel

bool isValid(int inums[]);

int main()
{
	int inums[COUNT]; //Pole celych cisel o velkosti COUNT

	for (int i = 0; i < COUNT; i++)
	{
		printf("Zadaj %i. cele cislo: ", i+1);

		scanf("%i", &inums[i]);
	}

	//Validacia
	printf(isValid(inums) ? "Postupnost je spravna!\n" : "Postupnost nie je spravna!\n");
}

bool isValid(int inums[]) {
	if (!(inums[0] >= 0 && inums[0] <= 10)) //Valid pre 1. prvok
		return false;
	for (int i = 1; i < COUNT; i++)
		if (inums[i] > inums[i-1] * 2 || inums[i] < inums[i-1] / 2) //Valid pre i-ty prvok
			return false;
	return true;
}