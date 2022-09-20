#include <stdio.h>
#include <stdlib.h>

int* make1dArray(int num);
int* make2dArray(int rows, int cols);

int main(void)
{
	srand(time(NULL));

	int** ipp;
	int i, j, rows, cols;
	int td[4][5];

	rows = 4;
	cols = 5;

	printf("sizeof int** = %d\n", (int)sizeof(ipp));

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
			td[i][j] = i + j;
	}

	printf("이차원 배열 내용\n");
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
			printf("td[%d][%d] =%2d ", i, j, td[i][j]);
		printf("\n");
	}

	printf("\n이차원 배열의 시작 주소 td = %p\n", td);
	for (i = 0; i < rows; i++)
	{
		printf("&td[%d] = %p  &td[%d][0] = %p\n", i, &td[i], i, &td[i][0]);
	}

	ipp = make2dArray(rows, cols);

	printf("동적 이차원 배열 내용\n");
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			printf("ipp[%d][%d] =%2d ", i, j, ipp[i][j]);
		}
		printf("\n");
	}

	printf("\n동적 이차원 배열 행의 주소 &ipp = %p\n", ipp);
	for (i = 0; i < rows; i++)
		printf("&ipp[%d]= %p  &ipp[%d][0]= %p\n", i, &ipp[i], i, &ipp[i][0]);

	free(ipp);

	return 0;
}

int* make1dArray(int num)
{
	int* ptr;
	if (!(ptr = malloc(sizeof(int) * num)))
	{
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < num; i++)
	{
		*(ptr + i) = rand() % 100;
	}
	return ptr;
}

int* make2dArray(int rows, int cols)
{
	int** ptr;

	if (!(ptr = malloc(sizeof(int*) * rows)))
	{
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < rows; i++)
	{
		*(ptr + i) = make1dArray(cols);
	}
	return ptr;
}