#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s)                            \
    if (!((p) = malloc(s))) {                   \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE);                     \
    }

// insertion sort with gap
// range of sort is from first to last
inc_insertion_sort(int list[], int first, int last, int gap)
// sublist sorting
{
    int i, j, key;
    for (i = first + gap; i <= last; i = i + gap) {
        key = list[i]; // i-th element is sorted
        for (j = i - gap; j >= first && key < list[j]; j = j - gap)
            list[j + gap] = list[j];
        list[j + gap] = key;
    }
}
//
void shell_sort(int list[], int n) // n = size
{
    int i, gap;
    for (gap = n / 2; gap > 0; gap = gap / 2) {
        if ((gap % 2) == 0)
            gap++;
        printf("\n\n");
        printf("gap is%5d ====>\n", gap);
        for (i = 0; i < gap; i++) // number of sublists : gap
            inc_insertion_sort(list, i, n - 1, gap);

        for (i = 0; i < n; i++) {
            printf("%5d", *(list + i));
        }
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
    for (i = 0; i < n; i++) {
        fscanf_s(fp, "%d", list + i);
    }

    printf("list[] data\n");
    for (i = 0; i < n; i++) {
        printf("%5d", *(list + i));
    }

    shell_sort(list, n);

    free(list);
    return 0;
}