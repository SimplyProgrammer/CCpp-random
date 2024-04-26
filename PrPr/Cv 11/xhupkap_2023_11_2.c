//11.2

#include <stdio.h>

unsigned int invert(unsigned int num, int from, int to) 
{
	if (from < 0 || to > 32)
		return num;

	unsigned int mask = 0xffffffff; // Create unsigned int where all bits are 1, bitshift it in a way that there are from 0 from left and to zeros from right
	mask = mask >> from + to; // from left
	mask = mask << to; // from right

	return num ^ mask; // Xor num with mask which will invert the bits within masks...
}

int main()
{
	unsigned int num;
	int from, to;
	scanf("%i %i %i", &num, &from, &to);

	printf("%i\n", invert(num, from, to));
}