#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s)                            \
    if (!((p) = malloc(s))) {                   \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE);                     \
    }

typedef struct node* nodePointer;
typedef struct node {
    int m;
    int vertex1;
    int vertex2;
    nodePointer link1;
    nodePointer link2;
} node;

void initAdjList(nodePointer adjList[], nodePointer edgeList[], int vertex, int edge);
void nodePrint_input(nodePointer adjList[], int vertex);
void nodePrint_vertex(nodePointer adjList[], int vertex);

int main(void)
{
    nodePointer* adjList = NULL;
    nodePointer* edgeList = NULL;
    int a, b;
    int vertex, edge;

    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");

    fscanf_s(fp, "%d %d", &vertex, &edge);

    MALLOC(adjList, vertex * sizeof(nodePointer));
    for (int i = 0; i < vertex; i++) {
        adjList[i] = NULL;
    }

    MALLOC(edgeList, edge * sizeof(nodePointer));
    for (int i = 0; i < edge; i++) {
        MALLOC(edgeList[i], sizeof(struct node));
        edgeList[i]->m = 0;
        edgeList[i]->link1 = NULL;
        edgeList[i]->link2 = NULL;
    }

    for (int i = 0; i < edge; i++) {
        fscanf_s(fp, "%d %d", &a, &b);
        edgeList[i]->vertex1 = a;
        edgeList[i]->vertex2 = b;
    }

    printf("<<<<<<<<<< edge incident to each vertex >>>>>>>>>>\n");

    initAdjList(adjList, edgeList, vertex, edge);

    printf("\n간선의 정점 출력 순서 - 입력데이터 순서대로");
    nodePrint_input(adjList, vertex);

    printf("\n\n간선의 정점 출력 순서 - 헤더노드 정점이 먼저 오게");
    nodePrint_vertex(adjList, vertex);

    return 0;
}

void initAdjList(nodePointer adjList[], nodePointer edgeList[], int vertex, int edge)
{
    for (int i = 0; i < vertex; i++) {
        for (int j = 0; j < edge; j++) {
            if ((i == edgeList[j]->vertex1) || (i == edgeList[j]->vertex2)) {
                adjList[i] = edgeList[j];
                break;
            }
        }
    }
    for (int i = 0; i < edge; i++) {
        for (int j = i + 1; j < edge; j++) {
            if ((edgeList[i]->vertex1 == edgeList[j]->vertex1) || (edgeList[i]->vertex1 == edgeList[j]->vertex2)) {
                edgeList[i]->link1 = edgeList[j];
                break;
            }
        }
    }
    for (int i = 0; i < edge; i++) {
        for (int j = i + 1; j < edge; j++) {
            if ((edgeList[i]->vertex2 == edgeList[j]->vertex1) || (edgeList[i]->vertex2 == edgeList[j]->vertex2)) {
                edgeList[i]->link2 = edgeList[j];
                break;
            }
        }
    }
}

void nodePrint_input(nodePointer adjList[], int vertex)
{
    nodePointer curr;
    for (int i = 0; i < vertex; i++) {
        curr = adjList[i];
        printf("\nedges incident to vertex %d :", i);
        while (curr != NULL) {
            printf(" (%d, %d)", curr->vertex1, curr->vertex2);
            if (i == curr->vertex1)
                curr = curr->link1;
            else if (i == curr->vertex2)
                curr = curr->link2;
        }
    }
}

void nodePrint_vertex(nodePointer adjList[], int vertex)
{
    nodePointer curr;
    for (int i = 0; i < vertex; i++) {
        curr = adjList[i];
        printf("\nedges incident to vertex %d :", i);
        while (curr != NULL) {
            if (i == curr->vertex1)
                printf(" (%d, %d)", curr->vertex1, curr->vertex2);
            else
                printf(" (%d, %d)", curr->vertex2, curr->vertex1);
            if (i == curr->vertex1)
                curr = curr->link1;
            else if (i == curr->vertex2)
                curr = curr->link2;
        }
    }
}