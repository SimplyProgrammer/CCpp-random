//1.5

#include <stdio.h>

#define PI 3.14

int main()
{
	float r;

	printf("Napis polomer kruhu: ");
	scanf("%f", &r);

	printf("Obvod kruhu s polomerom %.2f je: %.2f\n", r, 2 * PI * r);
}