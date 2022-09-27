#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 5
#define MAX_NAME_SIZE 20
#define MAX_LEN 20

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;

char* delimiter = " \n";
char* context;
char* op = NULL;

element stack[MAX_STACK_SIZE];
element student;
int top = -1;

void stackEmpty();
void stackFull();
void push(element item);
void pop();
void sprint();


int main(void)
{
	char line[MAX_LEN];
	FILE* fp = NULL;

	printf("<< stack operations where MAX STACK SIZE is %d>>\n", MAX_STACK_SIZE);
	printf("The format of the stack operation is as follows!! \n");
	printf("push 1 Jung\n");
	printf("pop\n\n");
	printf("********************************************************\n\n");

	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);

	while (1)
	{

		if (!(fgets(line, MAX_LEN, fp)))
			break;

		op = strtok_s(line, delimiter, &context);

		if (!strcmp(op, "push"))
		{
			sscanf_s(context, "%d %s", &student.id, student.name, (unsigned int)sizeof(student.name));
			push(student);
		}

		else if (!strcmp(op, "pop"))
			pop();

		else if (!strcmp(op, "sprint"))
		{
			sprint();
			printf("\n");
		}

		else if (!strcmp(op, "quit"))
			break;

		else
			printf("wrong command! try again! \n\n");
	}

	fclose(fp);
	return 0;
}

void stackEmpty()
{
	fprintf(stderr, "Stack is empty, cannot delete element");
	exit(EXIT_FAILURE);
}

void stackFull()
{
	fprintf(stderr, "Stack is full, cannot add element");
	printf("\ncurrent stack elements : \n");
	sprint();
	exit(EXIT_FAILURE);
}

void push(element item)
{
	if (top >= MAX_STACK_SIZE - 1)
		return stackFull();
	stack[++top].id = item.id;
	strcpy_s(stack[top].name, MAX_NAME_SIZE, item.name);
}

void pop()
{
	if (top == -1)
		return stackEmpty();
	top--;
}

void sprint()
{

	for (int i = top; i >= 0; i--)
	{
		printf("%d %s\n", stack[i].id, stack[i].name);
	}
}