// Uloha 5.4

#include <stdio.h>

#define printPointerAndValue(num) printf("%p: %i\n", num, *num);

void vymen_pointre(int*, int*);

float main()
{
	int a = 10, b = 14;

	printPointerAndValue(&a);
	printPointerAndValue(&b);

	vymen_pointre(&a, &b);

	printPointerAndValue(&a);
	printPointerAndValue(&b);
}

void vymen_pointre(int* num1, int* num2)
{
	int tmp = *num1;
	*num1 = *num2;
	*num2 = tmp;
}