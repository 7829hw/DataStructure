#include <stdio.h>

#define MAX_DEGREE 101
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)
typedef struct {
	int degree;
	float coef[MAX_DEGREE];
} polynomial;

void poly_print(char[], polynomial);

int main(void)
{
	int i;
	polynomial A, B, C;
	char name[] = "N(x)";

	printf("<< C(x) = A(x) + B(x) >>\n");
	printf("Input the degree of items of A(x) : ");
	scanf_s("%d", &A.degree);

	printf("Input the coefficients A(x) : ");
	for (i = 0; i <= A.degree; i++)
		scanf_s("%f", &A.coef[i]);

	printf("Input the degree of items of B(x) : ");
	scanf_s("%d", &B.degree);

	printf("Input the coefficients B(x) : ");
	for (i = 0; i <= B.degree; i++)
		scanf_s("%f", &B.coef[i]);

	for (i = 0; i < MAX_DEGREE; i++)
		C.coef[i] = 0;

	int startA = 0, startB = 0;
	C.degree = A.degree > B.degree ? A.degree : B.degree;
	for (i = 0; i < C.degree; i++)
	{
		if (C.degree - i <= A.degree)
		{
			C.coef[i] += A.coef[startA++];
		}
			
		if (C.degree - i <= B.degree)
		{
			C.coef[i] += B.coef[startB++];
		}
	}
	C.coef[i] += A.coef[startA] + B.coef[startB];

	name[0] = 'A';
	poly_print(name, A);
	name[0] = 'B';
	poly_print(name, B);
	name[0] = 'C';
	poly_print(name, C);

	return 0;
}

void poly_print(char name[], polynomial a)
{
	int i;
	printf("%s = ", name);
	for (i = 0; i < a.degree; i++)
		printf("%gx^%d + ", a.coef[i], a.degree - i);
	printf("%g\n", a.coef[i]);
}
