#include <stdio.h>
#include <stdlib.h>

int* func1(void);
void func2(int* func);
void func3(int** func);
char* func4(int n);

int main(void)
{
	int* pNum;
	char* pChar;

	pNum = func1();		// int ũ�⸸ŭ �����Ҵ� �޾� 10�� ������ ������ ������ ����
	printf("%d\n", *pNum);

	func2(pNum);		// pNum�� ����Ű�� ���� 100���� ����
	printf("%d\n", *pNum);

	func3(&pNum);		// pNum�� ����Ű�� ���� 200���� ����
	printf("%d\n", *pNum);

	pChar = func4(100);	// pChar �� 100byte �Ҵ� ���� �޸𸮿� Ű����κ��� �Է� ���� ���ڿ� ����

	printf("�Է��� ���ڿ� : ");

	scanf_s("%s", pChar, 100);
	printf("pChar contents = %s\n", pChar);

	free(pNum);
	free(pChar);
	return 0;

}

int* func1(void)
{
	int* p = (int*)malloc(sizeof(int));
	*p = 10;
	
	return p;
}

void func2(int* func)
{
	*func = 100;
}

void func3(int** func)
{
	**func = 200;
}

char* func4(int n)
{
	char* p = (char*)malloc(sizeof(char) * n);

	return p;
}