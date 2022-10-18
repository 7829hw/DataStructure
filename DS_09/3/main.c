#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s)                            \
    if (!((p) = malloc(s))) {                   \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE);                     \
    }

typedef struct node* nodePointer;
typedef struct node {
    nodePointer llink;
    int data;
    nodePointer rlink;
} node;
nodePointer header = NULL;

void dinsert(nodePointer node, nodePointer newnode);
void ddelete(nodePointer node, nodePointer deleted);
void printForward(nodePointer header);
void printBackward(nodePointer header);

int main(void)
{
    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");

    int temp;
    nodePointer newnode;

    MALLOC(header, sizeof(*header));
    header->rlink = header;
    header->llink = header;
    while (fscanf_s(fp, "%d", &temp) != EOF) {
        MALLOC(newnode, sizeof(*newnode));
        newnode->data = temp;
        dinsert(header->llink, newnode);
    }
    printf("After creating a doubly linked circular list with a head node :\n");
    printForward(header);
    printf("\n");
    printBackward(header);

    printf("After deleting numbers less than and equal to 50 :\n");
    if (header->rlink->data <= 50)
        ddelete(header, header->rlink);
    nodePointer tmp, curr = header->rlink;
    while (curr->rlink != header) {
        if (curr->data <= 50) {
            tmp = curr->llink;
            ddelete(curr->llink, curr);
            curr = tmp->rlink;
        } else {
            curr = curr->rlink;
        }
    }

    printForward(header);
    printBackward(header);

    fclose(fp);
    return 0;
}

void dinsert(nodePointer node, nodePointer newnode)
{
    newnode->llink = node;
    newnode->rlink = node->rlink;
    node->rlink->llink = newnode;
    node->rlink = newnode;
}

void ddelete(nodePointer node, nodePointer deleted)
{
    if (node == deleted) {
        printf("Deletion of header node not permitted.\n");
    } else {
        deleted->llink->rlink = deleted->rlink;
        deleted->rlink->llink = deleted->llink;
        free(deleted);
    }
}

void printForward(nodePointer header)
{
    printf("forward\n");
    int i = 1;
    nodePointer curr = header->rlink;
    while (curr != header) {
        printf("(%p %5d %p)   ", curr, curr->data, curr->rlink);
        if (i % 4 == 0)
            printf("\n");
        curr = curr->rlink;
        i++;
    }
    printf("\n");
}

void printBackward(nodePointer header)
{
    printf("backward\n");
    int i = 1;
    nodePointer curr = header->llink;
    while (curr != header) {
        printf("(%p %5d %p)   ", curr, curr->data, curr->llink);
        if (i % 4 == 0)
            printf("\n");
        curr = curr->llink;
        i++;
    }
    printf("\n");
}