#include <stdio.h>

#include <stdlib.h>

#define MALLOC(p, s) \
	if (!((p) = malloc(s))) {\
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

typedef struct listNode* listPointer;
struct listNode {
	int data;
	listPointer link;
} listNode;

listPointer first = NULL;

void add_sort(listPointer* first, int data);
void delete_odd(listPointer* first);
void add_last(listPointer* first, int data);
void printList(listPointer first);
void freeList(listPointer first);

int main(void)
{
	int n;
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);

	while (!feof(fp))
	{
		fscanf_s(fp, "%d", &n);
		add_sort(&first, n);
	}

	printf("The ordered list contains:\n");
	printList(first);

	delete_odd(&first);
	printf("After deleting nodes with odd value\n\n");
	printList(first);

	freeList(first);
	fclose(fp);
	return 0;
}

void add_sort(listPointer* first, int data)
{
	listPointer tmp = NULL;
	MALLOC(tmp, sizeof(*tmp));
	tmp->data = data;
	tmp->link = NULL;

	if (*first == NULL)
	{
		*first = tmp;
	}
	else
	{
		if ((*first)->data >= tmp->data)
		{
			tmp->link = *first;
			*first = tmp;
			return;
		}
		listPointer curr = *first;
		while (curr->link != NULL)
		{
			if (curr->data <= tmp->data && curr->link->data >= tmp->data)
			{
				tmp->link = curr->link;
				curr->link = tmp;
				return;
			}
			curr = curr->link;
		}
		curr->link = tmp;
	}
}

void delete_odd(listPointer* first)
{
	int found = 1;
	listPointer tmp = NULL;
	listPointer curr;
	while(found == 1)
	{
		found = 0;
		if ((*first)->data % 2 == 1)
		{
			found = 1;
			tmp = (*first);
			(*first) = (*first)->link;
			tmp->link = NULL;
			free(tmp);
		}
		curr = *first;
		while (curr->link != NULL)
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

void add_last(listPointer* first, int data)
{
	listPointer tmp = NULL;
	MALLOC(tmp, sizeof(*tmp));
	tmp->data = data;
	tmp->link = NULL;
	if (*first == NULL)
	{
		*first = tmp;
	}
	else
	{
		listPointer curr = *first;
		while (curr->link != NULL)
		{
			curr = curr->link;
		}
		curr->link = tmp;
	}

}

void printList(listPointer first)
{
	int i = 1;
	listPointer curr = first;
	while (curr != NULL)
	{
		printf("(%p, %4d, %p )", curr, curr->data, curr->link);
		if (i % 3 == 0)
			printf("\n");
		curr = curr->link;
		i++;
	}
	printf(" \n");
}

void freeList(listPointer first)
{
	listPointer curr = first;
	listPointer tmp = NULL;
	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->link;
		free(tmp);
	}
}