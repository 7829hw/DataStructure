#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 500

#define MALLOC(p, s)                            \
    if (!((p) = malloc(s))) {                   \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE);                     \
    }

typedef int iType;
typedef struct {
    int key;
    iType item;
} element;
typedef struct node* treePointer;
typedef struct node {
    element data;
    treePointer leftChild, rightChild;
} tNode;

treePointer modifiedSearch(treePointer node, int k);
void insert(treePointer* node, int k, iType theItem);
int* search(treePointer root, int k);
void inorder(treePointer ptr);

int main(void)
{
    int n;
    unsigned int seed;
    int key;
    treePointer root = NULL;

    printf("random number generation (1 ~ %d)\n", MAX_SIZE);
    printf("%s", "the number of nodes in BST (less than and equal to 50) : ");
    scanf_s("%d", &n);
    printf("%s", "seed : ");
    scanf_s("%u", &seed);
    printf("\ncreating a BST from random numbers\n");
    srand(seed);
    printf("generating number : ");
    for (int i = 0; i < n; i++) {
        key = rand() % MAX_SIZE + 1;
        printf("%4d", key);
        insert(&root, key, NULL);
    }

    printf("\nthe key to search : ");
    scanf_s("%d", &key);
    printf("the search process : ");
    if (search(root, key))
        printf("\nthe element is in BST");
    else
        printf("\nthe element is not in BST");

    printf("\n\ninorder traversal of the BST shows the sorted sequence\n");
    inorder(root);

    return 0;
}

treePointer modifiedSearch(treePointer node, int k)
{
    while (node) {
        if (k == node->data.key)
            return NULL;
        if ((k < node->data.key && node->leftChild == NULL) || (k > node->data.key && node->rightChild == NULL))
            return node;
        if (k < node->data.key)
            node = node->leftChild;
        else
            node = node->rightChild;
    }
    return NULL;
}

void insert(treePointer* node, int k, iType theItem)
{
    treePointer ptr, temp = modifiedSearch(*node, k);
    if (temp || !(*node)) {
        MALLOC(ptr, sizeof(*ptr));
        ptr->data.key = k;
        ptr->data.item = theItem;
        ptr->leftChild = ptr->rightChild = NULL;
        if (*node)
            if (k < temp->data.key)
                temp->leftChild = ptr;
            else
                temp->rightChild = ptr;
        else
            *node = ptr;
    }
}

int* search(treePointer root, int k)
{
    if (!root)
        return NULL;
    printf("%d => ", root->data.key);
    if (k == root->data.key)
        return &root->data;
    if (k < root->data.key)
        return search(root->leftChild, k);
    return search(root->rightChild, k);
}

void inorder(treePointer ptr)
{
    if (ptr) {
        inorder(ptr->leftChild);
        printf("%4d", ptr->data.key);
        inorder(ptr->rightChild);
    }
}