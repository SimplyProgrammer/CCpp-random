#include <stdio.h>
#include <stdlib.h>

#define isOp(ch) (((ch) | ' ') == '{' || (ch) == '(' || (ch) == '<')
#define isCls(ch) (((ch) | ' ') == '}' || (ch) == ')' || (ch) == '>')

int isBrackPair(char, char);
int validate(void*);

int main()
{
	short countToLoad, i;
	scanf("%hu", &countToLoad);

	getchar();

	int* countsOfErr = calloc(countToLoad, sizeof(int));
	for (i = 0; i < countToLoad; i++)
		countsOfErr[i] = validate(stdin);
	
	for (i = 0; i < countToLoad; i++)
	{
		if (i)
			printf("\n");
		printf("%i", countsOfErr[i]);
	}

	free(countsOfErr);
}

int isBrackPair(char op, char cls)
{
	return cls > op && cls - op < 3;
}

int validate(void* stream)
{
	int stackSize = 50, top = -1, countOfMissmatch = 0;
	char* stack = calloc(stackSize, sizeof(char)); // Ops stack

	for (char ch; (ch = getc(stream)) > ' '; ) // Read stream char by char until wt space
	{
		// printf("\t%c", ch);
		if (isOp(ch))
		{
			if (++top >= stackSize) // Realloc stack if owerflowed
			{
				stack = realloc(stack, stackSize*=2);
				// printf("\trealloced\n");
			}
			stack[top] = ch; 
		}
		else if (isCls(ch))
		{
			if (top < 0 || !isBrackPair(stack[top--], ch))
				countOfMissmatch++;
		}
	}
	// printf("\t\n");
	
	free(stack);
	return ++top + countOfMissmatch;
}