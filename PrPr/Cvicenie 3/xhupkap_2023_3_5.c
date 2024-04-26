// Uloha 3.5

#include <stdio.h>

int main()
{
	int f, g;
	printf("Zadaj interval <f,g> kde f, g su cele cisla: ");
	scanf("%i %i", &f, &g);

	for (; f <= g; f++) 
	{
		if (f % 3 == 0)
			printf("%i ", f);
	}

	printf("\n");
}