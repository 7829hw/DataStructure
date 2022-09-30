#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 10
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
int top[MAX_STACK_SIZE];
int bottom[MAX_STACK_SIZE];
int max_size[MAX_STACK_SIZE];
int num;		//Number of stacks
int size;		//Size of each stack

void stackEmpty(int number);
void stackFull(int number);
void push(element item);
void pop(int number);
void sprint(int number);


int main(void)
{
	char line[MAX_LEN];
	FILE* fp = NULL;
	printf("How Many Stacks ? : ");
	scanf_s("%d", &num);
	size = MAX_STACK_SIZE / num;
	for (int i = 0; i < num; i++)
	{
		top[i] = i * size - 1;
	}
	for (int i = 0; i < num; i++)
	{
		bottom[i] = i * size - 1;
	}
	for (int i = 0; i < num; i++)
	{
		max_size[i] = (i + 1) * size - 1;
	}
	max_size[num - 1] = (int)MAX_STACK_SIZE - 1;

	printf("\n C Language program to implement the Multiple Stacks\n");
	printf("add stack_num(0-%d) name : add 0 kim\n", num - 1);
	printf("delete stack_num(0-%d) name : delete 0\n", num - 1);
	printf("sprint stack_num(0-%d) name : sprint 0\n", num - 1);
	printf("quit\n");
	printf("********************************************************\n\n");

	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);

	while (1)
	{

		if (!(fgets(line, MAX_LEN, fp)))
			break;

		op = strtok_s(line, delimiter, &context);
		sscanf_s(context, "%d %s", &student.id, student.name, (unsigned int)sizeof(student.name));

		if (!strcmp(op, "add"))
		{
			if (student.id < 0 || student.id >= num)
				printf("stack number error, try again\n");
			else
				push(student);
		}

		else if (!strcmp(op, "delete"))
			pop(student.id);

		else if (!strcmp(op, "sprint"))
		{
			if (student.id < 0 || student.id >= num)
			{
				printf("stack number error, try again\n");
				continue;
			}
			sprint(student.id);
			printf("\n");
		}

		else if (!strcmp(op, "quit"))
			break;

		else
			printf("wrong command, try again!!\n\n");
	}

	printf("\nProgram end\n\n");
	for (int i = 0; i < num; i++)
	{
		printf("stack %d :", i);
		sprint(i);
		printf("\n\n");
	}

	fclose(fp);
	return 0;
}

void stackEmpty(int number)
{
	fprintf(stderr, "Stack %d is Full\n", number);
}

void stackFull(int number)
{
	fprintf(stderr, "Stack %d is Full\n", number);
}

void push(element item)
{
	if (top[item.id] >= max_size[item.id])
		return stackFull(item.id);
	strcpy_s(stack[++top[item.id]].name, MAX_NAME_SIZE, item.name);
	printf("%s is Pushed in Stack No. %d\n", item.name, item.id);
}

void pop(int number)
{
	if (top[number] <= bottom[number])
		return stackEmpty(number);
	printf("%s is popped from Stack No. %d\n", stack[top[number]].name, number);
	top[number]--;
}

void sprint(int number)
{
	printf("\n");
	for (int i = top[number]; i > bottom[number]; i--)
	{
		printf("%s\n", stack[i].name);
	}
}