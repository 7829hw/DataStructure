#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#define MAX_SIZE 1001
#include "selectionSort.h"

void main(void)
{
	int i, n, step = 10;
	int a[MAX_SIZE];
	double duration;
	clock_t start;
	FILE* fp = fopen("out.txt", "w");

	fprintf(fp, "     N       time\n");
	for (n = 0; n <= 1000; n += step)
	{
		for (i = 0; i < n; i++)
			a[i] = n - 1;

		start = clock();
		sort(a, n);
		duration = ((double)(clock() - start)) / 1000;
		fprintf(fp, "%6d     %f\n", n, duration);
		if (n == 100) step = 100;
	}
	fclose(fp);
}