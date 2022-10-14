#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
	if( !((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit( EXIT_FAILURE );\
	}

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
} listNode;
listPointer first = NULL;
listPointer last = NULL;

void insertFront(listPointer* last, listPointer node);
void insertLast(listPointer* last, listPointer node);
void printList(listPointer first);
void delete_odd(listPointer* first, listPointer* last);
void freeList(listPointer first);

int main(void)
{
	int n;

	FILE* fp = NULL;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);

	while (!feof(fp))
	{
		listPointer tmp = NULL;
		MALLOC(tmp, sizeof(*tmp));
		fscanf_s(fp, "%d", &n);
		tmp->data = n;
		insertLast(&last, tmp);
	}

	printf("The Circularly Linked List contains:\n");
	first = last->link;
	printList(first);
	printf("After deleting nodes with odd value\n");
	delete_odd(&first, &last);
	printList(first);

	freeList(first);
	fclose(fp);

	return 0;
}

void insertFront(listPointer* last, listPointer node)
{
	if (!(*last))
	{
		*last = node;
		node->link = node;
	}
	else
	{
		node->link = (*last)->link;
		(*last)->link = node;
	}
}

void insertLast(listPointer* last, listPointer node)
{
	if (!(*last))
	{
		*last = node;
		node->link = node;
	}
	else
	{
		node->link = (*last)->link;
		(*last)->link = node;
		*last = node;
	}
}

void printList(listPointer first)
{
	int i = 1;
	listPointer curr = first;
	do
	{
		printf("(%p, %4d, %p )", curr, curr->data, curr->link);
		if (i % 3 == 0)
			printf("\n");
		curr = curr->link;
		i++;
	} while (curr != first);
	printf(" \n");
}

void delete_odd(listPointer* first, listPointer* last)
{
	int found = 1;
	listPointer tmp = NULL;
	listPointer curr;
	while (found == 1)
	{
		found = 0;
		if ((*first)->data % 2 == 1)
		{
			found = 1;
			tmp = (*first);
			(*first) = (*first)->link;
			(*last)->link = (*first);
			tmp->link = NULL;
			free(tmp);
		}
		curr = *first;
		while (curr->link != (*first))
		{
			if (curr->link->data % 2 == 1)
			{
				found = 1;
				tmp = curr->link;
				curr->link = curr->link->link;
				tmp->link = NULL;
				free(tmp);
				break;
			}
			curr = curr->link;
		}
	}
}

void freeList(listPointer first)
{
	listPointer curr = first;
	listPointer tmp = NULL;
	do
	{
		tmp = curr;
		curr = curr->link;
		free(tmp);
	} while (curr != first);
}