#include <stdio.h>
#include <stdlib.h>
#define MAX_BUCKET 11
#define MAX_LEN 10

#define MALLOC(p, s)                            \
    if (!((p) = malloc(s))) {                   \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE);                     \
    }

typedef struct {
    char item[10];
    int key;
} element;

typedef struct node* nodePointer;
typedef struct node {
    element data;
    nodePointer link;
};

nodePointer ht[MAX_BUCKET] = { NULL };
int cnt;

// Program 8.1: Converting a string into a non-negative integer
unsigned int stringToInt(char* key)
{ /* simple additive approach to create a natural number
 that is within the integer range */
    int number = 0;
    while (*key)
        number += *key++;
    return number;
}

int h(int k)
{
    return k % MAX_BUCKET;
}

element* search(int k)
{
    nodePointer current;
    int homeBucket = h(k);
    for (current = ht[homeBucket]; current; current = current->link) {
        cnt++;
        if (current->data.key == k)
            return &current->data;
    }

    return NULL;
}

void insertNode(nodePointer* ptr, element input)
{
    nodePointer temp, curr;
    MALLOC(temp, sizeof(*temp));
    temp->data = input;
    temp->link = NULL;

    if (!*ptr) {
        *ptr = temp;
        return;
    } else {
        curr = *ptr;
        while (curr->link != NULL)
            curr = curr->link;
        curr->link = temp;
    }
}

int main(void)
{
    nodePointer curr;
    element input;
    char temp[MAX_LEN];
    element* search_result = NULL;
    int i, index;
    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");
    printf(" input strings :");
    for (i = 0; !feof(fp); i++) {
        fscanf_s(fp, "%s", input.item, 10);
        printf(" %s", input.item);
        input.key = stringToInt(input.item);
        insertNode(&ht[h(input.key)], input);
    }

    printf("\n\n          item  key\n");
    for (i = 0; i < MAX_BUCKET; i++) {
        curr = ht[i];
        printf("ht[%2d] :", i);
        while (curr != NULL) {
            printf(" (%s %d) ", curr->data.item, curr->data.key);
            curr = curr->link;
        }
        printf("\n");
    }

    for (;;) {
        cnt = 0;
        printf("input \"quit\" to quit\n");
        printf("string to search >> ");
        scanf_s("%s", temp, MAX_LEN);
        if (!strcmp(temp, "quit"))
            break;
        search_result = search(stringToInt(temp));
        if (search_result)
            printf("item: %s, key : %d, the number of comparisons : %d\n", temp, stringToInt(temp), cnt);
        else
            printf("it doesn't exist!\n");
        printf("\n");
    }

    return 0;
}