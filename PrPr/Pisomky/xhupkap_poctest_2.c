// Peter Hupka xhupka - pisomka 2

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define percentualDiff(a, b) (((b) * 100) / (a))-100

#define sign(val) ((val) > 0) ? 1 : -1

#define isInRange(val, diviation) ((val) * sign(val)) <= (diviation)

void _x(double*);
void _j(char**, char**, double*);

#define Pocet_Zaznamov 30 //nemenit
int main() {
	char** pole_ID_MM = NULL;      //ID mer. modul
	char** pole_Typ_MV = NULL;     //typ mer. veliciny
	char** pole_DM = NULL;      //Datum merania
	char** pole_CM = NULL;      //cas merania
	double* hodnota;
	char* pole[] = { "0905", "0915",  "0925", "0935", "0945", "1005", "1405", "1505" ,"1605" ,"1905" };
	char* pole1[] = { "20201030", "20201030",  "20211030", "20211030", "20211130", "20211130", "20211130", "20211212" ,"20211212" ,"20211212" };

	int i = 0, j = 0, r = 1;


	hodnota = (double*)malloc(Pocet_Zaznamov * sizeof(double));
	for (i = 0; i < Pocet_Zaznamov; i++) {
		if (i < Pocet_Zaznamov / 3) hodnota[i] = 100.255 + (i * 8.358);
		else if (i < Pocet_Zaznamov * 2 / 3) hodnota[i] = 10.255 + (i * 17.358);
		else hodnota[i] = (i * 11.358);;
	}

	pole_ID_MM = (char**)malloc(Pocet_Zaznamov * sizeof(char*));
	for (i = 0; i < Pocet_Zaznamov; i++) {
		pole_ID_MM[i] = (char*)malloc(6 * sizeof(char));
		if (i < Pocet_Zaznamov / 3)  strcpy(*(pole_ID_MM + i), "A111a");
		else if (i < Pocet_Zaznamov * 2 / 3) strcpy(*(pole_ID_MM + i), "A211b");
		else strcpy(*(pole_ID_MM + i), "B111a");
	}

	pole_Typ_MV = (char**)malloc(Pocet_Zaznamov * sizeof(char*));
	for (i = 0; i < Pocet_Zaznamov; i++) {
		pole_Typ_MV[i] = (char*)malloc(3 * sizeof(char));
		if (r == 1) { strcpy(*(pole_Typ_MV + i), "RM"); r = 2; }
		else if (r==2) {strcpy(*(pole_Typ_MV + i), "RO"); r = 3;}
		else {strcpy(*(pole_Typ_MV + i), "RD"); r = 1;}
	}

	pole_DM = (char**)malloc(Pocet_Zaznamov * sizeof(char*));
	for (i = 0, j = 0; i < Pocet_Zaznamov; i++) {
		pole_DM[i] = (char*)malloc(9 * sizeof(char));
		if (i < Pocet_Zaznamov / 3) { strcpy(*(pole_DM + i), pole1[j]); j++; }
		else if (i < Pocet_Zaznamov * 2 / 3) { j--; strcpy(*(pole_DM + i), pole1[j]); }
		else { strcpy(*(pole_DM + i), pole1[j]); j++; }
	}

	pole_CM = (char**)malloc(Pocet_Zaznamov * sizeof(char*));
	for (i = 0, j = 0; i < Pocet_Zaznamov; i++) {
		pole_CM[i] = (char*)malloc(5 * sizeof(char));
		if (i < Pocet_Zaznamov / 3) { strcpy(*(pole_CM + i), pole[j]); j++; }
		else if (i < Pocet_Zaznamov * 2 / 3) { j--; strcpy(*(pole_CM + i), pole[j]); }
		else { strcpy(*(pole_CM + i), pole[j]); j++; }
	}


	//vypis
	for (i = 0; i < Pocet_Zaznamov; i++) {
		printf("%3d %s %s %s %s \t%f\n", i, pole_ID_MM[i], pole_Typ_MV[i], pole_DM[i], pole_CM[i], hodnota[i]);

	}

	//vase riesenia / your solution

	// _j(pole_ID_MM, pole_Typ_MV, hodnota);

	_x(hodnota);

	//uvolnenie poli
	for (i = 0; i < Pocet_Zaznamov; i++) {
		free(*(pole_ID_MM + i));
		*(pole_ID_MM + i) = NULL;
		free(*(pole_Typ_MV + i));
		*(pole_Typ_MV + i) = NULL;
		free(*(pole_DM + i));
		*(pole_DM + i) = NULL;
		free(*(pole_CM + i));
		*(pole_CM + i) = NULL;
	}
	free(pole_ID_MM);
	pole_ID_MM = NULL;
	free(pole_Typ_MV);
	pole_Typ_MV = NULL;
	free(pole_DM);
	pole_DM = NULL;
	free(pole_CM);
	pole_CM = NULL;
	free(hodnota);
	hodnota = NULL;

	return 0;
}

