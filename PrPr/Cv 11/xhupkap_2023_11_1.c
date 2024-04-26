//11.1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Types
typedef FILE* File;
typedef char* String;

#define println(str) printf(str); printf("\n");

#define null NULL

#define LADENIE_ZAKLADNE
#define LADENIE_PODROBNE

int main() 
{
	#if defined(LADENIE_ZAKLADNE)
		println("Otvorenie suboru");
	#endif

	File file = fopen("suma.txt", "r");
	if (!file)
	{
		#if defined(LADENIE_PODROBNE)
			println("Subor sa nepodarilo otvorit");
		#endif
		return 1;
	}

	#if defined(LADENIE_PODROBNE)
		println("Subor otvoreny");
	#endif


	#if defined(LADENIE_ZAKLADNE)
		println("Kontrola sumy");
	#endif

	double expextedSum;
	fscanf(file, "%lf", &expextedSum);

	double sum;
	for (double num; fscanf(file, "%lf", &num) != EOF; )
	{
		sum += num;
		#if defined(LADENIE_PODROBNE)
			printf("Sucet: %g\n", sum);
		#endif
	}

	#if defined(LADENIE_ZAKLADNE)
		println(expextedSum == sum ? "Suma je spravna" : "Suma je nespravna");
	#endif

	#if defined(LADENIE_PODROBNE)
		println("Suma skontrolovana");
	#endif

	#if defined(LADENIE_ZAKLADNE)
		println("Zatvaranie suboru");
	#endif

	#if defined(LADENIE_PODROBNE)
		if (fclose(file) == 0)
		{
			println("Subor zatvoreny");
		}
		else
		{
			println("Subor sa nepodarilo uzatvorit");
			return 1;
		}
	#endif
}