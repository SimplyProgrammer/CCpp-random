// Uloha 7.3

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char* line = NULL;

	// Memory efficient string read...
	int len = 0;
	for (char ch; (ch = getchar()) != EOF && ch != '\n'; len++)
	{
		line = realloc(line, (len+1) * sizeof(char));
		line[len] = ch;
	}
	line[len] = '\0';

	printf("%s %i\n", line, len);
	free(line);
}
