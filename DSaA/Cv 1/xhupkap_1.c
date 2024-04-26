#include <stdlib.h>
#include <stdio.h>

typedef unsigned long long hugeInt;

hugeInt gcd(hugeInt, hugeInt);

int main() 
{
	int inCount;
	scanf("%i", &inCount);

	hugeInt* gcds = calloc(inCount, sizeof(hugeInt));
	for (int i = 0; i < inCount; i++)
	{
		hugeInt a, b;
		scanf("%llu %llu", &a, &b);

		gcds[i] = gcd(a, b);
	}

	for (int i = 0; i < inCount; i++)
	{
		if (i)
			printf("\n");
		printf("%llu", gcds[i]);
	}

	free(gcds);
}

hugeInt gcd(hugeInt a, hugeInt b) 
{
	for (hugeInt oldB; b; )
	{
		oldB = b;
		b = a % b;
		a = oldB;
	}
	return a;
}