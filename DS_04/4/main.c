#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0: 1)
#define MAX_TERMS 100
typedef struct {
	float coef;
	int expon;
} polynomial;
polynomial terms[MAX_TERMS];
int avail;

void attach(float coefficient, int exponent);

void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD);

void poly_print(char name, polynomial a[], int start, int num);

int duplicationCheck(int arr[], int size, int a);

int main(void)
{
	int aNum, bNum;
	int dNum = 0, tmp, check = 0, dNumCheck[2 * MAX_TERMS];
	int i;

	printf("<< D(x) = A(x) + B(x) >>\n");

	printf("Input the number of items of A(x) : ");
	scanf_s("%d", &aNum);
	printf("Input the number of items of B(x) : ");
	scanf_s("%d", &bNum);

	avail = aNum + bNum;

	printf("\nInput in descending order\n");
	printf("coefficient and exponent of A(x)=10x^5+8x^3+7 (10 5, 8 3, 7 0 ) : ");
	for(i = 0; i < aNum; i++)
		scanf_s("%f %d", &terms[i].coef, &terms[i].expon);

	printf("coefficient and exponent of B(x)=10x^5+8x^2+3 (10 5, 8 2, 3 0 ) : ");
	for (i = aNum; i < aNum + bNum; i++)
		scanf_s("%f %d", &terms[i].coef, &terms[i].expon);

	padd(0, aNum - 1, aNum, aNum + bNum - 1, &terms[aNum + bNum], &terms[2 * aNum + 2 * bNum]);

	for (i = 0; i < aNum + bNum; i++)
	{
		tmp = terms[i].expon;
		if (duplicationCheck(dNumCheck, aNum + bNum, tmp))
			continue;
		for (int j = 0; j < aNum + bNum; j++)
			if (tmp == terms[j].expon)
				check++;
		check--;
		dNumCheck[i] = terms[i].expon;
		printf("check:%d\n", check);
	}
	dNum = aNum + bNum - check;
	printf("dNum : %d", dNum);

	printf("\n");
	poly_print('A', terms, 0, aNum);
	poly_print('B', terms, aNum, bNum);
	poly_print('D', terms, aNum + bNum, dNum);

	return 0;
}

void attach(float coefficient, int exponent)
{
	if (avail >= MAX_TERMS)
	{
		fprintf(stderr, "Too many terms in the polynomial\n");
		exit(EXIT_FAILURE);
	}
	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}

void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD)
{
	float coefficient;
	*startD = avail;
	while (startA <= finishA && startB <= finishB)
		switch (COMPARE(terms[startA].expon, terms[startB].expon))
		{
		case -1:
			attach(terms[startB].coef, terms[startB].expon);
			startB++;
			break;
		case 0:
			coefficient = terms[startA].coef + terms[startB].coef;
			if (coefficient)
				attach(coefficient, terms[startA].expon);
			startA++;
			startB++;
			break;
		case 1:
			attach(terms[startA].coef, terms[startA].expon);
			startA++;
		}
	for (; startA <= finishA; startA++)
		attach(terms[startA].coef, terms[startA].expon);
	for (; startB <= finishB; startB++)
		attach(terms[startB].coef, terms[startB].expon);
	*finishD = avail - 1;
}

void poly_print(char name, polynomial a[], int start, int num)
{
	int i;
	printf("%c(x) = ", name);
	for (i = start; i < start + num - 1; i++)
	{
		printf("%gx^%d + ", a[i].coef, a[i].expon);
	}
	if (a[i].expon == 0)
		printf("%g\n", a[i].coef);
	else
		printf("%gx^%d\n", a[i].coef, a[i].expon);
}

int duplicationCheck(int arr[], int size, int a)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == a)
			return 1;
	}
	return 0;
}