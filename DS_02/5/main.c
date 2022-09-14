#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include "insertionSort.h"
#define MAX_SIZE 1001
/*selectionSort는 시간복잡도가 빅오 빅세타 빅오메가 모두 n^2로 동일한 반면
insertionSort는 시간복잡도가 빅오(n^2) 빅세타(n^2) 빅오메가(n)로 다르기 때문에
최선의 조건인 순정렬 된 배열에서 우수한 효율을 보였다고 생각합니다.*/
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
				a[i] = rand() % 10000;

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