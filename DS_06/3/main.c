#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

int stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];
int top;

static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
} precedence;

void push(int item);
int pop();
precedence getToken(char* symbol, int* n);
void printToken(precedence token);
void postfix(void);

FILE* fi, * fo;

int main(void)
{
	fopen_s(&fi, "input.txt", "r");
	fopen_s(&fo, "output.txt", "w");

	fgets(expr, MAX_EXPR_SIZE - 1, fi);

	printf("<<<<<<<<<< infix to postfix >>>>>>>>>>\n");
	printf("infix expression	: %s\n", expr);
	printf("postfix expression	: ");
	postfix();

	fclose(fi);
	fclose(fo);

	return 0;
}

void push(int item)
{
	stack[++top] = item;
}

int pop()
{
	return stack[top--];
}

precedence getToken(char* symbol, int* n)
{
	*symbol = expr[(*n)++];
	switch (*symbol)
	{
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}

void printToken(precedence token)
{
	char operator;
	switch (token)
	{
	case lparen: operator='('; break;
	case rparen: operator=')'; break;
	case plus: operator='+'; break;
	case minus: operator='-'; break;
	case divide: operator='/'; break;
	case times: operator='*'; break;
	case mod: operator='%'; break;
	}
	printf("%c", operator);
	fputc(operator, fo);
}

void postfix(void)
{
	char symbol;
	precedence token;
	int n = 0;
	top = 0;
	stack[0] = eos;
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n))
	{
		if (token == operand)
		{
			printf("%c", symbol);
			fputc(symbol, fo);
		}
		else if (token == rparen)
		{
			while (stack[top] != lparen)
				printToken(pop());
			pop();
		}
		else
		{
			while (isp[stack[top]] >= icp[token])
				printToken(pop());
			push(token);
		}
	}
	while ((token = pop()) != eos)
		printToken(token);
	printf("\n");
}