//1.8

#include <stdio.h>

int main()
{
	printf("Zadaj velkost kvadra s medzerami: ");

	float width, height, depth;
	scanf("%f %f %f", &width, &height, &depth);

	printf("Objem: %.3f\n", width * height * depth);
}