#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s)                            \
    if (!((p) = malloc(s))) {                   \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE);                     \
    }

typedef struct node* treePointer;
typedef struct node {
    char data;
    treePointer leftChild, rightChild;
};

void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);

int main(void)
{
    printf("creating a binary tree\n");
    treePointer root, A, B, C, D, E;

    MALLOC(A, sizeof(treePointer*));
    MALLOC(B, sizeof(treePointer*));
    MALLOC(C, sizeof(treePointer*));
    MALLOC(D, sizeof(treePointer*));
    MALLOC(E, sizeof(treePointer*));

    A->data = 'A';
    B->data = 'B';
    C->data = 'C';
    D->data = 'D';
    E->data = 'E';

    root = A;

    A->leftChild = B;
    A->rightChild = C;
    B->leftChild = D;
    B->rightChild = E;
    C->leftChild = NULL;
    C->rightChild = NULL;
    D->leftChild = NULL;
    D->rightChild = NULL;
    E->leftChild = NULL;
    E->rightChild = NULL;

    printf("\nthree binary tree traversals\n");

    printf("inorder traversal     :");
    inorder(root);
    printf("\n\n");

    printf("preorder traversal    :");
    preorder(root);
    printf("\n\n");

    printf("postorder traversal   :");
    postorder(root);
    printf("\n\n");

    return 0;
}

void inorder(treePointer ptr)
{
    if (ptr) {
        inorder(ptr->leftChild);
        printf("\n(%p : %p  %c  %p)", ptr, ptr->leftChild, ptr->data, ptr->rightChild);
        inorder(ptr->rightChild);
    }
}

void preorder(treePointer ptr)
{
    if (ptr) {
        printf("\n(%p : %p  %c  %p)", ptr, ptr->leftChild, ptr->data, ptr->rightChild);
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }
}

void postorder(treePointer ptr)
{
    if (ptr) {
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        printf("\n(%p : %p  %c  %p)", ptr, ptr->leftChild, ptr->data, ptr->rightChild);
    }
}