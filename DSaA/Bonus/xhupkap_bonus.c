#include <stdio.h>

int xorifyRange(int, int);

int main()
{
	int missing = 0, count = 0;
	for (int num; scanf("%i", &num) != EOF; count++)
		missing ^= num;

	int mask = xorifyRange(-count/4, 3*count/4); // Evil xor trick...
	printf("%i", missing ^ mask);
}

int xorifyRange(int from, int to) // Abusing reacuring nature of xor series where 1 repeats at every 4 place (% 4) and 0 as well offseted by 2...
{
	// int mask = from;
	// for (from++; from <= to; from++)
	// 	mask ^= from;
	// return mask;

	int rangeDifMod = (to - from) % 4; // Adjusting for range (faster than loop)
	if (rangeDifMod == 0)
		return to;
	if (rangeDifMod == 1)
		return 1;
	if (rangeDifMod == 2)
		return to + 1;
	return 0; // rangeDifMod == 3
}