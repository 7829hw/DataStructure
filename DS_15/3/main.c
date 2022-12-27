#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s)                            \
    if (!((p) = malloc(s))) {                   \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE);                     \
    }

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100

typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer link;
} Node;

nodePointer graph[MAX_VERTICES] = { NULL };
int visited[MAX_VERTICES];
void nodeInsert(nodePointer* node, int data);
void nodePrint(nodePointer node);
void dfs(int v);
void connected(void);

int main(void)
{
    int vertex, edge;
    int a, b;
    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");
    fscanf_s(fp, "%d %d", &vertex, &edge);

    while (!feof(fp)) {
        fscanf_s(fp, "%d %d", &a, &b);
        nodeInsert(&graph[a], b);
        nodeInsert(&graph[b], a);
    }

    printf("<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>>\n");
    for (int i = 0; i < vertex; i++) {
        printf("graph<%d>", i);
        nodePrint(graph[i]);
        printf("\n");
    }

    printf("\n<<<<<<<<<<<<< Connected Components >>>>>>>>>>>>>\n");

    connected();
}

void nodeInsert(nodePointer* node, int data)
{
    nodePointer tmp = NULL;
    MALLOC(tmp, sizeof(*tmp));
    tmp->vertex = data;
    tmp->link = (*node);
    (*node) = tmp;
}

void nodePrint(nodePointer node)
{
    nodePointer curr = node;
    while (curr) {
        printf("%5d", curr->vertex);
        curr = curr->link;
    }
}

void dfs(int v)
{
    nodePointer w;
    visited[v] = TRUE;
    printf("%3d", v);
    for (w = graph[v]; w; w = w->link)
        if (!visited[w->vertex])
            dfs(w->vertex);
}

void connected(void)
{
    int k = 1;
    int i;
    for (i = 0; i < 8; i++)
        if (!visited[i]) {
            printf("connected component %d :", k++);
            dfs(i);
            printf("\n");
        }
}