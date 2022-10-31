#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 20
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
void iterinorder(treePointer node);
void addq(treePointer ptr);
treePointer deleteq();
void levelOrder(treePointer ptr);
void push_tree(treePointer data);
treePointer pop_tree(void);
treePointer postfix(void);

treePointer stack_tree[MAX_STACK_SIZE];
treePointer stack_iter[MAX_STACK_SIZE];
int top_tree = -1;
int top_iter = -1;
treePointer queue[MAX_QUEUE_SIZE];
int front = 0;
int rear = 0;
char stackpush_order[MAX_EXPR_SIZE];
int stackpush_index = 0;

int main(void)
{
    printf("the length of input string should be less than %d\n", MAX_EXPR_SIZE);
    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");

    fgets(expr, MAX_EXPR_SIZE, fp);
    printf("input string (postfix expression) : %s\n", expr);
    printf("creating its binary tree\n");

    treePointer root = postfix();

    printf("\niterative inorder traversal    :");
    iterinorder(root);

    printf("\n스택에 들어가는 데이터의 순서  :");
    for (int i = 0; i < stackpush_index; i++)
        printf(" %c", stackpush_order[i]);

    printf("\n\nlevel order traversal          :");
    levelOrder(root);
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

void push_iter(treePointer ptr)
{
    stack_iter[++top_iter] = ptr;
}
treePointer pop_iter(void)
{
    return stack_iter[top_iter--];
}

void iterinorder(treePointer node)
{
    for (;;) {
        for (; node; node = node->leftChild) {
            push_iter(node);
            stackpush_order[stackpush_index++] = node->data;
        }
        stackpush_order[stackpush_index] = '\0';

        node = pop_iter();
        if (!node)
            break;
        printf(" %c", node->data);
        node = node->rightChild;
    }
}

void addq(treePointer ptr)
{
    queue[rear++] = ptr;
}
treePointer deleteq()
{
    return queue[front++];
}

void levelOrder(treePointer ptr)
{
    treePointer queue[MAX_QUEUE_SIZE];
    if (!ptr)
        return;
    addq(ptr);
    for (;;) {
        ptr = deleteq();
        if (ptr) {
            printf(" %c", ptr->data);
            if (ptr->leftChild)
                addq(ptr->leftChild);
            if (ptr->rightChild)
                addq(ptr->rightChild);
        } else
            break;
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
            treePointer node = NULL;
            MALLOC(node, sizeof(*node));
            node->data = symbol;
            node->leftChild = NULL;
            node->rightChild = NULL;
            push_tree(node);
        } else {
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