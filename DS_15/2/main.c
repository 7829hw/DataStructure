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
nodePointer front, rear;

void addq(int);
int deleteq();

nodePointer graph[MAX_VERTICES] = { NULL };
int visited[MAX_VERTICES];
void nodeInsert(nodePointer* node, int data);
void nodePrint(nodePointer node);

void bfs(int v);

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

    printf("\n<<<<<<<<<<<<< Breadth First Search >>>>>>>>>>>>>\n");

    for (int i = 0; i < vertex; i++) {
        printf("bfs<%d>", i);
        bfs(i);
        printf("\n");
        for (int j = 0; j < vertex; j++)
            visited[j] = FALSE;
    }
}

void addq(int data)
{
    nodePointer tmp = NULL;
    MALLOC(tmp, sizeof(*tmp));
    tmp->vertex = data;
    tmp->link = NULL;
    if (!front) {
        front = rear = tmp;
    } else {
        rear->link = tmp;
        rear = rear->link;
    }
}
int deleteq()
{
    nodePointer tmp = front;
    front = front->link;
    return tmp->vertex;
}

void nodeInsert(nodePointer* node, int data)
{
    nodePointer tmp = NULL;
    MALLOC(tmp, sizeof(*tmp));
    tmp->vertex = data;
    tmp->link = (*node);
    (*node) = tmp;
}

void bfs(int v)
{
    nodePointer w;
    front = rear = NULL;
    printf("%5d", v);
    visited[v] = TRUE;
    addq(v);
    while (front) {
        v = deleteq();
        for (w = graph[v]; w; w = w->link)
            if (!visited[w->vertex]) {
                printf("%5d", w->vertex);
                addq(w->vertex);
                visited[w->vertex] = TRUE;
            }
    }
}

void nodePrint(nodePointer node)
{
    nodePointer curr = node;
    while (curr) {
        printf("%5d", curr->vertex);
        curr = curr->link;
    }
}