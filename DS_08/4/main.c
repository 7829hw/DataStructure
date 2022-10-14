#include <stdio.h>
#include <stdlib.h>

#define COMPARE(a, b) (a > b ? 1 : (a < b ? -1 : 0))

#define MALLOC(p, s) \
	if( !((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit( EXIT_FAILURE );\
	}

#define FALSE 0
#define TRUE 1

typedef struct polyNode* polyPointer;
typedef struct polyNode {
	int coef;
	int expon;
	polyPointer link;
} polyNode;

void insertFront(polyPointer* last, polyPointer node);
void insertLast(polyPointer* last, polyPointer node);
polyPointer getNode(void);
polyPointer retNode(polyPointer node);
void attach(float coefficient, int exponent, polyPointer* ptr);
polyPointer cpadd(polyPointer a, polyPointer b);
void printPoly(polyPointer first);
void printPolylist(polyPointer first);
void cerase(polyPointer* ptr);
void freePolylist(polyPointer first);

polyPointer a = NULL;
polyPointer b = NULL;
polyPointer avail = NULL;

int main(void)
{
	polyPointer c;
	FILE* fa = NULL;
	FILE* fb = NULL;
	if (fopen_s(&fa, "a.txt", "r"))
		exit(1);
	if (fopen_s(&fb, "b.txt", "r"))
		exit(1);

	char sortA = fgetc(fa);
	char sortB = fgetc(fb);

	while (!feof(fa))
	{
		polyPointer tmp = NULL;
		MALLOC(tmp, sizeof(*tmp));
		tmp->link = NULL;
		fscanf_s(fa, "%d %d", &tmp->coef, &tmp->expon);
		if (sortA == 'a')
			insertFront(&a, tmp);
		else
			insertLast(&a, tmp);
	}
	
	while (!feof(fb))
	{
		polyPointer tmp = NULL;
		MALLOC(tmp, sizeof(*tmp));
		tmp->link = NULL;
		fscanf_s(fb, "%d %d", &tmp->coef, &tmp->expon);
		if (sortB == 'a')
			insertFront(&b, tmp);
		else
			insertLast(&b, tmp);
	}

	
	insertFront(&a, getNode());
	insertFront(&b, getNode());

	a = a->link;
	b = b->link;

	printf("    a :\n");
	printPoly(a);
	printf("    b :\n");
	printPoly(b);

	c = cpadd(a, b);
	printf("a+b=c :\n");
	printPoly(c);

	cerase(&a);
	cerase(&b);
	cerase(&c);
	printf("avail :\n");
	printPolylist(avail);
	freePolylist(avail);
	fclose(fa);
	fclose(fb);
	return 0;
}

void insertFront(polyPointer* last, polyPointer node)
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

void insertLast(polyPointer* last, polyPointer node)
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

polyPointer getNode(void)
{
	polyPointer node;
	if (avail)
	{
		node = avail;
		avail = avail->link;
	}
	else
		MALLOC(node, sizeof(*node));
	return node;
}

polyPointer retNode(polyPointer node)
{
	node->link = avail;
	avail = node;
}

void attach(float coefficient, int exponent, polyPointer* ptr)
{
	polyPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->coef = coefficient;
	temp->expon = exponent;
	(*ptr)->link = temp;
	*ptr = temp;
}

polyPointer cpadd(polyPointer a, polyPointer b)
{
	polyPointer startA, c, lastC;
	int sum, done = FALSE;
	startA = a;
	a = a->link;
	b = b->link;
	c = getNode();
	c->expon = -1; lastC = c;
	do
	{
		switch (COMPARE(a->expon, b->expon))
		{
		case -1:
			attach(b->coef, b->expon, &lastC);
			b = b->link;
			break;
		case 0:
			if (startA == a)
				done = TRUE;
			else
			{
				sum = a->coef + b->coef;
				if (sum)
					attach(sum, a->expon, &lastC);
				a = a->link;
				b = b->link;
			}
			break;
		case 1:
			attach(a->coef, a->expon, &lastC);
			a = a->link;
		}
	} while (!done);
	lastC->link = c;
	return c;
}

void printPoly(polyPointer first)
{
	polyPointer curr = first;
	do
	{
		printf("(%p : %+5dx^%d : %p)\n", curr, curr->coef, curr->expon, curr->link);
		curr = curr->link;
	} while (curr != first);
	printf(" \n");
}

void printPolylist(polyPointer first)
{
	polyPointer curr = first;
	while (curr != NULL)
	{
		printf("(%p : %+5dx^%d : %p)\n", curr, curr->coef, curr->expon, curr->link);
		curr = curr->link;
	}
	printf(" \n");
}

void cerase(polyPointer* ptr)
{
	polyPointer temp;
	if (*ptr)
	{
		temp = (*ptr)->link;
		(*ptr)->link = avail;
		avail = temp;
		*ptr = NULL;
	}
}

void freePolylist(polyPointer first)
{
	polyPointer curr = first;
	polyPointer tmp = NULL;
	while (curr != NULL)
	{		tmp = curr;
		curr = curr->link;
		free(tmp);
	}
}