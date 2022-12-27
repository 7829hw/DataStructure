#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 7
#define INF 1000L
int weight[MAX_VERTICES][MAX_VERTICES]; /* = {
    { 0, 28, INF, INF, INF, 10, INF },
    { 28, 0, 16, INF, INF, INF, 14 },
    { INF, 16, 0, 12, INF, INF, INF },
    { INF, INF, 12, 0, 22, INF, 18 },
    { INF, INF, INF, 22, 0, 25, 24 },
    { 10, INF, INF, INF, 25, 0, INF },
    { INF, 14, INF, 18, 24, INF, 0 }
};*/
int selected[MAX_VERTICES];
int dist[MAX_VERTICES];

int get_min_vertex(int n)
{
    int v, i;
    for (i = 0; i < n; i++)
        if (!selected[i]) {
            v = i;
            break;
        }
    for (i = v + 1; i < n; i++)
        if (!selected[i] && (dist[i] < dist[v]))
            v = i;
    return (v);
}

void prim(int s, int n)
{
    int utemp, vtemp;
    int i, u, v;
    for (u = 0; u < n; u++) // initialize dist and selected
    {
        dist[u] = INF;
        selected[u] = FALSE;
    }
    dist[s] = 0;
    for (i = 0; i < n; i++) {
        u = get_min_vertex(n);
        selected[u] = TRUE;
        if (dist[u] == INF)
            return;
        printf("선택 vertex : %d, distance : ", u);
        for (int j = 0; j < MAX_VERTICES; j++) {
            if (weight[u][j] == INF)
                printf("%5s", "INF");
            else
                printf("%5d", weight[u][j]);
        }

        for (v = 0; v < n; v++)
            if (weight[u][v] != INF)
                if (!selected[v] && weight[u][v] < dist[v]) {
                    dist[v] = weight[u][v];
                    utemp = u, vtemp = v;
                }

        printf("   선택 edge : (%d, %d) distance : %d", utemp, vtemp, dist[vtemp]);
        printf("\n");
    }
}

main()
{
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            weight[i][j] = INF;
        }
    }
    int dummy;
    int u, v, cost;
    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");
    fscanf_s(fp, "%d", &dummy);
    while (!feof(fp)) {
        fscanf_s(fp, "%d %d %d", &u, &v, &cost);
        weight[u][v] = cost;
        weight[u][0] = 0;
        weight[v][u] = cost;
        weight[v][0] = 0;
    }

    /* for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            if (weight[i][j] == INF)
                printf("INF ");
            else
                printf("%2d ", weight[i][j]);
        }
        printf("\n");
    }*/

    prim(0, MAX_VERTICES);
}