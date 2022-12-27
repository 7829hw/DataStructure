#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 500

#define MALLOC(p, s)                            \
    if (!((p) = malloc(s))) {                   \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE);                     \
    }

void initWinnertree(int* winner, int n);
void inorder(int* tree, int index, int origin);

int main(void)
{
    int n;
    unsigned int seed;
    int* key;
    int* winner;
    int* sorted;
    printf("<<<<<<<<<<<<< sorting with winner tree >>>>>>>>>>>>>>\n\n");
    printf("the number of keys ( 4, 8, 16, or 32 as a power of 2 )  >> ");
    scanf_s("%d", &n);
    printf("%s", "value of seed >>  ");
    scanf_s("%u", &seed);
    srand(seed);
    MALLOC(key, n * sizeof(int));
    MALLOC(sorted, n * sizeof(int));
    for (int i = 0; i < n; i++) {
        key[i] = rand() % MAX_SIZE + 1;
        printf("%5d", key[i]);
    }
    printf("\n\ninitialization of min-winner tree\n");
    MALLOC(winner, 2 * n * sizeof(int));
    for (int i = 0; i < n; i++) {
        winner[n + i] = key[i];
    }
    initWinnertree(winner, n);

    printf("\ninorder traversal for min-winner tree\n");
    initWinnertree(winner, n);
    inorder(winner, 1, n);

    for (int i = 0; i < n; i++) {
        sorted[i] = winner[1];
        for (int j = 1; j < 2 * n; j++) {
            if (winner[j] == sorted[i])
                winner[j] = 9999;
        }
        initWinnertree(winner, n);
        if (i == 1) {
            printf("\nWinner Tree inorder traversal after find 2 winners...\n");
            inorder(winner, 1, n);
        }
    }

    printf("\n\nsorting with min-winner tree...\n");
    printf("\nsorted result\n");
    for (int i = 0; i < n; i++) {
        printf("%5d", sorted[i]);
    }

    free(key);
    free(winner);
    free(sorted);
    return 0;
}

void initWinnertree(int* winner, int n)
{
    int depth = n;
    while (depth > 1) {
        depth /= 2;
        for (int i = depth; i < 2 * depth; i++) {
            winner[i] = winner[2 * i] < winner[2 * i + 1] ? winner[2 * i] : winner[2 * i + 1];
        }
    }
}

void inorder(int* tree, int index, int origin)
{
    if (index < 2 * origin) {
        inorder(tree, 2 * index, origin);
        printf("%5d", tree[index]);
        inorder(tree, 2 * index + 1, origin);
    }
}