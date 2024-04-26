// Uloha 4.5

#include <stdio.h>
#include <stdlib.h>

int sumOfDigitsFromStdin(int);

int main()
{
	printf("Zadaj cele cislo: ");
	printf("Sucet cislis: %i\n", sumOfDigitsFromStdin(0));
}

int sumOfDigitsFromStdin(int sum)
{
	char ch = getchar();
	if (ch != '\n') {
		sum += ch - '0';
		return sumOfDigitsFromStdin(sum);
	}
	return sum;
}