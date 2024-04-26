// Uloha 4.9

#include <stdio.h>
#include <stdbool.h>

int main()
{
	FILE* file1 = fopen("prvy.txt", "r");
	if (file1 == NULL)
		printf("Subor 1 sa nepodarilo otvorit!\n");

	FILE* file2 = fopen("druhy.txt", "r");
	if (file2 == NULL)
		printf("Subor 2 sa nepodarilo otvorit!\n");

	int countOfDiffrents = 0, lenDiff = 0;
	for (char ch1, ch2; ; )
	{
		bool eof1 = fscanf(file1, "%c", &ch1) == EOF;
		bool eof2 = fscanf(file2, "%c", &ch2) == EOF;
		if (eof1 && eof2) //Both ended
			break;

		if (eof1 ^ eof2) //One ended, other is still going...
			lenDiff++;
		else
			countOfDiffrents += ch1 != ch2;
	}

	printf(countOfDiffrents < 1 ? "Subory su identicke\n" : "Pocet roznych znakov: %i\n", countOfDiffrents);
	if (lenDiff > 0)
		printf("Jeden zo suborov je dlhsi o %i znakov!\n", lenDiff);

	fclose(file1);
	fclose(file2);
}