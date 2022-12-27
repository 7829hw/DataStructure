#include <stdio.h>
#include <stdlib.h>
#define MAX_BUCKET 8

typedef struct {
    // char item[10];
    int key;
} element;

int randNum[MAX_BUCKET];
int seed;
element* ht[MAX_BUCKET] = { NULL };
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

int s(int i)
{
    return randNum[i];
}

element* search(int k)
{
    int i;
    int b = MAX_BUCKET;
    int homeBucket, currentBucket;
    homeBucket = h(k);
    for (i = 1, currentBucket = homeBucket; ht[currentBucket] && ht[currentBucket]->key != k; i++) {
        cnt++;
        currentBucket = (currentBucket + s(i)) % b;
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
    int random_number;
    int i, j, index;
    int temp = -1, search_result;
    int n = 0;
    element keys[MAX_BUCKET];
    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");
    printf("key sequence from file :");
    for (i = 0; !feof(fp); i++) {
        fscanf_s(fp, "%d", &keys[i].key);
        printf("%5d", keys[i].key);
    }
    n = i;

    printf("\ninput seed >> ");
    scanf_s("%d", &seed);
    srand(seed);

    for (i = 1; i < MAX_BUCKET; i++) {
        randNum[i] = rand() % (MAX_BUCKET - 1) + 1;
        for (j = 1; j < i; j++) {
            if (randNum[i] == randNum[j]) {
                i--;
            }
        }
    }

    printf("\n");
    for (i = 1; i < MAX_BUCKET; i++) {
        printf("randNum[%d] :%3d\n", i, s(i));
    }

    for (i = 0; i < n; i++) {
        index = h(keys[i].key);
        for (j = 1; ht[index]; j++) {
            index = (h(keys[i].key) + s(j)) % MAX_BUCKET;
        }
        ht[index % MAX_BUCKET] = &keys[i];
    }

    printf("\n          key\n");
    for (i = 0; i < MAX_BUCKET; i++) {
        printf("ht[%2d] :", i);
        if (ht[i])
            printf("%4d", ht[i]->key);
        printf("\n");
    }

    for (;;) {
        cnt = 0;
        printf("\ninput 0 to quit\n");
        printf("key to search >> ");
        scanf_s("%d", &temp);
        if (temp == 0)
            break;
        search_result = search(temp);
        if (search_result)
            printf("key : %d, the number of comparisons : %d\n", temp, cnt);
        else
            printf("it doesn't exist!\n");
    }
}