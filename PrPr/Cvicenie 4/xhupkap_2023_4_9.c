// Uloha 4.9

#include <stdio.h>

int main()
{
	FILE* in = fopen("text.txt", "r");
	if (in == NULL)
		printf("Vstupny subor sa nepodarilo otvorit!\n");

	int spaceCount = 0;
	for (char ch; fscanf(in, "%c", &ch) != EOF; )
	{
		if (ch == '*')
		{
			printf("Koniec!\n");
			break;
		}

		if (ch == ' ')
			spaceCount++;
		else if (ch == '#' || ch == '$' || ch == '&')
			printf("Precital som riadiaci znak\n");
		else if ((ch &= '_') == 'X' || ch == 'Y')
			printf("Precital som %C\n", ch);
	}

	printf("Pocet medzier: %i\n", spaceCount);

	fclose(in);
}