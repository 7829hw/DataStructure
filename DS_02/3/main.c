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
	FILE* fp = fopen("out.txt", "w");

	fprintf(fp, "     n    repetitions     time\n");
	for (n = 0; n <= 1000; n += step)
	{
		long repetitions = 0;
		clock_t start = clock();
		do
		{
			repetitions++;

			for (i = 0; i < n; i++)
				a[i] = n - 1;

			sort(a, n);
		} while (clock() - start < 1000);

		duration = ((double)(clock() - start)) / 1000;
		duration /= repetitions;
		fprintf(fp, "%6d    %9d    %f\n", n, repetitions, duration);
		if (n == 100)step = 100;
	}
	fclose(fp);
}