#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Types
#define File FILE*
#define String char*

//Totally "necessary" macros...
#define Int int
#define Float float
#define null NULL

// Universal add to array function macro
#define DEF_ADD_FUNC(type) void add ## type(type** values, type value, int size) \
{\
	*values = realloc(*values, (size + 1) * sizeof(type));\
	(*values)[size] = (value);\
}\

#define COUNT_OF_RECORD_LINES 6

//Get value of record
#define ID 0
#define POS 1
#define TYPE 2
#define VALUE 3
#define TIME 4
#define DATE 5

#define get(objs, i, _value) (*objs)[i * COUNT_OF_RECORD_LINES + _value]

#define readLines(linesArr, stream, totalLines, buffSize) \
	for (char line[(buffSize)]; fscanf(stream, "%s", line) != EOF; (totalLines)++) \
		addString(linesArr, strdup(line), (totalLines)); \

DEF_ADD_FUNC(String);
// DEF_ADD_FUNC(Float);
// DEF_ADD_FUNC(Int);

File openFileR(String);

// void addPos(Latitude**, Longitude**, char line[], int);

void _v(File*, String**, int*);
void _n(File*, String**, int*);
void _z(File*, String**, int*);
void _k(File, String**, int*);

void freeRecords(String**, int*);
void printRecords(String**, int);

int main()
{
	String* records = null;
	int totalLines = 0;

	File file = null;

	_v(&file, &records, &totalLines);
	// _n(&file, &records, &totalLines);
	// _v(&file, ARGS_Record(&,), &totalLines);

	_z(&file, &records, &totalLines);

	_k(file, &records, &totalLines);

	printf("%i", totalLines / COUNT_OF_RECORD_LINES);
}

File openFileR(String path)
{
	File file = fopen(path, "r");
	if (file == null)
		printf("Neotvoreny subor!\n");
	return file;
}

//Functions
void freeRecords(String** records, int* totalLines)
{
	if (*records)
	{
		for (int i = 0; i < COUNT_OF_RECORD_LINES; i++)
			free((*records)[i]);
		free(*records);

		*records = null;
		*totalLines = 0;
	}
}

void printRecords(String** records, int totalLines)
{
	for (int i = 0; i < totalLines / COUNT_OF_RECORD_LINES; i++)
		printf("ID. mer. modulu: %s\nPozicia modulu: %s\nTyp mer. veliciny: %s\nHodnota: %s\nCas merania: %s\nDatum merania: %s\n\n", 
			get(records, i, ID), get(records, i, POS), get(records, i, TYPE), get(records, i, VALUE), get(records, i, TIME), get(records, i, DATE));
}

// void addPos(Latitude** latitude, Longitude** longitude, char line[], int size)
// {
// 	// char pos[2][7];
// 	// for (int i = 0; i < 14; i++)
// 	// 	pos[i/7][i%7] = line[i%7];

// 	addFloat(latitude, atof(pos[0]) / 10000.0, size);
// 	addFloat(longitude, atof(pos[1]) / 10000.0, size);
// }

//Prgorams...
void _v(File* file, String** records, int* totalLines) //Print content
{
	if (*file == null)
		if ((*file = openFileR("dataloger.txt")) == null)
			return;
	rewind(*file);

	if (*records) //Records already populated
	{
		// printf("Printing records from fields:\n");
		printRecords(records, *totalLines);

		return;
	}

	String* _records = null;
	int _totalLines = 0;

	_n(file, &_records, &_totalLines);
	_v(file, &_records, &_totalLines);
	freeRecords(&_records, &_totalLines);
}

void _n(File* file, String** records, int* totalLines) //Load content into arrays
{
	if (*file == null)
	{
		printf("Neotvoreny subor!\n");
		return;
	}
	
	freeRecords(records, totalLines);

	readLines(records, *file, *totalLines, 32);
}

void _c(File* file, String** records, int* totalLines)
{

}

void _z(File* file, String** records, int* totalLines)
{
	char idToDelete[5];
	scanf("%s", idToDelete);

	int countOfDeleted = 0;
	for (int i = 0; i < *totalLines / COUNT_OF_RECORD_LINES; i++)
	{
		printf("%s %s\n", get(records, i, ID), idToDelete);
		if (strcmp(get(records, i, ID), idToDelete) == 0)
			countOfDeleted++;
	}

	printf("Vymazalo sa : %i zaznamov !\n", countOfDeleted);
}

void _k(File file, String** records, int* totalLines)
{
	freeRecords(records, totalLines);

	fclose(file);
}






