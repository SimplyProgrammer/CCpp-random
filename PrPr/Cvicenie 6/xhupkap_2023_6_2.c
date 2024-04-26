// Uloha 6.2

#include <stdio.h>
#include <stdlib.h>

#define File FILE*

#define ALPHABET_COUNT 'Z'-'A'+1

int** calloc2D(int, int, size_t);
void free2DArr(int**, int);
void print2DArr(int**, int, int); // Vypis 2d pole
int** addRow(int**, int, int*);

File openFileR(char*);

void printChOccurrences(File);
int** generateOccurrencesMatrix(File, int*);

int main()
{
	printf("Zadaj cestu k suboru: ");

	char filePath[256];
	scanf("%s", filePath);

	File file = openFileR("subor.txt");
	if (file == NULL)
		return 1;

	printChOccurrences(file);
}

// Utility for files and ara
int** calloc2D(int w, int h, size_t typeSize)
{
	int** arr = calloc(h, typeSize);
	for (int i = 0; i < h; i++)
		arr[i] = calloc(w, typeSize);
	return arr;
}

int** addRow(int** arr, int w, int* h) {
	arr = realloc(arr, (*h + 1) * sizeof(int*));
	arr[(*h)++] = calloc(w, sizeof(int));

	return arr;
}

void print2DArr(int** arr, int w, int h)
{
	for (int y = 0; y < h; y++)
	{
		printf("%i: ", y+1);
		for (int x = 0; x < w; x++)
			printf("%i ", arr[y][x]);

		printf("\n");
	}
}

void free2DArr(int** arr, int h)
{
	for (int y = 0; y < h; y++)
		free(arr[y]);
	free(arr);
}

// Files...
File openFileR(char* path)
{
	File file = fopen(path, "r");
	if (file == NULL)
		printf("Subor '%s' sa nepodarilo otvorit!\n", path);
	return file;
}

int** generateOccurrencesMatrix(File file, int* lines)
{	
	int** arr = calloc2D(ALPHABET_COUNT, *lines, sizeof(int));

	for (char ch; fscanf(file, "%c", &ch) != EOF; )
	{
		if (ch == '\n') 
			arr = addRow(arr, ALPHABET_COUNT, lines);
		else if (ch > ' ')
			arr[*lines - 1][(int) ((ch & '_') - 'A')]++;
	}

	return arr;
}

void printChOccurrences(File file)
{
	printf("   ");
	for (int ch = 'A'; ch <= 'Z'; ch++)
		printf("%c ", ch);
	printf("\n");

	int lines = 1;
	int** arr = generateOccurrencesMatrix(file, &lines);
	print2DArr(arr, ALPHABET_COUNT, lines);

	free2DArr(arr, lines);
}
