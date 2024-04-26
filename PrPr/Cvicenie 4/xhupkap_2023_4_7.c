// Uloha 4.7

#include <stdio.h>

int main()
{
	FILE* file = fopen("cisla.txt ", "r");
	if (file == NULL)
		printf("Subor cisla.txt nemozno otvorit!\n");

	float total = 0;
	for (float num; fscanf(file, "%f", &num) != EOF; ) {
		printf("%g\n", num);

		total += num;
	}
	printf("Sucet cisel je: %g\n", total);

	fclose(file);
}