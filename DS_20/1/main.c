#include <stdio.h>
#define MAX_BUCKET 11
#define MAX_LEN 10

typedef struct {
    char item[10];
    int key;
} element;

element* ht[MAX_BUCKET] = { NULL };
int cnt = 0;

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
    int b = MAX_BUCKET;
    int homeBucket, currentBucket;
    homeBucket = h(k);
    for (currentBucket = homeBucket; ht[currentBucket] && ht[currentBucket]->key != k;) {
        cnt++;
        currentBucket = (currentBucket + 1) % b;
        if (currentBucket == homeBucket)
            return NULL;
    }
    if (ht[currentBucket] && ht[currentBucket]->key == k) {
        cnt++;
        return ht[currentBucket];
    }
    return NULL;
}

int main(void)
{
    element input[MAX_LEN];
    element temp;
    element* search_result = NULL;
    int i, index;
    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");
    printf(" Input strings :");
    for (i = 0; !feof(fp); i++) {
        fscanf_s(fp, "%s", input[i].item, 10);
        printf(" %s", input[i].item);
        input[i].key = stringToInt(input[i].item);
        index = h(input[i].key);
        while (ht[index] && index < MAX_BUCKET) {
            index++;
        }
        ht[index % MAX_BUCKET] = &input[i];
    }

    printf("\n             item     key\n");
    for (i = 0; i < MAX_BUCKET; i++) {
        printf("ht[%2d] :", i);
        if (ht[i])
            printf("%9s%8d", ht[i]->item, ht[i]->key);
        printf("\n");
    }

    printf("\nstring to search >> ");
    scanf_s("%s", temp.item, 10);
    temp.key = stringToInt(temp.item);
    search_result = search(temp.key);
    if (search_result)
        printf("item: %s, key : %d, the number of comparisions :%2d", temp.item, temp.key, cnt);
    else
        printf("it doesn't exist!");
}