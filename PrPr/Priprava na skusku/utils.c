#include <stdio.h>

int min(int* arr, int len) // 14. Implementacia prototypu
{
	int min = arr[0];
	for (int i = 1; i < len; i++)
		if (arr[i] < min)
			min = arr[i];
	return min;
}