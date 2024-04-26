// Uloha 9.1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* String;

#define free2D(values, size) \
	if (values)\
	{\
		for (int i = 0; i < size; i++)\
			free((values)[i]);\
		free(values);\
	}\

// Definition macros of utility functions
#define DEF_ADD_FUNC(type) void add ## type(type** values, type value, int size) \
{\
	*values = realloc(*values, (size + 1) * sizeof(type));\
	(*values)[size] = (value);\
}\

DEF_ADD_FUNC(String)

int countOf(String*, int, String);

int indexOfMax(String*, int);

int main()
{
	String* names = NULL;
	int count = 0;

	for (;;)
	{
		printf("Zadaj meno %i. cloveka chodiaceho do kina: ", count+1);

		char name[16];
		scanf("%s", name);
		if (strcmp(name, "-") == 0) //- ukoncuje nacitane
			break;

		addString(&names, strdup(name), count);
		count++;
	}

	printf("Najviac do kina chodi: %s\n", names[indexOfMax(names, count)]);
	
	free2D(names, count);
}

int countOf(String* arr, int len, String val)
{
	int count = 0;
	for (int i = 0; i < len; i++)
		count += strcmp(arr[i], val) == 0 ? 1 : 0;
	return count;
}

int indexOfMax(String* names, int count)
{
	int max = countOf(names, count, names[0]), maxI = 0;
	for (int i = 1; i < count; i++)
		if (countOf(names, count, names[i]) > max)
			maxI = i;

	return maxI;
}