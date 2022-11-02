#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_EXPR_SIZE 80
#define MAX_STACK_SIZE 20

#define MALLOC(p, s)                            \
    if (!((p) = malloc(s))) {                   \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE);                     \
    }

typedef enum { not,
    and,
    or,
    true,
    false } logical;

typedef struct node* treePointer;
typedef struct node {
    treePointer leftChild;
    logical data;
    short int value;
    treePointer rightChild;
} node;

void push(treePointer data);
treePointer pop(void);
treePointer postfix(void);
void postOrderEval(treePointer node);

char expr[MAX_EXPR_SIZE];
logical A;
logical B;
logical C;

treePointer root = NULL;
treePointer stack[MAX_STACK_SIZE];
int top = -1;

int main(void)
{
    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");
    fgets(expr, MAX_EXPR_SIZE, fp);

    printf("input string(postfix)   : %s\n", expr);

    int flag = FALSE;
    for (logical i = false; i >= true; i--) {
        A = i;
        for (logical j = false; j >= true; j--) {
            B = j;
            for (logical k = false; k >= true; k--) {
                C = k;
                treePointer root = postfix();
                postOrderEval(root);
                if (root->value) {
                    if (!flag) {
                        printf("find true condition\n");
                        flag = TRUE;
                    }
                    printf("a=%d, b=%d, c=%d\n", !(A - 3), !(B - 3), !(C - 3));
                }
            }
        }
    }
    if (!flag)
        printf("No satisfiable combination\n");

    fclose(fp);
    return 0;
}

void push(treePointer data)
{
    stack[++top] = data;
}

treePointer pop(void)
{
    return stack[top--];
}

treePointer postfix(void)
{
    char token;
    int i = 0;
    for (token = expr[i]; token != '\0'; token = expr[++i]) {
        if (token != '~' && token != '&' && token != '|') {
            treePointer node = NULL;
            MALLOC(node, sizeof(*node));
            switch (token) {
            case 'a':
                node->data = A;
                break;
            case 'b':
                node->data = B;
                break;
            case 'c':
                node->data = C;
            }
            node->leftChild = NULL;
            node->rightChild = NULL;
            push(node);
        } else {
            treePointer node = NULL;
            MALLOC(node, sizeof(*node));
            switch (token) {
            case '~':
                node->data = not ;
                break;
            case '&':
                node->data = and;
                break;
            case '|':
                node->data = or ;
            }
            if (node->data == not ) {
                node->rightChild = pop();
                node->leftChild = NULL;
            } else {
                node->rightChild = pop();
                node->leftChild = pop();
            }
            push(node);
        }
    }
    return pop();
}

void postOrderEval(treePointer node)
{
    if (node) {
        postOrderEval(node->leftChild);
        postOrderEval(node->rightChild);
        switch (node->data) {
        case not:
            node->value = !node->rightChild->value;
            break;
        case and:
            node->value = node->rightChild->value && node->leftChild->value;
            break;
        case or:
            node->value = node->rightChild->value || node->leftChild->value;
            break;
        case true:
            node->value = TRUE;
            break;
        case false:
            node->value = FALSE;
        }
    }
}