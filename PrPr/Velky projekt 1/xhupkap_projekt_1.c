#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Types
typedef FILE* File;
typedef char* String;

//Qol totally "necessary" macros...
typedef int Int;
typedef float Float;
#define null NULL

#define _free(ptr) \
	free(ptr); \
	ptr = null \

#define free2D(values, size) \
	if (values)\
	{\
		for (int i = 0; i < size; i++)\
			free((values)[i]);\
		_free(values);\
	}\

// Definition macros of utility functions
#define DEF_ADD_FUNC(type) void add ## type(type** values, type value, int size) \
{\
	*values = realloc(*values, (size + 1) * sizeof(type));\
	(*values)[size] = (value);\
}\

#define DEF_REMOVE_FUNC(type) void remove ## type(type** values, int size, int i) \
{\
	type* newArr = malloc((size - 1) * sizeof(type));\
	if (i > 0)\
		memcpy(newArr, *values, i * sizeof(type));\
	if (i < size - 1)\
		memcpy(newArr+i, *values+i+1, (size - i - 1) * sizeof(type));\
	_free(*values);\
	*values = newArr;\
}\

#define DEF_INDEX_OF(type, predicate) int indexOf##type(type* arr, int size, type value)\
{\
	for (int i = 0; i < size; i++)\
		if (predicate(arr[i], value))\
			return i;\
	return -1;\
}\

//Helper Record types, so I can change them easily later...
typedef String ID;
typedef String Pos;
typedef String Type;
typedef String Value;
typedef String Time;
typedef String Date;

//Record "struct/object"
#define DEF_Records(name) ID* name##id = null; \
	Pos* name##pos = null; \
	Type* name##type = null; \
	Value* name##value = null; \
	Time* name##time = null; \
	Date* name##date = null; \
	int name##recordCount = 0;\

#define COUNT_OF_RECORD_LINES 6
#define COUNT_OF_CIACHED_LINES 2

#define DEF_ARGS_Record ID** id, Pos** pos, Type** type, Value** value, Time** time, Date** date //Records as func args
#define ARGS_Record(ptr, name) ptr name##id, ptr name##pos, ptr name##type, ptr name##value, ptr name##time, ptr name##date //Send Records to function

DEF_ADD_FUNC(String);
DEF_ADD_FUNC(Float);
DEF_ADD_FUNC(Int);

DEF_REMOVE_FUNC(String);

DEF_INDEX_OF(String, 0 == strcmp);

File openFileR(String);
int* sortIndexes(int*, int);

void _v(File*, DEF_ARGS_Record, int);
void _n(File, DEF_ARGS_Record, int*);
void _c(DEF_ARGS_Record, int);
void _s(DEF_ARGS_Record, int);
void _h(DEF_ARGS_Record, int);
void _z(DEF_ARGS_Record, int*);
void _k(File, DEF_ARGS_Record, int*);

void freeRecords(DEF_ARGS_Record, int*);
void addPos(float**, float**, char str[], int);
int getMonth(String);

int main()
{
	DEF_Records();

	File file = null;

	for (char option; ; )
	{
		scanf("%c", &option);

		option |= ' ';
		if (option == 'v')
			_v(&file, ARGS_Record(&,), recordCount);
		else if (option == 'n')
			_n(file, ARGS_Record(&,), &recordCount);
		else if (option == 'c')
			_c(ARGS_Record(&,), recordCount);
		else if (option == 'z')
			_z(ARGS_Record(&,), &recordCount);
		else if (option == 's')
			_s(ARGS_Record(&,), recordCount);
		else if (option == 'h')
			_h(ARGS_Record(&,), recordCount);
		else if (option == 'k') //end...
		{
			_k(file, ARGS_Record(&,), &recordCount);
			break;
		}
	}
}

File openFileR(String path)
{
	File file = fopen(path, "r");
	if (file == null)
		printf("Neotvoreny subor!\n");
	return file;
}

int* sortIndexes(int* arr, int size) // Get selection-sorted indexes of array
{
	int* sorted = malloc(size * sizeof(int));
	for (int i = 0; i < size; i++)
		sorted[i] = i;

	for (int i = 0, minI; i < size - 1; i++) 
	{
		for (int j = (minI = i) + 1; j < size; j++) //Find current minimum from i to end
			if (arr[sorted[j]] < arr[sorted[minI]]) 
				minI = j;

		int temp = sorted[i]; //Swap i with new min
		sorted[i] = sorted[minI];
		sorted[minI] = temp;
	}

	return sorted;
}

