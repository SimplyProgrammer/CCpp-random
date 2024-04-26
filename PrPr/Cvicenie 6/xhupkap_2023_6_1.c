// Uloha 6.1

#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("Zadaj velkost slova: ");

	int size;
	scanf("%i", &size);

	printf("Zadaj slovo: ");

	char* word = malloc(size * sizeof(char));
	scanf("%s", word);

	for (int i = size-1; i >= 0; i--)
		printf("%c", *(word + i));
	printf("\n");

	free(word);
}