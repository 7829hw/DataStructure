#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 20

#define MALLOC(p, s)                            \
    if (!((p) = malloc(s))) {                   \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE);                     \
    }

typedef struct node* treePointer;
typedef struct node {
    char data;
    treePointer leftChild, rightChild;
} node;

treePointer root = NULL;
treePointer queue[MAX_QUEUE_SIZE] = { NULL };
int front = -1;
int rear = -1;

void enqueue(treePointer ptr);
treePointer dequeue(void);

void insert(treePointer ptr);
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);

int main(void)
{
    printf("creating a complete binary tree\n");

    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");

    treePointer temp;
    char C;

    while ((C = fgetc(fp)) != EOF) {
        MALLOC(temp, sizeof(*temp));
        temp->data = C;
        temp->leftChild = NULL;
        temp->rightChild = NULL;
        insert(temp);
    }

    printf("\nthree binary tree traversals\n");
    printf("inorder traversal    :");
    inorder(root);
    printf("\n");

    printf("preorder traversal   :");
    preorder(root);
    printf("\n");

    printf("postorder traversal  :");
    postorder(root);
    printf("\n");

    fclose(fp);
    return 0;
}

void enqueue(treePointer ptr)
{
    queue[++rear] = ptr;
}

treePointer dequeue(void)
{
    return queue[++front];
}

void insert(treePointer ptr)
{
    if (!root) {
        root = ptr;
    } else {
        treePointer temp = queue[front + 1];
        if (!temp->leftChild) {
            temp->leftChild = ptr;
        } else if (!temp->rightChild) {
            temp->rightChild = ptr;
            dequeue();
        }
    }
    enqueue(ptr);
}

void inorder(treePointer ptr)
{
    if (ptr) {
        inorder(ptr->leftChild);
        printf(" %c", ptr->data);
        inorder(ptr->rightChild);
    }
}

void preorder(treePointer ptr)
{
    if (ptr) {
        printf(" %c", ptr->data);
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }
}

void postorder(treePointer ptr)
{
    if (ptr) {
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        printf(" %c", ptr->data);
    }
}