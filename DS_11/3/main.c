#include <stdio.h>
#include <stdlib.h>

#define MAX_EXPR_SIZE 80
#define MAX_STACK_SIZE 20

#define MALLOC(p, s)                            \
    if (!((p) = malloc(s))) {                   \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE);                     \
    }

typedef enum {
    lparen,
    rparen,
    plus,
    minus,
    times,
    divide,
    mod,
    eos,
    operand
} precedence;
/* isp and icp arrays -- index is value of precedence
lparen, rparen, plus, minus, times, divide, mod, eos */
int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };
char expr[MAX_EXPR_SIZE]; // postfix expression

typedef struct node* treePointer;
typedef struct node {
    char data;
    treePointer leftChild, rightChild;
} node;

treePointer root = NULL;

char expr[MAX_EXPR_SIZE];

precedence getToken(char* symbol, int* n);
void push_iter(treePointer ptr);
treePointer pop_iter(void);
void iterpreorder(treePointer node);
void iterpostorder(treePointer node);
void iterinorder(treePointer node);
void push_tree(treePointer data);
treePointer pop_tree(void);
treePointer postfix(void);

treePointer stack_tree[MAX_STACK_SIZE];
treePointer stack_iter[MAX_STACK_SIZE];
int top_tree = -1;
int top_iter = -1;
int push_cnt;

int main(void)
{
    printf("the length of input string should be less than %d\n", MAX_EXPR_SIZE);
    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");

    fgets(expr, MAX_EXPR_SIZE, fp);
    printf("input string (postfix expression) : %s\n", expr);
    printf("creating its binary tree\n");

    treePointer root = postfix();

    printf("\npreorder traversal :");
    iterpreorder(root);
    printf("\npush_cnt = %d", push_cnt);

    printf("\npostorder traversal :");
    iterpostorder(root);
    printf("\npush_cnt = %d", push_cnt);

    fclose(fp);
    return 0;
}

precedence getToken(char* symbol, int* n)
{
    *symbol = expr[(*n)++];
    switch (*symbol) {
    case '(':
        return lparen;
    case ')':
        return rparen;
    case '+':
        return plus;
    case '-':
        return minus;
    case '/':
        return divide;
    case '*':
        return times;
    case '%':
        return mod;
    case '\0':
        return eos;
    default:
        return operand;
    }
}

void push_iter(treePointer ptr)
{
    stack_iter[++top_iter] = ptr;
    push_cnt++;
}
treePointer pop_iter(void)
{
    if (top_iter == -1)
        // printf("error!\n");
        return NULL;
    return stack_iter[top_iter--];
}

void iterpreorder(treePointer node)
{
    push_cnt = 0;
    top_iter = -1;
    push_iter(node);
    for (;;) {
        node = pop_iter();
        if (!node)
            break;
        printf(" %c", node->data);
        if (node->rightChild)
            push_iter(node->rightChild);
        if (node->leftChild)
            push_iter(node->leftChild);
    }
}

void iterpostorder(treePointer node)
{
    char temp[MAX_EXPR_SIZE];
    char temp_index = 0;
    push_cnt = 0;
    top_iter = -1;
    push_iter(node);
    for (;;) {
        node = pop_iter();
        if (!node)
            break;
        temp[temp_index++] = node->data;
        if (node->leftChild)
            push_iter(node->leftChild);
        if (node->rightChild)
            push_iter(node->rightChild);
    }
    for (int i = temp_index - 1; i >= 0; i--)
        printf(" %c", temp[i]);
}

treePointer postfix(void)
{
    char symbol;
    precedence token;
    int n = 0;
    for (token = getToken(&symbol, &n); token != eos;
         token = getToken(&symbol, &n)) {
        if (token == operand) {
            // printf("%c", symbol);
            treePointer node = NULL;
            MALLOC(node, sizeof(*node));
            node->data = symbol;
            node->leftChild = NULL;
            node->rightChild = NULL;
            push_tree(node);
        } else {
            // printf("%c", symbol);
            treePointer node = NULL;
            MALLOC(node, sizeof(*node));
            node->data = symbol;
            node->rightChild = pop_tree();
            node->leftChild = pop_tree();
            push_tree(node);
        }
    }
    return pop_tree();
}

void push_tree(treePointer data)
{
    stack_tree[++top_tree] = data;
}

treePointer pop_tree(void)
{
    return stack_tree[top_tree--];
}