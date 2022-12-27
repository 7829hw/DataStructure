#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s)                            \
    if (!((p) = malloc(s))) {                   \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE);                     \
    }

#define MIN(X, Y) ((X < Y) ? X : Y)

int* sorted; // additional space
/*
i left index of sorted list
j right index of sorted list
k index */
void merge(int list[], int left, int mid, int right)
{
    int i, j, k, l;
    i = left;
    j = mid + 1;
    k = left;
    /* merge of sorted lists */
    while (i <= mid && j <= right) {
        if (list[i] <= list[j])
            sorted[k++] = list[i++];
        else
            sorted[k++] = list[j++];
    }
    if (i > mid) /* copy of remained elemnets */
        for (l = j; l <= right; l++)
            sorted[k++] = list[l];
    else /* copy of remained elemnets */
        for (l = i; l <= mid; l++)
            sorted[k++] = list[l];
    /* copy sorted[] to list[] */
    for (l = left; l <= right; l++)
        list[l] = sorted[l];
}

void merge_sort(int list[], int n)
{
    int cnt = 0;
    int seg_size;
    int left;

    for (seg_size = 1; seg_size < n; seg_size *= 2, cnt++) {
        printf("segment size :%2d\n", seg_size);
        if (cnt % 2)
            printf("%12s : ", "temp");
        else
            printf("%12s : ", "a");
        for (int i = 0; i < n; i++) {
            printf("%3d ", *(list + i));
        }
        printf("\n");

        for (left = 0; left < n; left += 2 * seg_size) {
            int mid = MIN(left + seg_size - 1, n - 1);
            int right = MIN(left + 2 * seg_size - 1, n - 1);
            merge(list, left, mid, right);
        }

        if (cnt % 2)
            printf("%12s : ", "a");
        else
            printf("%12s : ", "temp");
        for (int i = 0; i < n; i++) {
            printf("%3d ", *(sorted + i));
        }
        printf("\n\n");
    }
}

int main(void)
{
    int* list;
    int i;
    int n;
    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");
    fscanf_s(fp, "%d", &n);
    MALLOC(list, n * sizeof(int));
    MALLOC(sorted, n * sizeof(int));
    for (i = 0; i < n; i++) {
        fscanf_s(fp, "%d", list + i);
    }

    printf("<<<<<<<<<<<<< Input List >>>>>>>>>>>>>\n");
    for (i = 0; i < n; i++) {
        printf("%3d ", *(list + i));
    }

    printf("\n\n<<<<< executing itterative merge sort >>>>>\n");
    merge_sort(list, n);

    printf("<<<<<<<<<<<<< Sorted List >>>>>>>>>>>>>\n");
    for (i = 0; i < n; i++) {
        printf("%3d ", *(list + i));
    }
    printf("\n\n");

    free(list);
    free(sorted);
    return 0;
}