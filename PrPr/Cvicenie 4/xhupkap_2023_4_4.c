// Uloha 4.4

#include <stdio.h>
#include <stdlib.h>

int sumOfOdds(int, int, int);

int main()
{
	printf("Zadaj cele cislo: ");

	int num;
	scanf("%li", &num);

	printf("%i\n", sumOfOdds(0, num, 0));
}

int sumOfOdds(int from, int to, int sum)
{
	if (from >= to)
		return sum;
	if (from % 2 != 0)
		sum += from;
	sumOfOdds(++from, to, sum);
}