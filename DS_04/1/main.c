#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_TERMS 101

typedef struct {
	int row;
	int col;
	int value;
} term;

int compare(const void* a, const void* b)
{
	term A = *(term*)a;
	term B = *(term*)b;
	if (A.row > B.row)
		return 1;
	else if (A.row == B.row)
	{
		if (A.col > B.col)
			return 1;
		else
			return -1;
	}
	return -1;
}

int main(void)
{
	srand(time(NULL));
	term a[MAX_TERMS], tmp;
	int i;
	a[0].row = 20; a[0].col = 20;
	printf("원소의 개수를 쓰시오 .. ");
	scanf_s("%d", &a[0].value);

	for (i = 1; i <= a[0].value; i++)
	{
		a[i].col = rand() % 20;
		a[i].row = rand() % 20;
		a[i].value = rand() % 100;
	}

	qsort(&a[1], a[0].value, sizeof(term), compare);

	printf("Random generated matrix(20,20)\n");
	i = 0;
	int onoff = 0;
	for (int j = 0; j < a[0].row; j++)
	{
		for (int k = 0; k < a[0].col; k++)
		{
			for (i = 1; i <= a[0].value; i++)
			{
				if (a[i].row == j && a[i].col == k)
				{
					printf("%5d", a[i].value);
					onoff = 0;
					break;
				}
				else
					onoff = 1;
			}
			if (onoff == 1)
				printf("%5d", 0);
		}
		printf("\n");
	}

	printf("sparse matrix\n");
	for (i = 0; i <= a[0].value; i++)
	{
		printf("%5d, %5d, %5d\n", a[i].row, a[i].col, a[i].value);
	}

	return 0;
}