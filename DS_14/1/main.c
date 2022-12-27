#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s)                            \
    if (!((p) = malloc(s))) {                   \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE);                     \
    }

typedef struct node* nodePointer;
typedef struct node {
    int data;
    nodePointer link;
} node;

void nodeInsert(nodePointer adjList[], int index, int vertex);
void nodePrint(nodePointer adjList[], int vertex);

int main(void)
{
    nodePointer* adjList;
    int a, b;
    char graphType;
    int vertex, edge;

    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");

    fscanf_s(fp, "%c %d %d", &graphType, (unsigned int)sizeof(char), &vertex, &edge);

    MALLOC(adjList, vertex * sizeof(nodePointer));
    for (int i = 0; i < vertex; i++) {
        adjList[i] = NULL;
    }

    if (graphType == 'u') {
        while (!feof(fp)) {
            fscanf_s(fp, "%d %d", &a, &b);
            nodeInsert(adjList, b, a);
            nodeInsert(adjList, a, b);
        }
    } else if (graphType == 'd') {
        while (!feof(fp)) {
            fscanf_s(fp, "%d %d", &a, &b);
            nodeInsert(adjList, a, b);
        }
    }

    printf("<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>>\n");
    nodePrint(adjList, vertex);

    return 0;
}

void nodeInsert(nodePointer adjList[], int index, int vertex)
{
    nodePointer tmp = NULL;
    MALLOC(tmp, sizeof(*tmp));

    tmp->data = vertex;
    tmp->link = adjList[index];
    adjList[index] = tmp;
}

void nodePrint(nodePointer adjList[], int vertex)
{
    nodePointer curr;
    for (int i = 0; i < vertex; i++) {
        curr = adjList[i];
        printf("adjList[%d] :", i);
        while (curr != NULL) {
            printf("%4d", curr->data);
            curr = curr->link;
        }
        printf("\n");
    }
}