// Peter Hupka

#include <stdio.h>

// Argumenty pre funkcie
#define NUM_BOTTOM_INTERVAL 1
#define NUM_UPPER_INTERVAL 15
#define NUM_TYPE 'l'

#define OUT_TYPE 'O'
#define IMG_SIZE 5

#define oddEven(ch) (ch == 'P' ? "parne" : (ch == 'N' ? "neprarne" : ""))

// Prototypes
int NacitajCislo(int, int, char);
void generateImage(FILE* into, int);
int Vykreslenie(char, int);

int main()
{
	int num = NacitajCislo(NUM_BOTTOM_INTERVAL, NUM_UPPER_INTERVAL, NUM_TYPE);
	printf(num ? "Nacitanie prebehlo uspesne, z intervalu <%i,%i> vyberam %s cislo : %i\n" : "Neuspesne nacitanie!\n", NUM_BOTTOM_INTERVAL, NUM_UPPER_INTERVAL, oddEven(NUM_TYPE), num);

	int isValid = Vykreslenie(OUT_TYPE, IMG_SIZE);
	printf(isValid ? "Vykreslenie prebehlo uspesne.\n" : "Neuspesne vykreslenie!\n");
}


int NacitajCislo(int N, int M, char znak)
{
	if (N > M || !(znak == 'P' || znak == 'N')) //Validation
		return 0;

	printf("Zadaj %s cele cislo z intervalu <%i,%i>:\n", oddEven(znak), N, M);

	for (int num; ; )
	{
		scanf("%i", &num);

		if (num == 0)
			continue;

		if (num < N || num > M)
			continue;

		if (znak == 'N')
		{
			if (num % 3 == 0)
				return num;
		}
		else //P
		{
			if (num % 2 == 0)
				return num;
		}
	}
}

void generateImage(FILE* into, int size)
{
	for (int y = 0; y < size; y++)
	{
		if (y == 0 || y >= size-1) //First and last row
		{
			for (int x = 0; x < size; x++)
				printf("x");
			printf("\n");
		}
		else 
		{
			for (int x = 0; x < size; x++)
				printf(x == 0 || x >= size-1 ? "x" : "-");
			printf("\n");
		}
	}
}

int Vykreslenie(char op, int size) //Validation
{
	if (size < 1 || !(op == 'O' || op == 'T'))
		return 0;

	FILE* output = stdout;

	if (op == 'T')
	{
		output = fopen("PT1.txt", "w");
		if (output == NULL)
			return 0;
	}

	generateImage(output, size);

	if (op == 'T')
		fclose(output);
	return 1;
}