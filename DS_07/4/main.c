#include <stdio.h>
#include <stdlib.h>
#define MAX_STACKS 10
#define MALLOC(p, s) \
	if (!((p) = malloc(s))) {\
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}


typedef struct {
	int subject;
	int class;
	int score;
} element;

typedef struct stack* stackPointer;
typedef struct stack {
	element data;
	stackPointer link;
};

stackPointer top[MAX_STACKS];

void stackEmpty(void);
void push(int i, element item);
element pop(int i);
void printStack(stackPointer top[]);
void freeStack(stackPointer top[]);

int main(void)
{
	for (int i = 0; i < MAX_STACKS; i++)
	{
		top[i] = NULL;
	}
	element tmp;

	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);

	while (!feof(fp))
	{
		fscanf_s(fp, "%d %d %d", &tmp.subject, &tmp.class, &tmp.score);
		push(tmp.subject, tmp);
	}

	printf("과목번호, 학반, 성적\n");
	printStack(top);

	freeStack(top);
	fclose(fp);
	return 0;
}

void stackEmpty(void)
{
	fprintf(stderr, "stackEmpty!\n");
	return;
}

void push(int i, element item)
{
	stackPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = item;
	temp->link = top[i];
	top[i] = temp;
}

element pop(int i)
{
	element item;
	stackPointer temp = top[i];
	if (!temp)
	{
		stackEmpty();
		return;
	}
		
	item = temp->data;
	top[i] = temp->link;
	free(temp);
	return item;
}

void printStack(stackPointer top[])
{
	for(int i = 0; i < MAX_STACKS; i++)
	{
		if (top[i] != NULL)
		{
			stackPointer curr = top[i];
			printf("***********************\n");
			while (curr != NULL)
			{
				printf("%8d%6d%6d\n", curr->data.subject, curr->data.class, curr->data.score);
				curr = curr->link;
			}
		}
	}
}

void freeStack(stackPointer top[])
{
	for (int i = 0; i < MAX_STACKS; i++)
	{
		if (top[i] != NULL)
		{
			stackPointer curr = top[i];
			stackPointer tmp = NULL;
			while (curr != NULL)
			{
				tmp = curr;
				curr = curr->link;
				free(tmp);
			}
		}
	}
}