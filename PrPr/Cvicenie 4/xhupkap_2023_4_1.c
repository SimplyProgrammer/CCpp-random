// Uloha 4.1

#include <stdio.h>

int zisti_prvocislo(int);

int main()
{
	printf("Zadaj 2 cele cisla odelene mezderov <a, b>: ");

	int from, to;
	scanf("%i %i", &from, &to);

	printf("Prvocisla z daneho intervalu:\n");

	int primeCount = 0;
	for (; from <= to; from++)
	{
		int flag = zisti_prvocislo(from);
		if (flag > 0) 
		{
			printf("%i\n", from);
			primeCount++;
		}
	}
	if (primeCount < 1)
		printf("Neexsituju!\n");
}

int zisti_prvocislo(int cislo) 
{
	if (cislo <= 1) //0 a 1 = nie prvocisla
		return -1;

	if (cislo == 2 || cislo == 3) // najpravdepodobnejsie
		return 1;

	for (int i = 2; i*i <= cislo; i++) //ostatne
		if (cislo % i == 0)
			return -1;
	return 1;
}