void _x(double* hodnota)
{
	int k;
	while (1) // Load k, ensure it is in selected interval...
	{
		scanf("%i", &k);
		if (k >= 1 && k <= 6)
			break;
	}
	
	int numCounts[10] = {0};
	printf("Pole hodnot:\n");
	for (int i = 0; i < Pocet_Zaznamov; i+=k)
	{
		char str[32];
		int len = sprintf(str, "%lf" , hodnota[i]); //Convert num to string, max alloved lenght is 32 digits... 

		strtok(str, ".");
		char* decimalPart = strtok(NULL, "."); // Obtain decimal part

		// Count cifers in selected range...
		for (int j = 1; j < 4; j++)
			numCounts[decimalPart[j]  - '0']++;
		printf("%lf\n", hodnota[i]);
	}

	// Print histogram...
	printf("Cislice:   ");
	for (int i = 0; i < 10; i++)
		if (numCounts[i])
			printf("%i ", i);
	printf("\n");

	printf("Pocetnost: ");
	for (int i = 0; i < 10; i++)
		if (numCounts[i])
			printf("%i ", numCounts[i]);
	printf("\n");
}

void _j(char** pole_ID_MM, char** pole_Typ_MV, double* hodnota)
{
	char ids[2][6], type[3];
	scanf("%s %s %s", ids[0], ids[1], type);

	double maxValue[2] = {0}, minValue[2] = {0}, sums[2] = {0}, countOfIds[2] = {0};
	for (int id = 0; id < 2; id++) //Find initial values for min, max
		for (int i = 1; i < Pocet_Zaznamov; i++)
			if (strcmp(pole_ID_MM[i], ids[id]) == 0)
			{
				minValue[id] = maxValue[id] = hodnota[i];
				break;
			}

	for (int i = 0; i < Pocet_Zaznamov; i++) //Clack mins maximums, counts and sums for ids
	{
		if (strcmp(pole_Typ_MV[i], type) == 0)
		{
			int j;
			for (int id = 0; id < 2; id++)
			{
				if (strcmp(pole_ID_MM[i], ids[id]) == 0)
				{
					j = id;
					break;
				}
			}

			if (hodnota[i] > maxValue[j])
				maxValue[j] = hodnota[i];
			if (hodnota[i] < minValue[j])
				minValue[j] = hodnota[i];

			sums[j] += hodnota[i];
			countOfIds[j]++;
		}
	}

	//Printing
	for (int id = 0; id < 2; id++)
		printf("%s    min. hodnota %lf    stredna hodnota %lf    max hodnota %lf\n", ids[id], minValue[id], sums[id]/countOfIds[id], maxValue[id]);

	if (countOfIds[0] && countOfIds[1])
	{
		double avgOfId1 = sums[0]/countOfIds[0], avgOfId2 = sums[1]/countOfIds[1];

		double prMin[2] = {percentualDiff(minValue[0], avgOfId1), percentualDiff(minValue[1], avgOfId2)};
		double prMax[2] = {percentualDiff(maxValue[0], avgOfId1), percentualDiff(maxValue[1], avgOfId2)};

		double prs1 = percentualDiff(avgOfId1, avgOfId2);
		double prs2 = percentualDiff(avgOfId2, avgOfId1);

		printf("%lf %lf, %f %f | %lf %lf", prMin[0], prMax[0], prMin[1], prMax[1], prs1, prs2);

		if (isInRange(prMin[0], 15) && isInRange(prMin[1], 15) && isInRange(prMax[0], 15) && isInRange(prMax[1], 15) && isInRange(prs1, 15) && isInRange(prs2, 15))
			printf("%s %s su v standardnej odchilke.\n",  ids[0], ids[1]);
		else
			printf("%s %s prektacuju limit povoleneho rozmedzia.\n", ids[0], ids[1]);
		return;
	}

	printf("%s %s sa nemozu porovnavat.\n", ids[0], ids[1]);
}