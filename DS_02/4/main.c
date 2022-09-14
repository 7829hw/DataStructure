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

	fprintf(fp, "  n size    역정렬      순정렬        랜덤\n");
	for (n = 0; n <= 1000; n += step)
	{
		fprintf(fp, "%6d", n);

		//역정렬
		long repetitions = 0;
		clock_t start = clock();
		do
		{
			repetitions++;

			for (int i = 0; i < n; i++)
				a[i] = n - i - 1;

			sort(a, n);
		} while (clock() - start < 1000);

		duration = ((double)(clock() - start)) / 1000;
		duration /= repetitions;
		fprintf(fp, "    %f", duration);

		//순정렬
		repetitions = 0;
		start = clock();
		do
		{
			repetitions++;

			for (int i = 0; i < n; i++)
				a[i] = i;

			sort(a, n);
		} while (clock() - start < 1000);

		duration = ((double)(clock() - start)) / 1000;
		duration /= repetitions;
		fprintf(fp, "    %f", duration);

		//랜덤
		srand(time(NULL));
		repetitions = 0;
		start = clock();
		do
		{
			repetitions++;

			for (int i = 0; i < n; i++)
				a[i] = rand() % 1000;

			sort(a, n);
		} while (clock() - start < 1000);

		duration = ((double)(clock() - start)) / 1000;
		duration /= repetitions;
		fprintf(fp, "    %f", duration);

		fprintf(fp, "\n");

		if (n == 100)step = 100;
	}
	fclose(fp);
}