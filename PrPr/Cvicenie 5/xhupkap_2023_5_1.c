// Uloha 5.1

#include <stdio.h>

void nacitaj(float*, float*);
void vypocitaj(float, float, float*, float*);

float main()
{
	float w, h, obvod, obsah;
	nacitaj(&w, &h);
	vypocitaj(w, h, &obvod, &obsah);

	printf("Obsah %.3f\nObvod: %.3f\n", obsah, obvod);
}

void nacitaj(float* w, float* h)
{
	printf("Zadaj sirku a vysku: ");
	scanf("%f %f", w, h);
}

void vypocitaj(float w, float h, float* obvod, float* obsah)
{
	*obvod = w*2 + h*2;
	*obsah = w * h; 
}