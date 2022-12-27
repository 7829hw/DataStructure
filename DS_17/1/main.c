#include <limits.h>
#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 7 // number of vertex
#define INF 999 // no connection
int weight[MAX_VERTICES][MAX_VERTICES];

int distance[MAX_VERTICES]; // shortest distance from source node
int found[MAX_VERTICES]; // visited vertex information
int path[MAX_VERTICES]; // passed vertex information

void shortestPath(int v, int cost[][MAX_VERTICES], int distance[], int n, int found[])
{
    int i, u, w;
    for (i = 0; i < n; i++) {
        found[i] = FALSE;
        distance[i] = cost[v][i];
    }
    found[v] = TRUE;
    distance[v] = 0;
    printf("%d : ", 0);
    for (int i = 0; i < n; i++) {
        printf("%5d", distance[i]);
    }
    printf("\n");
    for (i = 0; i < n - 2; i++) {
        u = choose(distance, n, found);
        found[u] = TRUE;
        printf("%d : ", u);
        for (w = 0; w < n; w++) {
            if (!found[w]) {
                if (distance[u] + cost[u][w] < distance[w]) {
                    distance[w] = distance[u] + cost[u][w];
                    path[w] = u;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            printf("%5d", distance[i]);
        }
        printf("\n");
    }
}

int choose(int distance[], int n, int found[])
{
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (i = 0; i < n; i++)
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    return minpos;
}

void dirPrint(int i)
{
    if (i == 0)
        return;
    else {
        dirPrint(path[i]);
        printf(" <%d->%d>", path[i], i);
    }
}

int main(void)
{

    for (int i = 0; i < MAX_VERTICES; i++)
        path[i] = 0;
    int vertex, edge;
    int u, v, w;
    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            if (i == j)
                weight[i][j] = 0;
            else
                weight[i][j] = INF;
        }
    }
    fscanf_s(fp, "%d %d", &vertex, &edge);
    while (!feof(fp)) {
        fscanf_s(fp, "%d %d %d", &u, &v, &w);
        weight[u][v] = w;
        weight[v][u] = w;
    }

    shortestPath(0, weight, distance, vertex, found);
    printf("\n");
    for (int i = 1; i < MAX_VERTICES; i++) {
        printf("distance[0-%d]=%-4d:", i, distance[i]);
        dirPrint(i);
        printf("\n");
    }
}