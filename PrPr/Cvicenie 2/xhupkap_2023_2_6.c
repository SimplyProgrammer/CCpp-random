// Uloha 2.6

#include <stdio.h>


int main()
{
	printf("Napis 2 cisla a znamienko odelene medzerov: ");

	int c1, c2;
	char op;
	scanf("%i %i %c", &c1, &c2, &op);

	if (op == '*')
		printf("%i %c %i = %i\n", c1, op, c2, c1 * c2);
	else if (op == '/')
		printf("%i %c %i = %i\n", c1, op, c2, c1 / c2);
	else if (op == '+')
		printf("%i %c %i = %i\n", c1, op, c2, c1 + c2);
	else if (op == '-')
		printf("%i %c %i = %i\n", c1, op, c2, c1 - c2);
	else
		printf("Zle zadana volba! %c je neplatna operacia!\n", op);
}