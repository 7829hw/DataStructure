#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
} precedence;

int stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];
int top;

void push(int item);
int pop();
precedence getToken(char* symbol, int* n);
int eval(void);

int main(void)
{
	FILE* fi, * fo;
	fopen_s(&fi, "input.txt", "r");
	fopen_s(&fo, "output.txt", "w");

	fscanf_s(fi, "%s", expr, MAX_EXPR_SIZE);
	printf("postfix expreession : %s\n", expr);
	fprintf(fo, "postfix expreession : %s\n", expr);

	printf("the evaluation value : %d\n", eval());
	fprintf(fo, "the evaluation value : %d\n", eval());

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

int eval(void)
{
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0;
	top = -1;
	token = getToken(&symbol, &n);
	while (token != eos)
	{
		if (token == operand)
			push(symbol - '0');
		else
		{
			op2 = pop();
			op1 = pop();
			switch (token)
			{
			case plus:
				push(op1 + op2);
				break;
			case minus:
				push(op1 - op2);
				break;
			case times:
				push(op1 * op2);
				break;
			case divide:
				push(op1 / op2);
				break;
			case mod:
				push(op1 % op2);
			}
		}
		token = getToken(&symbol, &n);
	}
	return pop();
}