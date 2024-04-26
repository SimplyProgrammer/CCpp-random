//10.1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union Value {
	double value;
	double valuePerKg;
};

enum ValueType {
	NORMAL, PER_KG
};

struct RecordNode {
	char name[20];
	char vendor[20];

	int count;
	union Value value;
	enum ValueType valueType;

	struct RecordNode* next;
};

typedef struct RecordNode RecordNode;

#define null NULL
#define new(struct) malloc(sizeof(struct))

void printRecord(RecordNode*);

void addRecordNode(RecordNode**);

short rmRecordNode(RecordNode**, char name[20]);

void freeLinkedList(RecordNode*);

void printLinkedList(RecordNode*);

int main() 
{	
	RecordNode* head = null;

	while (1)
	{
		char ch;
		scanf("%c", &ch);
		if (ch == 'a')
		{
			addRecordNode(&head);
		}
		if (ch == 'r')
		{
			char nameToRm[20];

			printf("Type name of record to remove: ");
			scanf("%s", nameToRm);

			printf(rmRecordNode(&head, nameToRm) ? "Element removed!\n" : "No elements to remove!\n");
		}
		if (ch == 'p')
		{
			printLinkedList(head);
		}
		else if (ch == 'e')
			break;
	}

	freeLinkedList(head);
}

void printRecord(RecordNode* node)
{
	printf("RecordNode[%s, %s, %i, %lf, %s]\n", node->name, node->name, node->count, node->valueType == NORMAL ? node->value.value : node->value.valuePerKg, node->valueType == NORMAL ? "NORMAL" : "PER_KG");
}

void addRecordNode(RecordNode** head) 
{
	RecordNode* newRecord = new(RecordNode);

	printf("Type <name vendor count value> with no <>: ");
	double value, perKg;
	newRecord->valueType = scanf("%s %s %i %lf %lf", newRecord->name, newRecord->vendor, &newRecord->count, &value, &perKg) < 5 ? NORMAL : PER_KG;
	if (newRecord->valueType == NORMAL)
		newRecord->value.value = value;
	else
		newRecord->value.valuePerKg = perKg;
	newRecord->next = null;

	if (*head == null || newRecord->name[0] < (*head)->name[0]) //Should unshift
	{
		newRecord->next = *head;
		*head = newRecord;
		goto print;
	}

	RecordNode* current = *head;
	while (current->next != null && newRecord->name[0] >= current->next->name[0]) // Find sort pos when not first...
	{
		current = current->next;
	}

	newRecord->next = current->next;
	current->next = newRecord;

	print: printf("Element added successfully!\n");
}

short rmRecordNode(RecordNode** head, char name[20])
{
	for (RecordNode* current = *head, *prev = null; current != null; current = current->next)
	{	
		if (current != null && strcmp(current->name, name) == 0)
		{
			if (prev != null)
				prev->next = current->next;
			else // Is first
				*head = current->next;
			return 1;
		}

		prev = current;
	}

	return 0;
}

void freeLinkedList(RecordNode* head) 
{
	for (RecordNode* current = head; current != null; current = current->next) 
	{
		free(current);
	}
}

void printLinkedList(RecordNode* head) 
{
	if (head == null)
	{
		printf("There are no elements to print!");
		return;
	}

	for (RecordNode* current = head; current != null; current = current->next) 
	{
		printRecord(current);
	}
}