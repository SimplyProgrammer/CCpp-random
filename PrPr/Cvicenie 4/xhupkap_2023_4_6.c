// Uloha 4.6

#include <stdio.h>

int main()
{
	printf("Zadaj cislo: ");

	double num;
	scanf("%lf", &num);

	FILE* file = fopen("nasobky.txt ", "w");
	if (file == NULL)
		printf("Subor nemozno otvorit/vytovirt!\n");

	for (int i = 1; i <= 10; i++)
	{
		fprintf(file, "%i * %.2f = %.2f\n", i, num, num * i);
	}

	fclose(file);
}