//Functions
void freeRecords(DEF_ARGS_Record, int* recordCount)
{
	free2D(*id, *recordCount);
	free2D(*pos, *recordCount);
	free2D(*value, *recordCount);
	free2D(*type, *recordCount);
	free2D(*time, *recordCount);
	free2D(*date, *recordCount);

	*recordCount = 0;
}

void addPos(float** latitude, float** longitude, char str[], int size) //Split string "pos" string and parse it into latitude and longitude...
{
	char pos[2][7];
	for (int i = 0; i < 14; i++)
		pos[i/7][i%7] = str[i%7];

	addFloat(latitude, atof(pos[0]) / 10000.0, size);
	addFloat(longitude, atof(pos[1]) / 10000.0, size);
}

int getMonth(String date) //Substring month from date string and return it to as int
{
	char strMonth[3]; 
	strMonth[0] = date[4];
	strMonth[1] = date[5];

	return atoi(strMonth);
}

//Prgorams...
void _v(File* file, DEF_ARGS_Record, int recordCount) //Print content
{
	if (*file == null)
		if ((*file = openFileR("dataloger.txt")) == null)
			return;

	if (*id && *pos && *type && *value && *time && *date) //Records already populated
	{
		// printf("Printing records from fields:\n");
		for (int i = 0; i < recordCount; i++)
			printf("ID. mer. modulu: %s\nPozicia modulu: %s\nTyp mer. veliciny: %s\nHodnota: %s\nCas merania: %s\nDatum merania: %s\n\n", 
				(*id)[i], (*pos)[i], (*type)[i], (*value)[i], (*time)[i], (*date)[i]);

		return;
	}

	DEF_Records(_);

	_n(*file, ARGS_Record(&, _), &_recordCount);
	_v(file, ARGS_Record(&, _), _recordCount);
	// printf("Printing records from file!\n");
	freeRecords(ARGS_Record(&, _), &_recordCount);
}

void _n(File file, DEF_ARGS_Record, int* recordCount) //Load content into arrays
{
	if (file == null)
	{
		printf("Neotvoreny subor!\n");
		return;
	}
	
	freeRecords(ARGS_Record(,), recordCount);
	rewind(file); //Prepare file for reading from start

	int recordLine = 0;
	for (char line[32]; fscanf(file, "%s", line) != EOF; recordLine = (recordLine+1) % COUNT_OF_RECORD_LINES) //Read lines into records
	{
		if (recordLine == 0) //id
			addString(id, strdup(line), *recordCount);
		else if (recordLine == 1) //pos
			addString(pos, strdup(line), *recordCount);
		else if (recordLine == 2) //type
			addString(type, strdup(line), *recordCount);
		else if (recordLine == 3) //value
			addString(value, strdup(line), *recordCount);
		else if (recordLine == 4) //time
			addString(time, strdup(line), *recordCount);
		else if (recordLine == 5) //date
		{
			addString(date, strdup(line), *recordCount);

			(*recordCount)++;
		}

		// printf("%s\n", line);
	}

	// printf("Record count: %i\n", *recordCount);
}

void _c(DEF_ARGS_Record, int recordCount) //Idk what the hell is this good, and I dont understand what is it meant to do...
{
	if (*id && *pos && *type && *value && *time && *date)
	{
		int acceptableMonthDiff;
		scanf("%i", &acceptableMonthDiff);

		DEF_Records(ciached_);
		File ciachedFile = openFileR("ciachovanie.txt");

		int recordLine = 0;
		for (char line[32]; fscanf(ciachedFile, "%s", line) != EOF; recordLine = (recordLine+1) % COUNT_OF_CIACHED_LINES) //Read lines into ciached records (only ids and dates) from ciachovanie.txt
		{
			if (recordLine == 0) //id
				addString(&ciached_id, strdup(line), ciached_recordCount);
			else if (recordLine == 1) //date
			{
				addString(&ciached_date, strdup(line), ciached_recordCount);

				ciached_recordCount++;
			}
		}

		fclose(ciachedFile);

		int invalidCount = 0;
		for (int ic = 0; ic < ciached_recordCount; ic++) //Print validations...
		{
			int countOfActualyCiached = 0, ciachedMonth = getMonth(ciached_date[ic]);
			for (int j = 0; j < recordCount; j++)
			{
				if (strcmp((*id)[j], ciached_id[ic]) == 0)
				{
					int month = getMonth((*date)[j]), monthDiff = month - ciachedMonth;
					if (monthDiff > acceptableMonthDiff) {
						invalidCount++;
						printf("ID. mer. modulu [%s] ma %i mesiacov po ciachovani.\n", ciached_id[ic], monthDiff);
					}

					countOfActualyCiached++;
				}
			}

			if (countOfActualyCiached < 1) {
				printf("ID. mer. modulu [%s] nie je ciachovany.\n", ciached_id[ic]);
				invalidCount++;
			}
		}

		if (invalidCount < 1)
			printf("Data su korektne.\n");
		
		freeRecords(ARGS_Record(&, ciached_), &ciached_recordCount);
		return;
	}

	printf("Polia nie su vytvorene.\n");
}

