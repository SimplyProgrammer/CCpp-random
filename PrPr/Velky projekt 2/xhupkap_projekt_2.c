//10.1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Types
typedef FILE* File;
typedef char* String;

#define null NULL

#define new(struct) calloc(1, sizeof(struct))

#define splitInHalf(str, lenOfTok) char tokens[2][lenOfTok];\
	for (int i = 0; i < lenOfTok*2; i++)\
		tokens[i/lenOfTok][i%lenOfTok] = str[i];\

struct RecordNode {
	char ID[5];
	float latitude, longitude;
	char type[2];

	float value;

	int time;
	int date;

	struct RecordNode* next;
};
typedef struct RecordNode RecordNode;

/* Prototypes... */
void printRecord(RecordNode*);
void freeLinkedList(RecordNode*);
RecordNode* getRecord(RecordNode*, int, short);
int size(RecordNode*);

void swapRecordNodes(RecordNode**, RecordNode*, RecordNode*, RecordNode*, RecordNode*);
int swapRecords(RecordNode**, int, int);

void _n(RecordNode**, String);
void _v(RecordNode*);
void _p(RecordNode**);
void _z(RecordNode**);
void _u(RecordNode**);
void _r(RecordNode**);

int main() 
{	
	RecordNode* head = null;

	for (char option; ; )
	{
		scanf("%c", &option);

		option |= ' ';
		if (option == 'n')
			_n(&head, "dataloger_V2.txt");
		else if (option == 'v')
			_v(head);
		else if (option == 'p')
			_p(&head);
		else if (option == 'z')
			_z(&head);
		else if (option == 'r')
			_r(&head);
		else if (option == 'u')
			_u(&head);
		else if (option == 'k')
		{
			freeLinkedList(head);
			break;
		}
	}
}

/* Utility functions */
void printRecord(RecordNode* re) 
{
	if (!re)
		return;
	printf("ID:  %s\t%s\t%g\n", re->ID, re->type, re->value);
	printf("Pos: %c%g\t\t%c%g\n", re->latitude > 0 ? '+' : '-', re->latitude, re->longitude > 0 ? '+' : '-', re->longitude);
	printf("DaC: %04d\t\t%i\n", re->time, re->date);
}

void freeLinkedList(RecordNode* head) 
{
	for (RecordNode* current = head; current; current = current->next) 
		free(current);
}

RecordNode* getRecord(RecordNode* head, int index, short returnNullIfOutOfBounds) // Get record by index
{
	int i = 0;
	RecordNode* current = head;
	for (; current; current = current->next, i++)
		if (i == index)
			return current;
	return returnNullIfOutOfBounds ? null : current;
}

void insertRecord(RecordNode** head, RecordNode* newRecord, int index)
{
	if (index < 1 || !(*head)) // Add to start
	{
		newRecord->next = *head;
		*head = newRecord;
		return;
	}

	RecordNode* prevRecord = getRecord(*head, index-1, 0); // Find prev record 

	newRecord->next = prevRecord->next; // Update linking
	prevRecord->next = newRecord;
}

void swapRecordNodes(RecordNode** head, RecordNode* record1, RecordNode* prevRec1, RecordNode* record2, RecordNode* prevRec2) // Perfrom swapping links + handle if its 0 index swap
{
	if (prevRec1) // Prevs are needed cos linked list is not bidirectional...
		prevRec1->next = record2;
	else
		*head = record2;

	if (prevRec2)
		prevRec2->next = record1;
	else
		*head = record1;

	RecordNode* tmp = record1->next;
	record1->next = record2->next;
	record2->next = tmp;
}

int swapRecords(RecordNode** head, int i1, int i2)
{
	RecordNode* record1, *record2;

	if (!(record1 = getRecord(*head, i1, 1)) || 
		!(record2 = getRecord(*head, i2, 1)) || record1 == record2) 
	{
		return 0;
	}

	RecordNode* prevRec1 = getRecord(*head, i1-1, 1); // Find records before rec 1 and 2
	RecordNode* prevRec2 = getRecord(*head, i2-1, 1);

	swapRecordNodes(head, record1, prevRec1, record2, prevRec2);
	return 1;
}

int size(RecordNode* head)
{
	int sz = 0;
	for (RecordNode* current = head; current; current = current->next)
		sz++;
	return sz;
}

