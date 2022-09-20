#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* make1dArray(int num);

int main(void)
{
	int* ipp;
	int i, num;

	printf("일차원 배열의 수를 입력하세요: ");
	scanf_s("%d", &num);

	ipp = make1dArray(num);
	for (i = 0; i < num; i++)
	{
		printf("ipp[%2d] =%2d ", i, ipp[i]);
		if ((i % 5) == 4)
			printf("\n");
	}

	free(ipp);

	return 0;
}

int* make1dArray(int num)
{
	srand(time(NULL));
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