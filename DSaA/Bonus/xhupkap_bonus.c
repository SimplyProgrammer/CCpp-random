#include <stdio.h>

int main()
{
	int missing = 0, count = 0;
	for (int num; scanf("%i", &num) != EOF; count++)
		missing ^= num;

	int mask = 0;
	for (int i = -count/4; i <= 3*count/4; i++)
		mask ^= i;

	printf("%i", missing ^ mask);
}