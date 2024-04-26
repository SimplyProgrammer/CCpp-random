#include <stdio.h>
#include <stdlib.h>

#define DECIMAL_PART 11

typedef struct
{
	int whole;
	char decimal[DECIMAL_PART];
} Float;

int cmpFloats(Float, Float);

int indexOf(Float*, int, Float);

int main()
{
	// int countToLoad;
	// scanf("%i", &countToLoad);

	// Float* nums = calloc(countToLoad, sizeof(Float));
	// for (int i = 0; i < countToLoad; i++) // Populate nums...
	// 	scanf("%i,%s", &nums[i].whole, nums[i].decimal);

	// int cmp = cmpFloats(nums[0], nums[1]);
	// printf("%i\n", cmp);

	int countToLoad;
	scanf("%i", &countToLoad);

	Float* nums = calloc(countToLoad, sizeof(Float));
	for (int i = 0; i < countToLoad; i++) // Populate nums...
		scanf("%i,%s", &nums[i].whole, nums[i].decimal);

	// for (int i = 0; i < countToLoad; i++)
	// {
	// 	printf("\t%i %s\n", nums[i].whole, nums[i].decimal);
	// }

	int countToFind;
	scanf("%i", &countToFind);

	int* indexOfFound = calloc(countToFind, sizeof(int));
	for (int i = 0; i < countToFind; i++) // Perform search
	{
		Float valToFind = {0};
		scanf("%i,%s", &valToFind.whole, valToFind.decimal);

		indexOfFound[i] = indexOf(nums, countToLoad, valToFind);
	}

	for (int i = 0; i < countToFind; i++)
	{
		if (i)
			printf("\n");
		printf("%i", indexOfFound[i]+1);
	}

	free(nums);
	free(indexOfFound);
}

int cmpFloats(Float fl1, Float fl2)
{
	if (fl1.whole > fl2.whole)
		return 1;
	if (fl1.whole < fl2.whole)
		return -1;

	int sign = fl1.whole < 0 ? -1 : 1;
	for (int i = 0; i < DECIMAL_PART; i++) // Cmp decimal part
	{
		char ch1 = fl1.decimal[i], ch2 = fl2.decimal[i];
		ch1 = ch1 < '1' ? 0 : ch1; // Solution for trailing 0
		ch2 = ch2 < '1' ? 0 : ch2;

		if (ch1 > ch2)
			return sign;
		if (ch1 < ch2)
			return -sign;
	}

	return 0;
}

int indexOf(Float* nums, int size, Float value) // Bin seacrh
{
	for (int start = 0, end = size - 1; start <= end; ) 
	{
		int mid = start + (end - start) / 2;

		int cmp = cmpFloats(nums[mid], value);
		// printf("\t%i,%s is %s %i,%s (%i)\n", nums[mid].whole, nums[mid].decimal, cmp == 0 ? "equal" : cmp > 0 ? "greater than" : "less than", value.whole, value.decimal, cmp);
		if (cmp == 0) 
			return mid; 

		if (cmp < 0)
			start = mid + 1; 
		else
			end = mid - 1; 
	}

	return -1;
}