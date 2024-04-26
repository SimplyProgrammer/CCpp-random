// Uloha 4.8

#include <stdio.h>

int main()
{
	printf("Zadaj znak: ");

	char ch;
	scanf("%c", &ch);

	FILE* in = fopen("znaky.txt", "r");
	if (in == NULL)
		printf("Vstupny subor sa nepodarilo otvorit!\n");

	FILE* out = stdout;

	if (ch == 's')
	{
		out = fopen("novy.txt", "w");
		if (out == NULL)
			printf("Vystupny subor sa nepodarilo otvorit!\n");
	}
	
	for (char str[256]; fscanf(in, "%s", str) != EOF; ) 
	{
		fprintf(out, "%s\n", str);
	}

	fclose(in);
	fclose(out);
}