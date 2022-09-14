#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COMPARE(x, y) (((x) < (y)) ? -1: ((x) == (y))? 0: 1)

void swap(int* x, int* y);
void sort(int list[], int n);
int binarySearch(int arr[], int searchnum, int n);
int binarySearch_recursive(int list[], int searchnum, int left, int right);

int main(void)
{
	int n, searchnum, index;
	int* arr;

	srand(time(NULL));

	printf("Enter the number of numbers to generate: ");
	scanf("%d", &n);

	if ((arr = (int*)malloc(n * sizeof(int))) == NULL)
	{
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 1000;
	}

	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n\n");

	sort(arr, n);
	printf("Sorted array:\n");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}

	printf("\n\nEnter the number to search: ");
	scanf("%d", &searchnum);

	index = binarySearch(arr, searchnum, n);

	printf("The search number is present in list[%d]\n", index);
	free(arr);
}

void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void sort(int list[], int n)
{
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++)
	{
		min = i;
		for (j = i + 1; j < n; j++)
			if (list[j] < list[min])
				min = j;
		swap(&list[i], &list[min]);
	}
}

int binarySearch_recursive(int list[], int searchnum, int left, int right)
{
	printf("call binsearch_recur, left=%d, right=%d\n", left, right);
	int middle;
	if (left <= right) {
		middle = (left + right) / 2;
		switch (COMPARE(list[middle], searchnum)) {
		case -1: return
			binarySearch_recursive(list, searchnum, middle + 1, right);
		case 0: return middle;
		case 1: return
			binarySearch_recursive(list, searchnum, left, middle - 1);
		}
	}
	return -1;
}

int binarySearch(int list[], int searchnum, int n)
{
	int left = 0, right = n - 1;
	int middle = (left + right) / 2;
	return binarySearch_recursive(list, searchnum, left, right);
}