// Uloha 7.1

#include <stdio.h>
#include <stdlib.h>

#define RECT_SIZE 20

short isMagic(int rect[][RECT_SIZE], int);

int main()
{
	int rect[RECT_SIZE][RECT_SIZE];

	printf("Zadaj stranu stvorca: ");

	int side;
	scanf("%i", &side);

	if (side > RECT_SIZE)
	{
		printf("Strana stvorca nesmie byt vacsia ako %i!", RECT_SIZE);
		return 1;
	}

	for (int y = 0; y < side; y++)
	{
		printf("Zadaj %i prvky %i riadku stvorca:\n", side, y+1);
		for (int x = 0; x < side; x++)
		{
			scanf("%i", &rect[y][x]);
		}
	}

	short result = isMagic(rect, side);
	printf("Stvorec %s magicky!", result ? "je" : "nie je");
}

short isMagic(int rect[][RECT_SIZE], int side)
{
	float sumOfRows = 0, sumOfCols = 0, sumOfLeftDiagonal = 0, sumOfRightDiagonal = 0;
	for (int y = 0; y < side; y++)
		for (int x = 0; x < side; x++)
			sumOfCols += rect[y][x];

	for (int x = 0; x < side; x++)
		for (int y = 0; y < side; y++)
			sumOfRows += rect[y][x];

	for (int i = 0; i < side; i++) 
	{
		sumOfLeftDiagonal += rect[i][i]; 
		sumOfRightDiagonal += rect[side - i - 1][side - i - 1];
	}

	// printf("%f %f %f %f", sumOfRows / side, sumOfCols / side, sumOfLeftDiagonal, sumOfRightDiagonal);
	return sumOfRows / side == sumOfCols / side && sumOfCols / side == sumOfLeftDiagonal && sumOfLeftDiagonal == sumOfRightDiagonal;
}
