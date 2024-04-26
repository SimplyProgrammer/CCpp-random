// Uloha 2.2

#include <stdio.h>

int main()
{
	printf("Zadaj 2 cisla odelene mezderov (cm, kg): ");

	float mass, height, bpi;
	scanf("%f %f", &height, &mass);

	height /= 100; //cm 2 m
	bpi = mass / (height * height);

	printf("Priemer cisel: %.3f\n", bpi);
}