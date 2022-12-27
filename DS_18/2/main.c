#include <stdio.h>
#include <stdlib.h>

#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))

#define MALLOC(p, s)                            \
    if (!((p) = malloc(s))) {                   \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE);                     \
    }

typedef struct {
    int key;
} element;

int cnt = 0;
int n;

printList(element list[])
{
    for (int i = 0; i < n; i++) {
        printf("%3d", list[i].key);
    }
    printf("\n");
}

void quickSort(element a[], int left, int right)
{ /* sort a[left:right] into nondecreasing order on the key field; a[left].key is arbitrarily
chosen as the pivot key; it is assumed that a[left].key <= a[right+1].key */
    int pivot, i, j;
    element temp;
    if (left < right) {
        cnt++;
        i = left;
        j = right + 1;
        pivot = a[left].key;
        printf("pivot = %d :", pivot);
        do { /* search for keys from the left and right
        sublists, swapping out-of-order elements until
        the left and right boundaries cross or meet */
            do
                i++;
            while ((a[i].key < pivot) && (i < right));
            do
                j--;
            while (a[j].key > pivot);
            if (i < j)
                SWAP(a[i], a[j], temp);
        } while (i < j);
        SWAP(a[left], a[j], temp);
        printList(a);
        quickSort(a, left, j - 1);
        quickSort(a, j + 1, right);
    }
}

int main(void)
{
    element* list;
    int i;
    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");
    fscanf_s(fp, "%d", &n);
    MALLOC(list, n * sizeof(element));
    for (i = 0; i < n; i++) {
        fscanf_s(fp, "%d", &list[i].key);
    }

    printf("<<<<<<<<<<<<< Input List >>>>>>>>>>>>>\n");
    for (i = 0; i < n; i++) {
        printf("%2d ", list[i].key);
    }
    printf("\n\n");

    printf("execution of quick sort ...\n");
    quickSort(list, 0, n - 1);

    printf("\ncalls of quick sort:%2d", cnt);

    printf("\n\n<<<<<<<<<<<<< Sorted List >>>>>>>>>>>>>\n");
    for (i = 0; i < n; i++) {
        printf("%2d ", list[i].key);
    }
    printf("\n\n");

    free(list);
    return 0;
}