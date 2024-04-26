#include <stdlib.h>
#include <stdio.h>

struct Record
{
	int id;
	char name[12];
	char surname[12];
	char date[11];

	int h;
	struct Record* left;
	struct Record* right;
};
typedef struct Record Record;

#define height(node) (!(node) ? 0 : node->h)

void printTree(Record* root, int indent, char side)
{
	if (root)
	{
		if (!indent)
			printf("> ");
		else
			for (int i = 0; i < indent; i++)
				printf(i == indent - 1 ? "  %c- " : "    ", side);

		printf("%d(%i)\n", root->id, height(root));
		printTree(root->right, ++indent, 'R');
		printTree(root->left, indent, 'L');
	}
}

Record* rotateRight(Record*);
Record* rotateLeft(Record*);
void calcHeight(Record*);

Record* insert(Record*, Record*, int);
void delete(Record*, Record**, int);

void searchAndPrint(Record*, int*, int, int);

void freeTree(Record*);

int main()
{
	Record* root = NULL;

	int countOfPrints = 0;

	for (char option; (option = getchar()) != EOF; ) 
	{
 		if (option == 'i')
		{
			Record* rec = calloc(1, sizeof(Record));
			scanf("%i %s %s %s", &rec->id, rec->name, rec->surname, rec->date);

			root = insert(root, rec, 1);
			// printTree(root, 0, ' ');
		}
		else if (option == 's')
		{
			int from, to = -1;

			char str[17];
			fgets(str, sizeof(str), stdin);
			sscanf(str, "%i %i", &from, &to);

			// printf("\t%i %i\n", from, to);

			searchAndPrint(root, &countOfPrints, from, to);
		}
		else if (option == 'd')
		{
			int id;
			scanf("%i", &id);

			delete(root, &root, id);
		}
		// else if (option == 'p')
		// {
		// 	printTree(root, 0, ' ');
		// }
		// else if (option == 'q')
		// 	break;

		// getchar();
	}

	// printTree(root, 0, ' ');
	freeTree(root);
}

void calcHeight(Record* node) 
{
	if (node) 
	{
		int lH = height(node->left), rH = height(node->right);
		node->h = (lH > rH ? lH : rH) + 1;
	}
}

Record* rotateRight(Record* node)
{
	Record* leftChild = node->left;

	node->left = leftChild->right;
	leftChild->right = node;

	calcHeight(node);
	calcHeight(leftChild);

	return leftChild;
}

Record* rotateLeft(Record* node) 
{
	Record* rightChild = node->right;

	node->right = rightChild->left;
	rightChild->left = node;

	calcHeight(node);
	calcHeight(rightChild);

	return rightChild;
}

Record* insert(Record* curr, Record* record, int doBalance)
{
	if (!curr || !record)
		return record;

	if (record->id < curr->id)
		curr->left = insert(curr->left, record, doBalance);
	else if (record->id > curr->id)
		curr->right = insert(curr->right, record, doBalance);

	calcHeight(curr);

	if (doBalance)
	{
		int balance = height(curr->right) - height(curr->left);
		if (balance > 1) // Inbalance on right
		{
			if (record->id > curr->right->id) // L
				return rotateLeft(curr);

			if (record->id < curr->right->id) // R,L
			{
				curr->right = rotateRight(curr->right);
				return rotateLeft(curr);
			}
		}

		if (balance < -1) // Inbalance on left
		{
			if (record->id < curr->left->id) // R
				return rotateRight(curr);

			if (record->id > curr->left->id) // L,R
			{
				curr->left = rotateLeft(curr->left);
				return rotateRight(curr);
			}
		}
	}

	return curr;
}

void delete(Record* root, Record** curr, int id)
{
	if (!root || !(*curr))
		return;

	if (id < (*curr)->id)
		delete(root, &(*curr)->left, id);
	else if (id > (*curr)->id)
		delete(root, &(*curr)->right, id);
	else
	{
		Record* tmpLeft = (*curr)->left;
		Record* tmpRight = (*curr)->right;

		if (*curr == root)
		{
			free(*curr);
			*curr = tmpLeft ? tmpLeft : tmpRight; // Set smaller one as root

			insert(*curr, tmpLeft ? tmpRight : tmpLeft, 0); // Reinsert the other branch...
			return;
		}

		free(*curr);
		*curr = NULL;

		insert(root, tmpLeft, 0); //Reinsert the branches...
		insert(root, tmpRight, 0);
	}
}

void searchAndPrint(Record* root, int* countOfPrints, int from, int to)
{
	if (!root)
		return;

	if (to < 0)
	{
		if (root->id == from)
		{
			if ((*countOfPrints)++)
				printf("\n");
			printf("%i %s %s %s", root->id, root->name, root->surname, root->date);
			return;
		}

		if (from < root->id)
			searchAndPrint(root->left, countOfPrints, from, to);
		else
			searchAndPrint(root->right, countOfPrints, from, to);
		return;
	}

	if (from > to)
	{
		int oldFrom = from;
		from = to;
		to = oldFrom;
	}

	if (from < root->id)
		searchAndPrint(root->left, countOfPrints, from, to);

	if (root->id >= from && root->id <= to)
	{
		if ((*countOfPrints)++)
			printf("\n");
		printf("%i %s %s %s", root->id, root->name, root->surname, root->date);
	}

	if (to > root->id)
		searchAndPrint(root->right, countOfPrints, from, to);
}

void freeTree(Record* root)
{
	if (root)
	{
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}