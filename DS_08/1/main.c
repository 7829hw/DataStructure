#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUES 10

#define MALLOC(p, s) \
	if( !((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit( EXIT_FAILURE );\
	}

typedef struct element {
	int subject;
	int class;
	int score;
} element;

typedef struct queue* queuePointer;
typedef struct queue {
	element data;
	queuePointer link;
};

queuePointer front[MAX_QUEUES], rear[MAX_QUEUES];

element queueEmpty(void);
void addq(int i, element item);
element deleteq(int i);
void printQueue(queuePointer front[]);
void freeQueue(queuePointer first);

int main(void)
{
	for (int i = 0; i < MAX_QUEUES; i++)
		front[i] = NULL;

	element tmp;

	FILE* fp = NULL;
	if (fopen_s(&fp, "input.txt", "r"))
		exit(1);

	while (!feof(fp))
	{
		fscanf_s(fp, "%d %d %d", &tmp.subject, &tmp.class, &tmp.score);
		addq(tmp.subject, tmp);
	}

	printf("과목번호, 학반, 성적\n");
	printQueue(front);

	freeQueue(front);
	fclose(fp);

	return 0;
}

element queueEmpty(void)
{
	element item = { .subject = NULL, .class = NULL, .score = NULL };
	fprintf(stderr, "Queue is Empty\n");
	return item;
}

void addq(int i, element item)
{
	queuePointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = item;
	temp->link = NULL;
	if (front[i])
		rear[i]->link = temp;
	else
		front[i] = temp;
	rear[i] = temp;
}

element deleteq(int i)
{
	element item;
	queuePointer temp = front[i];
	if (!temp)
		return queueEmpty();
	item = temp->data;
	front[i] = temp->link;
	free(temp);
	return item;
}

void printQueue(queuePointer front[])
{
	for (int i = 0; i < MAX_QUEUES; i++)
	{
		if (front[i] != NULL)
		{
			queuePointer curr = front[i];
			printf("***********************\n");
			while (curr != NULL)
			{
				printf("%8d%6d%6d\n", curr->data.subject, curr->data.class, curr->data.score);
				curr = curr->link;
			}
		}
	}
}

void freeQueue(queuePointer front[])
{
	for (int i = 0; i < MAX_QUEUES; i++)
	{
		if (front[i] != NULL)
		{
			queuePointer curr = front[i];
			queuePointer tmp = NULL;
			while (curr != NULL)
			{
				tmp = curr;
				curr = curr->link;
				free(tmp);
			}
		}
	}
}