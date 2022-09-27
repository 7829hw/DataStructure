#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 3
#define MAX_NAME_SIZE 20
#define MAX_LEN 20

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;

char* delimiter = " \n";
char* context;
char* op = NULL;

element queue[MAX_QUEUE_SIZE];
element student;
int rear = -1;
int front = -1;

void queueEmpty();
void queueFull();
void addq(element item);
void deleteq();
void qprint();

int main(void)
{
	char line[MAX_LEN];
	FILE* fp = NULL;

	printf("<< Linear queue operations where MAX_QUEUE_SIZE is %d>>\n", MAX_QUEUE_SIZE);
	printf("The format of the stack operation is as follows!! \n");
	printf("add 1 Jung\n");
	printf("delete\n\n");
	printf("********************************************************\n\n");

	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);

	while (1)
	{
		if (!(fgets(line, MAX_LEN, fp)))
			break;

		op = strtok_s(line, delimiter, &context);

		if (!strcmp(op, "add"))
		{
			sscanf_s(context, "%d %s", &student.id, student.name, (unsigned int)sizeof(student.name));
			addq(student);
		}

		else if (!strcmp(op, "delete"))
			deleteq();

		else if (!strcmp(op, "qprint"))
		{
			qprint();
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

void queueEmpty()
{
	fprintf(stderr, "Queue is empty, cannot delete element");
	exit(EXIT_FAILURE);
}

void queueFull()
{
	fprintf(stderr, "Queue is full, cannot add element\n");
}

void addq(element item)
{
	if (rear == MAX_QUEUE_SIZE - 1 && front > -1)
	{
		printf("data shift\n");
		for (int i = 0; i < rear - front; i++)
		{
			queue[i].id = queue[i + front + 1].id;
			strcpy_s(queue[i].name, MAX_NAME_SIZE, queue[i + front + 1].name);
		}
		rear = rear - front - 1;
		front = -1;
	}

	else if (rear == MAX_QUEUE_SIZE - 1)
		return queueFull();
	queue[++rear].id = item.id;
	strcpy_s(queue[rear].name, MAX_NAME_SIZE, item.name);
}

void deleteq()
{
	if (front == rear)
		return queueEmpty();
	front++;
}

void qprint()
{
	for (int i = front + 1; i <= rear; i++)
	{
		printf("%d %s\n", queue[i].id, queue[i].name);
	}
}