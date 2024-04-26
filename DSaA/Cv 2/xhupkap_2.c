#include <stdlib.h>
#include <stdio.h>

int isPrime(int x);

int main()
{
	int from, to;
	scanf("%i %i", &from, &to);

	for (int wasOut = 0; from <= to; from++)
	{
		if (isPrime(from))
		{
			if (wasOut)
				printf(", ");
			printf("%i", from);
			wasOut = 1;
		}
	}
}

int isPrime(int x)
{
	if (x <= 1) // 0, 1 are not
		return 0;

	if (x == 2 || x == 3) // 2, 3 are
		return 1;

	if (x % 2 == 0 || x % 3 == 0) // 2, 3 multiples are not
		return 0;

	for (int i = 5; i*i <= x; i++) // others
		if (x % i == 0)
			return 0;
	return 1;
}