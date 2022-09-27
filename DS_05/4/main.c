#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 3
#define MAX_NAME_SIZE 20
#define MAX_LEN 20

#define MALLOC(p, s) \
	if( !((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit( EXIT_FAILURE );\
	}

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;

char* delimiter = " \n";
char* context;
char* op = NULL;

element* queue;
element student;
int rear, front;
int capacity = 2;

void copy(element* a, element* b, element* c);
void queueEmpty();
void queueFull();
void addq(element item);
void deleteq();
void qprint();

int main(void)
{
	char line[MAX_LEN];
	FILE* fp = NULL;
	MALLOC(queue, capacity * sizeof(*queue));

	printf("<< Circular queue operations using dynamic allocated array, where initial capacity is %d>>\n", capacity);
	printf("The format of the stack operation is as follows!! \n");
	printf("add 1 Jung\n");
	printf("delete\n\n");
	printf("********************************************************\n");

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
			printf("wrong command! try again! \n");
	}
	fclose(fp);
	return 0;
}

void copy(element* a, element* b, element* c)
{
	while (a != b)
		*c++ = *a++;
}

void queueEmpty()
{
	fprintf(stderr, "Queue is empty, cannot delete element");
	exit(EXIT_FAILURE);
}

void queueFull()
{
	int start;
	element* newQueue;
	MALLOC(newQueue, 2 * capacity * sizeof(*queue));

	start = (front + 1) % capacity;
	if (start < 2)
		copy(queue + start, queue + start + capacity - 1, newQueue);
	else
	{
		copy(queue + start, queue + capacity, newQueue);
		copy(queue, queue + rear + 1, newQueue + capacity - start);
	}

	front = 2 * capacity - 1;
	rear = capacity - 2;
	capacity *= 2;
	free(queue);
	queue = newQueue;
	printf("queue capacity is doubled,\ncurrent queue capacity is %d.\n", capacity);
}


void addq(element item)
{
	rear = (rear + 1) % capacity;
	if (front == rear)
	{
		queueFull();
		queue[++rear].id = item.id;
		strcpy_s(queue[rear].name, MAX_NAME_SIZE, item.name);
	}
	else
	{
		queue[rear].id = item.id;
		strcpy_s(queue[rear].name, MAX_NAME_SIZE, item.name);
	}
}

void deleteq()
{
	if (front == rear)
		return queueEmpty();
	front = (front + 1) % capacity;
}

void qprint()
{
	int i = front;
	do {
		i = (i + 1) % capacity;
		printf("%d %s\n", queue[i].id, queue[i].name);
		if (i == rear)
			break;
	} while (i != front);
}