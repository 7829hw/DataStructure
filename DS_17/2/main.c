#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 7

#define MALLOC(p, s)                            \
    if (!((p) = malloc(s))) {                   \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE);                     \
    }

typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer link;
};
typedef struct {
    int count;
    nodePointer link;
} hdnodes;
hdnodes graph[MAX_VERTICES];
int stack[20];
int top;

void push(int data)
{
    stack[++top] = data;
}
int pop()
{
    return stack[top--];
}

void topSort(hdnodes graph[], int n)
{
    int i, j, k;
    nodePointer ptr;
    top = -1;
    for (i = 0; i < n; i++) {
        if (!graph[i].count) {
            push(i);
        }
    }

    for (i = 0; i < n; i++) {
        if (top == -1) {
            fprintf(stderr, "\nNetwork has a cycle. Sort terminated. \n");
            exit(EXIT_FAILURE);
        } else {
            j = pop();
            if (i == 0) {
                printf("%d", j);
            } else {
                printf(" -> %d", j);
            }
            for (ptr = graph[j].link; ptr; ptr = ptr->link) {
                k = ptr->vertex;
                graph[k].count--;
                if (!graph[k].count) {
                    push(k);
                }
            }
        }
    }
}

int main(void)
{
    int n, u, v;
    nodePointer tmp;
    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");
    fscanf_s(fp, "%d", &n);
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph[i].count = 0;
        graph[i].link = NULL;
    }

    while (!feof(fp)) {
        MALLOC(tmp, sizeof(*tmp))
        fscanf_s(fp, "%d %d", &u, &v);
        tmp->vertex = v;
        tmp->link = graph[u].link;
        graph[u].link = tmp;
        graph[v].count++;
    }
    topSort(graph, n);
}