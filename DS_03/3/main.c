#define FALSE 0
#define TRUE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[20];
	int age;
	float salary;
} humanBeing;

int humansEqual(humanBeing* person1, humanBeing* person2);

int main(void)
{
	char tmp[20];
	humanBeing* person1;
	humanBeing* person2;
	if (!(person1 = malloc(sizeof(humanBeing))))
	{
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}
	if (!(person2 = malloc(sizeof(humanBeing))))
	{
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}

	printf("Input person1's name, age, salary :\n");
	fgets(tmp, 20, stdin);
	strcpy_s(person1->name, 19, tmp);
	scanf_s("%d %f", &(person1->age), &(person1->salary));
	getchar();

	printf("Input person2's name, age, salary :\n");
	fgets(tmp, 20, stdin);
	strcpy_s(person2->name, 19, tmp);
	scanf_s("%d %f", &(person2->age), &(person2->salary));

	if (humansEqual(person1, person2))
		printf("The two human beings are the same\n");
	else
		printf("The two human beings are not the same\n");

	free(person1);
	free(person2);

	return 0;
}

int humansEqual(humanBeing* person1, humanBeing* person2)
{
	if (strcmp(person1->name, person2->name))
		return FALSE;
	if (person1->age != person2->age)
		return FALSE;
	if (person1->salary != person2->salary)
		return FALSE;
	return TRUE;
}