#include <stdio.h>
#include <stdlib.h>

#define SWAP(a, b, tmp) \
    {                   \
        tmp = a;        \
        a = b;          \
        b = tmp;        \
    }

#define MAX_HEAP_SIZE 100

typedef struct {
    int key;
} element;

typedef struct {
    element heap[MAX_HEAP_SIZE];
    int heap_size;
} HeapType;

void insert_max_heap(HeapType* h, int data)
{
    element item = { .key = data };
    int i;
    i = ++(h->heap_size);

    while ((i != 1) && (item.key > h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

element delete_max_heap(HeapType* h)
{
    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;

    while (child <= h->heap_size) {
        if ((child < h->heap_size) && ((h->heap[child].key) < h->heap[child + 1].key)) {
            child++;
        }
        if (temp.key >= h->heap[child].key) {
            break;
        }

        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }

    h->heap[parent] = temp;
    return item;
}

void adjust(element a[], int root, int n)
{
    int child, rootkey;
    element temp;
    temp = a[root];
    rootkey = a[root].key;
    child = 2 * root;
    while (child <= n) {
        if ((child <= n) && (a[child].key < a[child + 1].key))
            child++;
        if (rootkey > a[child].key)
            break;
        else {
            a[child / 2] = a[child];
            child *= 2;
        }
    }
    a[child / 2] = temp;
}

void heapSort(element a[], int n)
{
    int i, j;
    element temp;

    for (i = n / 2; i > 0; i--)
        adjust(a, i, n);
    for (i = n - 1; i > 0; i--) {
        SWAP(a[1], a[i + 1], temp);
        adjust(a, 1, i);
    }
}

int main(void)
{
    element* sorted;
    HeapType heap = { .heap = { NULL }, .heap_size = 0 };
    int n;
    int temp;
    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");
    printf("<<<<<<<<<<<<< Input List >>>>>>>>>>>>>\n");

    fscanf_s(fp, "%d", &n);
    sorted = malloc(n * sizeof(element));
    for (int i = 0; i < n; i++) {
        fscanf_s(fp, "%d", &temp);
        printf("%d ", temp);
        insert_max_heap(&heap, temp);
    }

    printf("\n\n<<<<<<<<<<<<< executing heap sort >>>>>>>>>>>>>\nafter initialization of max heap...\n");
    for (int i = 1; i < heap.heap_size + 1; i++) {
        printf("%d ", heap.heap[i].key);
    }
    printf("\n\n\n");

    for (int i = 0; heap.heap_size > 0; i++) {
        printf("step%3d:", i + 1);
        temp = delete_max_heap(&heap).key;
        (sorted + n - i - 1)->key = temp;
        printf("Ãâ·Â %2d:", temp);
        for (int i = 1; i < heap.heap_size + 1; i++) {
            printf("%4d", heap.heap[i].key);
        }
        printf("\n");
    }

    printf("<<<<<<<<<<<< Sorted List >>>>>>>>>>>>>\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", (sorted + i)->key);
    }

    free(sorted);
    return 0;
}