/* Action functions... */
void _n(RecordNode** head, String path) //Construct linked list from file
{
	File file = fopen(path, "r");
	if (file == null) {
		printf("Zaznamy neboli nacitane!”\n");
		return;
	}

	freeLinkedList(*head);

	RecordNode* current = null;
	int lineNum = 0, count = 0;
	for (char line[32]; fscanf(file, "%s", line) != EOF; lineNum++) //Read lines into records
	{
		if (strcmp(line, "$$$") == 0)
		{
			RecordNode* prev = current;
			current = new(RecordNode);
			if (!(*head)) // If list is empty (this is going to be 0 element)
				*head = current;

			if (prev) // Link next element to new one
				prev->next = current;

			lineNum = -1; //0 in next iter
			count++;
			continue;
		}

		if (lineNum == 0)
		{
			strcpy(current->ID, line);
		}
		else if (lineNum == 1)
		{
			splitInHalf(line, 8);

			current->latitude = atof(tokens[0]);
			current->longitude = atof(tokens[1]);
		}
		else if (lineNum == 2)
		{
			strcpy(current->type, line);
		}
		else if (lineNum == 3)
		{
			current->value = atof(line);
		}
		else if (lineNum == 4)
		{
			current->time = atoi(line);
		}
		else if (lineNum == 5)
		{
			current->date = atoi(line);
		}

		// printf("%i %s\n", lineNum, line);
	}

	fclose(file);
	printf("Nacitalo sa %i zaznamov.\n", count);
}

void _v(RecordNode* head) //Print records
{
	if (head == null)
	{
		printf("Ziadne zaznamy neboli nacitane!\n");
		return;
	}

	int i = 1;
	for (RecordNode* current = head; current; current = current->next)
	{
		printf("%i:\n", i);
		printRecord(current);
		i++;
	}
}

void _p(RecordNode** head)
{
	printf("Zadaj index kam sa ma zaznam pridat: ");

	int index;
	scanf("%i", &index); // !! Indexes are not from zero but from 1... Shoutout to whoever was creaeting this assigment :/

	RecordNode* newRecord = new(RecordNode); // Create new record from console...

	scanf("%s", &newRecord->ID);

	char pos[16];
	scanf("%s", pos);

	splitInHalf(pos, 8);

	newRecord->latitude = atof(tokens[0]);
	newRecord->longitude = atof(tokens[1]);

	scanf("%s", &newRecord->type);

	scanf("%f", &newRecord->value);

	scanf("%i", &newRecord->time);
	scanf("%i", &newRecord->date);

	insertRecord(head, newRecord, index-1); // Insert record at pos

	print: printf("Zaznam:\n");
	printRecord(newRecord);
	printf("bol uspesne pridany na poziciu %i!\n", index);
}

void _z(RecordNode** head) // Remove record by id
{
	printf("Zadaj ID modulov na zmazanie: ");

	char idToRemove[6];
	scanf("%s", idToRemove);

	for (RecordNode* current = *head, *prev = null; current; )
	{	
		if (current && strcmp(current->ID, idToRemove) == 0) // Check if id mathces and remove is yes
		{
			if (prev)
				prev->next = current->next;
			else // Is first
				*head = current->next;
			printf("Zaznam pre ID: %s bol vymazany.\n", current->ID);

			RecordNode* oldCurrent = current; //Prepare for freeing
			current = current->next;

			free(oldCurrent);
			continue;
		}

		prev = current; // Update vars for next iter
		current = current->next;
	}
}

void _u(RecordNode** head) // Sort the linked list
{
	int oldSize = size(*head);
	if (!oldSize)
		return;

	int i = 0, j;
	for (RecordNode* current = *head; current->next; current = getRecord(*head, ++i, 1)) // Go from start to one element before end (i < len-1)
	{	
		RecordNode* min = current;

		int indexOfMin = i;
		j = indexOfMin + 1;
		for (RecordNode* findMin = current->next; findMin; findMin = getRecord(*head, ++j, 1)) // Find min after current min
		{
			if (findMin->date < min->date || (findMin->date == min->date && findMin->time < min->time)) // Sorting by date and time where date has bigger priority
			{
				min = findMin;
				indexOfMin = j;
			}
		}

		swapRecordNodes(head, current, getRecord(*head, i-1, 1), min, getRecord(*head, indexOfMin-1, 1)); // Getting elements by index is recuired so swaping linking wont mess up with next iterations...
	}

	printf(oldSize == size(*head) ? "Spajany zoznam bol usporiadany.\n" : "Chyba usporiadania.\n"); // This makes no sense to check...
}

void _r(RecordNode** head) // Swap 2 records
{
	printf("Zadaj 2 indexi zaznaov ktore sa maju prehodit sa ma zaznam pridat: ");

	int index, index2;
	scanf("%i %i", &index, &index2);

	if (swapRecords(head, index-1, index2-1))
		printf("Zaznamy boli prehodene!\n");
}