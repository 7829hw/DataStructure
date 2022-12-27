#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
#define INF 1000
#define MAX_ELEMENT 100

#define HEAP_FULL(n) (n == MAX_ELEMENT - 1)
#define HEAP_EMPTY(n) (!n)

// heap element
typedef struct {
    int key; // weighted value
    int u; // vertex 1
    int v; // vertex 2
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;
// ...
int parent[MAX_ELEMENT];

void init(HeapType* h)
{
    (*h).heap_size = 0;
}

void set_init(int n)
{
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

// insertion into a min heap
void insert_min_heap(HeapType* h, element item)
{ /* insert item into a max heap of current size *n */
    // printf("heap size = %d\n", (*h).heap_size);
    // printf("%d %d %d\n", item.u, item.v, item.key);
    int i;
    if (HEAP_FULL((*h).heap_size)) {
        fprintf(stderr, "The heap is full. \n");
        exit(EXIT_FAILURE);
    }

    i = ++((*h).heap_size);

    while ((i != 1) && (item.key < (*h).heap[i / 2].key)) {
        (*h).heap[i] = (*h).heap[i / 2];
        i /= 2;
    }
    (*h).heap[i] = item;
}

// Program 5.14: Deletion from a max heap
element delete_min_heap(HeapType* h)
{ /* delete element with the smallest key from the heap */
    int parent, child;
    element item, temp;
    if (HEAP_EMPTY((*h).heap_size)) {
        fprintf(stderr, "The heap is empty. \n");
        exit(EXIT_FAILURE);
    }

    /* save value of the element with the smallest key */
    item = (*h).heap[1];

    /* use last elementin heap to adjust heap */
    temp = (*h).heap[(*h).heap_size--];
    parent = 1;
    child = 2;

    while (child <= (*h).heap_size) { /* find the smaller child of he current parent */
        if ((child < (*h).heap_size) && ((*h).heap[child].key > (*h).heap[child + 1].key))
            child++;
        if (temp.key <= (*h).heap[child].key)
            break;
        /* move to the next lower level */
        (*h).heap[parent] = (*h).heap[child];
        parent = child;
        child *= 2;
    }

    (*h).heap[parent] = temp;
    return item;
}

// insert edge in heap
void insert_heap_edge(HeapType* h, int u, int v, int weight)
{
    element e;
    e.u = u;
    e.v = v;
    e.key = weight;
    insert_min_heap(h, e);
}
// make heap
void insert_all_edges(HeapType* h)
{
    int u, v, weight_value;
    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");
    fgetc(fp);
    while (!feof(fp)) {
        fscanf_s(fp, "%d %d %d", &u, &v, &weight_value);
        // printf("%d %d %d\n", u, v, weight_value);
        insert_heap_edge(h, u, v, weight_value);
    }
}

int simpleFind(int i)
{
    for (; parent[i] >= 0; i = parent[i])
        ;
    return i;
}

void simpleUnion(int i, int j)
{
    parent[i] = j;
}

void kruskal(int n)
{
    int sum = 0;
    int edge_accepted = 0; // number of selected edge
    HeapType h; // min heap
    int uset, vset; // root of vertex
    element e; // heap elemnet
    init(&h); // init heap
    insert_all_edges(&h); // make heap
    set_init(n); // initialize union-find funtion.
    while (edge_accepted < (n - 1)) // number of edge < (n-1)
    {
        e = delete_min_heap(&h); // get a vertex from heap
        uset = simpleFind(e.u); // find() root
        vset = simpleFind(e.v); // find() root
        if (uset != vset) { // different root
            printf("(%d,%d) %d \n", e.u, e.v, e.key);
            edge_accepted++;
            sum += e.key;
            simpleUnion(uset, vset); // union two vertices.
        }
    }
    printf("\n최소비용 :%3d\n", sum);
}

main()
{
    int n;
    int u1, u2, dummy;
    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");
    fscanf_s(fp, "%d", &n);
    int max = -1;
    while (!feof(fp)) {
        fscanf_s(fp, "%d %d %d", &u1, &u2, &dummy);
        if (u1 > max)
            max = u1;
        if (u2 > max)
            max = u2;
    }
    rewind(fp);
    fscanf_s(fp, "%d", &dummy);
    kruskal(max + 1); // number of node
}