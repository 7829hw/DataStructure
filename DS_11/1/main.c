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
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);
void push(treePointer data);
treePointer pop(void);
treePointer postfix(void);

treePointer stack_tree[MAX_STACK_SIZE];
precedence stack[MAX_STACK_SIZE];
int top = -1;

int main(void)
{
    printf("the length of input string should be less than %d\n", MAX_EXPR_SIZE);
    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");

    fgets(expr, MAX_EXPR_SIZE, fp);
    printf("input string (postfix expression) : %s\n", expr);
    printf("creating its binary tree\n");

    treePointer root = postfix();
    printf("\ninorder traversal    : ");
    inorder(root);
    printf("\npreorder traversal   : ");
    preorder(root);
    printf("\npostorder traversal  : ");
    postorder(root);
    printf("\n");

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

void inorder(treePointer ptr)
{
    if (ptr) {
        inorder(ptr->leftChild);
        printf("%c", ptr->data);
        inorder(ptr->rightChild);
    }
}

void preorder(treePointer ptr)
{
    if (ptr) {
        printf("%c", ptr->data);
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }
}

void postorder(treePointer ptr)
{
    if (ptr) {
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        printf("%c", ptr->data);
    }
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
            push(node);
        } else {
            // printf("%c", symbol);
            treePointer node = NULL;
            MALLOC(node, sizeof(*node));
            node->data = symbol;
            node->rightChild = pop();
            node->leftChild = pop();
            push(node);
        }
    }
    return pop();
}

void push(treePointer data)
{
    stack_tree[++top] = data;
}

treePointer pop(void)
{
    return stack_tree[top--];
}