#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC(p, s) \
	if (!((p) = malloc(s))) {\
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

typedef struct listNode {
	char name[20];
	char department[20];
	char gender[10];
	struct listNode* link;
} listNode;

listNode* first = NULL;
listNode* male = NULL;
listNode* female = NULL;

void add_last(listNode** first, listNode data);
void printList(listNode* first);
void freeList(listNode* first);

int main(void)
{
	listNode* curr = NULL;
	listNode* curr_male = NULL;
	listNode* curr_female = NULL;
	listNode temp;
	temp.link = NULL;
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);

	while (!feof(fp))
	{
		fscanf_s(fp, "%s %s %s", temp.name, 19, temp.department, 19, temp.gender, 9);
		add_last(&first, temp);
	}

	printf("전체 리스트\n");
	printList(first);

	curr = first;
	while (curr != NULL)
	{
		if (!strcmp(curr->gender, "남자"))
		{
			if (male == NULL)
			{
				male = curr;
				if (curr->link != NULL)
					curr = curr->link;
				else
				{
					curr_male = curr_male->link;
					break;
				}
				male->link = NULL;
				curr_male = male;
			}
			else
			{
				curr_male->link = curr;
				if (curr->link != NULL)
					curr = curr->link;
				else
				{
					curr_male = curr_male->link;
					break;
				}
				curr_male = curr_male->link;
			}
		}
		else
		{
			if (female == NULL)
			{
				female = curr;
				if (curr->link != NULL)
					curr = curr->link;
				else
				{
					curr_female = curr_female->link;
					break;
				}
				female->link = NULL;
				curr_female = female;
			}
			else
			{
				curr_female->link = curr;
				if (curr->link != NULL)
					curr = curr->link;
				else
				{
					curr_female = curr_female->link;
					break;
				}
				curr_female = curr_female->link;
			}
		}
	}
	curr_male->link = NULL;
	curr_female->link = NULL;

	printf("남자 리스트\n");
	printList(male);

	printf("여자 리스트\n");
	printList(female);

	freeList(male);
	freeList(female);
	fclose(fp);
	return 0;
}

void add_last(listNode** first, listNode data)
{
	listNode* tmp = NULL;
	MALLOC(tmp, sizeof(*tmp));
	strcpy_s(tmp->name, 19, data.name);
	strcpy_s(tmp->department, 19, data.department);
	strcpy_s(tmp->gender, 9, data.gender);
	tmp->link = NULL;
	if (*first == NULL)
	{
		*first = tmp;
	}
	else
	{
		listNode* curr = *first;
		while (curr->link != NULL)
		{
			curr = curr->link;
		}
		curr->link = tmp;
	}

}

void printList(listNode* first)
{
	int i = 1;
	listNode* curr = first;
	while (curr != NULL)
	{
		printf("(%p, %s, %s, %s %p )  ", curr, curr->name, curr->department, curr->gender, curr->link);
		if (i % 2 == 0)
			printf("\n");
		curr = curr->link;
		i++;
	}
	printf(" \n\n");
}

void freeList(listNode* first)
{
	listNode* curr = first;
	listNode* tmp = NULL;
	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->link;
		free(tmp);
	}
}