void _s(DEF_ARGS_Record, int recordCount) //Save selected to file
{
	if (*id && *pos && *type && *value && *time && *date)
	{
		int* dates = null, *times = null;
		float* values = null, *latitudes = null, *longitudes = null;
		int foundCount = 0;

		char idToFind[6], typeToFind[3];
		scanf("%s %s", idToFind, typeToFind);

		for (int i = 0; i < recordCount; i++)
		{
			if (strcmp((*id)[i], idToFind) == 0 && strcmp((*type)[i], typeToFind) == 0) //Filter and keep only those that were selected...
			{
				addInt(&dates, atoi((*date)[i]), foundCount);
				addInt(&times, atoi((*time)[i]), foundCount);
				addFloat(&values, atof((*value)[i]), foundCount);
				addPos(&latitudes, &longitudes, (*pos)[i], foundCount);

				foundCount++;
			}
		}

		if (foundCount < 1)
		{
			printf("Pre dany vstup neexistuju zaznamy.\n");
			return;
		}

		int* indexes = sortIndexes(times, foundCount);
		File out = fopen("vystup_S.txt", "w");
		if (out == null)
			printFileErr: printf("Pre dany vstup nie je vytvoreny txt subor.\n");
		else
		{
			for (int j = 0, i; j < foundCount; j++) //Write sorted records that were selected into file...
				fprintf(out, "%i+%i\t%.5f\t%c%g\t%c%g\n",
					dates[(i = indexes[j])], times[i], values[i], latitudes[i] > 0 ? '+' : '-', latitudes[i], longitudes[i] > 0 ? '+' : '-', longitudes[i]);

			if (fclose(out) != 0)
				goto printFileErr;
			printf("Pre dany vstup je vytvoreny txt subor.\n");
		}

		free(indexes);

		free(dates);
		free(times);
		free(values);
		free(latitudes);
		free(longitudes);

		return;
	}

	printf("Polia nie su vytvorene.\n");
}

void _h(DEF_ARGS_Record, int recordCount) //Print histo for all types
{
	if (*id && *pos && *type && *value && *time && *date)
	{
		String types[6] = {"RD", "RM", "RO", "PI", "PE", "PA"};
		float counts[6] = {0}, maxs[6], mins[6];
		for (int i = 0; i < 6; i++)
			mins[i] = -(maxs[i] = -99999);

		for (int i = 0; i < recordCount; i++)
		{
			int index = indexOfString(types, recordCount, (*type)[i]);
			float val = atof((*value)[i]);

			if (val > maxs[index])
				maxs[index] = val;
			if (val < mins[index])
				mins[index] = val;
			counts[index]++;
		}

		printf("Typ mer. vel.  Pocetnost  Minimum  Maximum\n");
		for (int i = 0; i < 6; i++)
		{
			if (counts[i])
				printf("   %s\t \t%i\t  %g    %g\n", types[i], (int) counts[i], mins[i], maxs[i]);
		}

		return;
	}

	printf("Polia nie su vytvorene.\n");
}

void _z(DEF_ARGS_Record, int* recordCount) // Remove records with id
{
	if (*id && *pos && *type && *value && *time && *date)
	{
		char idToRemove[6];
		scanf("%s", idToRemove);

		const int oldCount = *recordCount;
		for (int i = oldCount - 1; i >= 0; i--)
		{
			// printf("%s %s\n", (*id)[i], idToRemove);
			if (strcmp((*id)[i], idToRemove) == 0)
			{
				removeString(id, *recordCount, i);
				removeString(pos, *recordCount, i);
				removeString(type, *recordCount, i);
				removeString(value, *recordCount, i);
				removeString(time, *recordCount, i);
				removeString(date, *recordCount, i);

				(*recordCount)--;
			}
		}

		printf("Vymazalo sa : %i zaznamov !\n", oldCount - *recordCount);
		return;
	}

	printf("Polia nie su vytvorene.\n");
}

void _k(File file, DEF_ARGS_Record, int* recordCount) //Dealocate all records and close the input file...
{
	freeRecords(ARGS_Record(,), recordCount);

	fclose(file);
}