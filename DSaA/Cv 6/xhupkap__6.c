#include <stdlib.h>
#include <stdio.h>

#define HASH_MAP_SIZE 4096

struct Record
{
	char signature[42];
	float balance;

	struct Record* next;
};
typedef struct Record Record;

void printHashTable(Record* hashTable[HASH_MAP_SIZE])
{
	for (int h = 0; h < HASH_MAP_SIZE; h++)
	{
		int i = 0;
		for (Record* curr = hashTable[h]; curr; curr = curr->next, i++)
		{
			if (i)
				printf(" - ");
			else
				printf("%i | ", h);
			printf("%s %g", curr->signature, curr->balance, h);
		}
		if (i)
			printf("\n");
	}
}

int scanf4str(void*, void*, void*, void*);

float parseFloat(char*);
int streq(char*, char*);
unsigned int hash(char*, unsigned int _);
void fail(char*, int*);

void insert(Record* hashTable[HASH_MAP_SIZE], Record*, int*);
Record* search(Record* hashTable[HASH_MAP_SIZE], char*);
void update(Record* hashTable[HASH_MAP_SIZE], char*, float, int*);
void delete(Record* hashTable[HASH_MAP_SIZE], char*, int*);

void freeTree(Record* hashTable[HASH_MAP_SIZE]);

int main()
{
	Record* hashTable[HASH_MAP_SIZE] = {0};

	int countOfPrints = 0;

	for (char option, lastOp; (option = getchar()) != EOF; ) 
	{
 		if (option == 'i')
		{
			char name[15], surname[15], date[11], blnc[15];
			if (scanf4str(name, surname, date, blnc) != 4)
			{
				fail("insert", &countOfPrints);
				continue;
			}

			Record* rec = calloc(1, sizeof(Record));
			sprintf(rec->signature, "%s %s %s", name, surname, date);
			rec->balance = parseFloat(blnc);

			// printf("%s %g  |  %i\n", rec->signature, rec->balance, hash(rec->signature, HASH_MAP_SIZE));
			insert(hashTable, rec, &countOfPrints);
		}
		else if (option == 'u')
		{
			char name[15], surname[15], date[11], blnc[15], signature[42];
			if (scanf4str(name, surname, date, blnc) != 4)
			{
				fail("update", &countOfPrints);
				continue;
			}

			sprintf(signature, "%s %s %s", name, surname, date);
			
			update(hashTable, signature, parseFloat(blnc), &countOfPrints);
		}
		else if (option == 's' || option == 'd')
		{
			char name[15], surname[15], date[11], signature[42], _[8];
			if (scanf4str(name, surname, date, _) != 3)
			{
				if (option == 'd')
				{
					fail("delete", &countOfPrints);
					continue;
				}
				goto printSearchFail;
			}

			sprintf(signature, "%s %s %s", name, surname, date);
			// printf("%s\n", signature);

			if (option == 's')
			{
				Record* rec = search(hashTable, signature);
				if (!rec)
				{
					printSearchFail: fail("search", &countOfPrints);
					continue;
				}

				char blnc[15];
				sprintf(blnc, "%.2f", rec->balance);
				for (int i = 0; blnc[i]; i++) // Replace . with ,
					if (blnc[i] == '.')
					{
						blnc[i] = ',';
						break;
					}

				if (countOfPrints++)
					printf("\n");
				printf("%s", blnc);
			}
			else if (option == 'd')
				delete(hashTable, signature, &countOfPrints);
		}
		// else if (option == 'p')
		// {
		// 	printHashTable(hashTable);
		// }
		// else if (option == 'q')
		// 	break;
	}

	freeTree(hashTable);
}

int scanf4str(void* name, void* surname, void* date, void* blnc) //No blocking, not biased scanf that returns count of tokens
{
	char line[56] = {0}, _[8];
	fgets(line, sizeof(line), stdin);

	return sscanf(line, "%s %s %s %s %s", name, surname, date, blnc, _);
}

float parseFloat(char* str)
{
	for (int i = 0; str[i]; i++) // Replace , with .
		if (str[i] == ',')
		{
			str[i] = '.';
			break;
		}

	float flt;
	sscanf(str, "%f", &flt);
	return flt;
}

int streq(char* str1, char* str2)
{
	int i = 0;
	for (; str1[i] && str2[i]; i++)
		if (str1[i] != str2[i])
			return 0;

	return str1[i] == '\0' && str1[i] == str2[i];
}

unsigned int hash(char* str, unsigned int range)
{
	unsigned int hash = 0;
	for (char ch; ch = *(str++); )
		// if (ch > 32)
			hash = 31*hash + ch;
	return hash % range;
}

void fail(char* str, int* countOfPrints)
{
	if ((*countOfPrints)++)
		printf("\n");
	printf("%s failed", str);
}

void insert(Record* hashTable[HASH_MAP_SIZE], Record* rec, int* countOfPrints)
{
	int h = hash(rec->signature, HASH_MAP_SIZE);
	Record* curr;
	if (!(curr = hashTable[h]))
	{
		hashTable[h] = rec;
		return;
	}

	for (; curr; curr = curr->next) // For collisions...
	{
		if (streq(curr->signature, rec->signature)) // Dups
		{
			fail("insert", countOfPrints);
			return;
		}

		if (!curr->next)
			break;
	}
	curr->next = rec;
}

Record* search(Record* hashTable[HASH_MAP_SIZE], char* signature)
{
	Record* rec = hashTable[hash(signature, HASH_MAP_SIZE)];
	for (; rec && !streq(rec->signature, signature); rec = rec->next);  // For collisions...
	return rec;
}

void delete(Record* hashTable[HASH_MAP_SIZE], char* signature, int* countOfPrints)
{
	int h = hash(signature, HASH_MAP_SIZE);
	Record* rec = hashTable[h], *prevRec = NULL;
	if (!rec)
	{
		printFail: fail("delete", countOfPrints);
		return;
	}

	for (; rec && !streq(rec->signature, signature); rec = rec->next) // For collisions...
		prevRec = rec;
	if (!rec)
		goto printFail;

	Record* next = rec->next;
	free(rec);
	if (prevRec)
		prevRec->next = next;
	else // Was first
		hashTable[h] = next;
}

void update(Record* hashTable[HASH_MAP_SIZE], char* signature, float addBalance, int* countOfPrints)
{
	Record* rec = search(hashTable, signature);
	if (!rec)
	{
		printFail: fail("update", countOfPrints);
		return;
	}

	if (rec->balance + addBalance < 0)
		goto printFail;
	rec->balance += addBalance;
}

void freeTree(Record* hashTable[HASH_MAP_SIZE])
{
	for (int h = 0; h < HASH_MAP_SIZE; h++)
		for (Record* curr = hashTable[h]; curr; )
		{
			Record* tmp = curr;
			curr = curr->next;
			free(tmp);
		}
}