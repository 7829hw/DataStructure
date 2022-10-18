#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s)                            \
    if (!((p) = malloc(s))) {                   \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE);                     \
    }

#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1
#define MAX_STACK_SIZE 5

typedef struct node* nodePointer;
typedef struct node {
    int data;
    nodePointer link;
};

int top = -1;
int stack[MAX_STACK_SIZE];

void stackEmpty(void);
void stackFull(void);
void push(int item);
int pop(void);

int main(void)
{
    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");
    short int out[MAX_SIZE];
    nodePointer seq[MAX_SIZE];
    nodePointer x, y;
    int i, j, n;
    printf("/* MAX_SIZE of a set S : %d */\n", MAX_SIZE);
    fscanf_s(fp, "%d", &n);
    printf("current size of S : %d\n", n);

    printf("S = {");
    for (i = 0; i < n; i++) {
        printf(" %d,", i);
    }
    printf("\b }\n");

    for (i = 0; i < n; i++) {
        out[i] = TRUE;
        seq[i] = NULL;
    }

    printf("input pairs :");
    while (fscanf_s(fp, "%d %d", &i, &j) != EOF) {
        printf(" %dR%d", i, j);
        MALLOC(x, sizeof(*x));
        x->data = j;
        x->link = seq[i];
        seq[i] = x;
        MALLOC(x, sizeof(*x));
        x->data = i;
        x->link = seq[j];
        seq[j] = x;
    }

    printf("\n\nsymmetric 관계 linked List\n");
    for (i = 0; i < n; i++) {
        printf("%-3d: symmetric 관계:", i);
        x = seq[i];
        if (x == NULL)
            continue;
        printf("\n");
        while (x != NULL) {
            printf("(%p %2d %p)   ", x, x->data, x->link);
            x = x->link;
        }
        printf("\n");
    }

    for (i = 0; i < n; i++) {
        if (out[i] == TRUE) {
            printf("\nNew class: %5d", i);
            out[i] = FALSE;
            x = seq[i];
            top = -1;
            for (;;) {
                while (x) {
                    j = x->data;
                    if (out[j]) {
                        printf("%5d", j);
                        out[j] = FALSE;
                        push(j);
                        x = x->link;
                    } else {
                        x = x->link;
                    }
                }
                if (top == -1)
                    break;
                x = seq[pop()];
            }
        }
    }

    fclose(fp);
    return 0;
}

void stackEmpty()
{
    fprintf(stderr, "Stack is empty, cannot delete element");
    exit(EXIT_FAILURE);
}

void stackFull()
{
    fprintf(stderr, "Stack is full, cannot add element");
    exit(EXIT_FAILURE);
}

void push(int item)
{
    if (top >= MAX_STACK_SIZE - 1)
        return stackFull();
    stack[++top] = item;
}

int pop()
{
    if (top == -1)
        stackEmpty();
    return stack[top--];
}