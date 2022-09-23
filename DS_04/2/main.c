#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101

typedef struct {
	int row;
	int col;
	int value;
} term;

void transpose(term a[], term b[]);

int main(void)
{
	term a[MAX_TERMS], b[MAX_TERMS];
	FILE* fa = NULL;
	fopen_s(&fa, "a.txt", "r");
	FILE* fb = NULL;
	fopen_s(&fb, "b.txt", "w");
	int n = 0;;
	int i;

	for (i = 0; i < MAX_TERMS; i++)
	{
		if (EOF == fscanf_s(fa, "%d %d %d", &a[i].row, &a[i].col, &a[i].value))
			break;
	}
	n = i;

	transpose(a, b);
	for (i = 0; i < n; i++)
	{
		fprintf(fb, "%3d %3d %3d\n", b[i].row, b[i].col, b[i].value);
	}

	printf("A\n");
	int onoff = 0;
	for (int j = 0; j < 6; j++)
	{
		for (int k = 0; k < 6; k++)
		{
			for (i = 0; i < n; i++)
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

	printf("B\n");
	onoff = 0;
	for (int j = 0; j < 6; j++)
	{
		for (int k = 0; k < 6; k++)
		{
			for (i = 0; i < n; i++)
			{
				if (b[i].row == j && b[i].col == k)
				{
					printf("%5d", b[i].value);
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

	return 0;
}

void transpose(term a[], term b[])
{
	int n, i, j, currentb;
	n = a[0].value;
	b[0].row = a[0].col;
	b[0].col = a[0].row;
	b[0].value = n;
	if (n > 0)
	{
		currentb = 1;
		for (i = 0; i < a[0].col; i++)
			for(j = 1; j <= n; j++)
				if (a[j].col == i)
				{
					b[currentb].row = a[j].col;
					b[currentb].col = a[j].row;
					b[currentb].value = a[j].value;
					currentb++;
				}
	}
}