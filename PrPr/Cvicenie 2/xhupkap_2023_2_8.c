// Uloha 2.8

#include <stdio.h>


int main()
{
	int a, b, c, d, e;

	//Ukazka 1
	printf("Ukazka 1:\nNapis 5 cisla odelene medzerov: ");
	scanf("%i %i %i %i %i", &a, &b, &c, &d, &e);

	// Vyraz ukazky 1
	/* 
		--a = decrementuje premennu o 1 az potom vrati jej hodnotu
		b++ a c++ vratia povodnu hodnotu premennych az potom b c incrementuje o 1
		nasledne cely vyraz vypocita z lava do prava nakolko operacie su rovnocenne a vysledo vrati
	*/
	printf("Vystup pre ukazku 1: %i\n", e / --a * b++ / c++);

	//Ukazka 2
	printf("Ukazka 2:\nNapis 5 cisla odelene medzerov: ");
	scanf("%i %i %i %i %i", &a, &b, &c, &d, &e);

	// Vyraz ukazky 2
	/*
		ako prve vyrata vyraz e / 2 nasledne jeho hodnotu pripocita k 1, z vysledom dalej pracuje...
		vysledok tejto operacie nasledne priradi do premennych b a d
		nasledne tym istym vysledkom moduluje premennu a (a % ten vysledok) a tuto hodnotu nasledne ulozi spatne do a pricom ju aj vrati
	*/
	printf("Vystup pre ukazku 1: %i\n", a %= b = d = 1 + e / 2);
}