#include <stdio.h>
#include <stdlib.h>

#define COMPARE(a, b) (a > b ? 1 : (a < b ? -1 : 0))

#define MALLOC(p, s) \
	if( !((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit( EXIT_FAILURE );\
	}

typedef struct polyNode* polyPointer;
typedef struct polyNode {
	int coef;
	int expon;
	polyPointer link;
} polyNode;

polyPointer a, b;

void insertFront(polyPointer* first, polyNode node);
void insertLast(polyPointer* first, polyNode node);
void attach(float coefficient, int exponent, polyPointer* ptr);
polyPointer padd(polyPointer a, polyPointer b);
void printPoly(polyPointer first);
void freePoly(polyPointer first);

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

	polyNode tmp = { .coef = NULL, .expon = NULL, .link = NULL };
	while (!feof(fa))
	{
		fscanf_s(fa, "%d %d", &tmp.coef, &tmp.expon);
		if(sortA == 'a')
			insertFront(&a, tmp);
		else
			insertLast(&a, tmp);
	}

	while (!feof(fb))
	{
		fscanf_s(fb, "%d %d", &tmp.coef, &tmp.expon);
		if (sortB == 'a')
			insertFront(&b, tmp);
		else
			insertLast(&b, tmp);
	}

	printf("    a :\n");
	printPoly(a);
	printf("    b :\n");
	printPoly(b);

	c = padd(a, b);
	printf("a+b=c :\n");
	printPoly(c);


	freePoly(a);
	freePoly(b);
	freePoly(c);
	fclose(fa);
	fclose(fb);

	return 0;
}

void insertFront(polyPointer* first, polyNode node)
{
	polyPointer tmp;
	MALLOC(tmp, sizeof(*tmp));
	*tmp = node;
	if (!(*first))
	{
		*first = tmp;
	}
	else
	{
		tmp->link = *first;
		*first = tmp;
	}
}

void insertLast(polyPointer* first, polyNode node)
{
	polyPointer tmp;
	polyPointer curr = *first;
	MALLOC(tmp, sizeof(*tmp));
	*tmp = node;
	if (!(*first))
	{
		*first = tmp;
	}
	else
	{
		while (curr->link != NULL)
		{
			curr = curr->link;
		}
		curr->link = tmp;
	}
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

polyPointer padd(polyPointer a, polyPointer b)
{
	polyPointer c, rear, temp;
	int sum;
	MALLOC(rear, sizeof(*rear));
	c = rear;
	while (a && b)
	{
		switch (COMPARE(a->expon, b->expon))
		{
			case -1:
				attach(b->coef, b->expon, &rear);
				b = b->link;
				break;
			case 0:
				sum = a->coef + b->coef;
				if (sum)
					attach(sum, a->expon, &rear);
				a = a->link;
				b = b->link;
				break;
			case 1:
				attach(a->coef, a->expon, &rear);
				a = a->link;
		}
	}
	for (; a; a = a->link)
		attach(a->coef, a->expon, &rear);
	for (; b; b = b->link)
		attach(b->coef, b->expon, &rear);
	rear->link = NULL;
	temp = c;
	c = c->link;
	free(temp);
	return c;
}

void printPoly(polyPointer first)
{
	polyPointer curr = first;
	while (curr != NULL)
	{
		printf("(%p : %+5dx^%d : %p)\n", curr, curr->coef, curr->expon, curr->link);
		curr = curr->link;
	}
	printf("\n");
}

void freePoly(polyPointer first)
{
	polyPointer curr = first;
	polyPointer tmp = NULL;
	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->link;
		free(tmp);
	}
}