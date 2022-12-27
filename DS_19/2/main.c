#include <stdio.h>
#include <stdlib.h>

#define BUCKETS 10
#define MAX_QUEUE_SIZE 4

typedef struct queue {
    int front, rear;
    int len;
    int data[MAX_QUEUE_SIZE];
} QueueType;

int is_full(QueueType* queue)
{
    return queue->rear == MAX_QUEUE_SIZE - 1;
}

int is_empty(QueueType* queue)
{
    return queue->rear == queue->front; // 공백상태
}

void enqueue(QueueType* queue, int object)
{
    if (is_full(queue)) {
        fprintf(stderr, "OVERFLOW");
        return;
    }
    queue->data[++queue->rear] = object; // rear값을 증가시킨 후 반환
    queue->len++;
}

int dequeue(QueueType* queue)
{
    if (is_empty(queue)) {
        fprintf(stderr, "UNDERFLOW");
    }
    queue->len--;
    return queue->data[++queue->front]; // front값을 증가시킨 후 반환
}

void init(QueueType* queue)
{
    queue->front = queue->rear = -1;
    queue->len = 0;
}

void radix_sort(int list[], int DIGITS, int n)
{
    int i, j, k, b, d, factor = 1;
    QueueType queues[BUCKETS];
    for (d = 0; d < DIGITS; d++) {
        for (b = 0; b < BUCKETS; b++)
            init(&queues[b]); // initialize Queue

        printf("\nstep %d 자리 ---\n\nQueue의 내용 ---\n", d);
        for (i = 0; i < n; i++) // enqueue
            enqueue(&queues[(list[i] / factor) % 10], list[i]);

        for (j = 0; j < BUCKETS; j++)
            printf("%5d", j);
        printf("\n");
        for (j = MAX_QUEUE_SIZE - 1; j >= 0; j--) {
            for (k = 0; k < BUCKETS; k++) {
                if (queues[k].len > j)
                    printf("%5d", queues[k].data[j]);
                else
                    printf("     ");
            }
            printf("\n\n");
        }
        printf("--------------------------------------------------\n");

        for (b = i = 0; b < BUCKETS; b++) // dequeue
            while (!is_empty(&queues[b]))
                list[i++] = dequeue(&queues[b]);

        for (j = 0; j < n; j++) {
            printf("%5d", list[j]);
        }
        printf("\n");
        factor *= 10; // next digit
    }
}

int main(void)
{
    int d, n, *list;
    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");
    fscanf_s(fp, "%d %d", &d, &n);
    list = malloc(n * sizeof(int));
    printf("input data ---\n");
    for (int i = 0; i < n; i++) {
        fscanf_s(fp, "%d", list + i);
        printf("%5d", list[i]);
    }

    printf("\n");
    radix_sort(list, d, n);

    printf("\nresult ---\n");
    for (int j = 0; j < n; j++) {
        printf("%5d", list[j]);
    }
    printf("\n");

    free(list);
    return 0;
}