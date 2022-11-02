#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MALLOC(p, s)                            \
    if (!((p) = malloc(s))) {                   \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE);                     \
    }

typedef struct threadTree* threadedPointer;
typedef struct threadTree {
    short int leftThread;
    threadedPointer leftChild;
    char data;
    threadedPointer rightChild;
    short int rightThread;
};

threadedPointer insucc(threadedPointer tree);
void tinorder(threadedPointer tree);

int main(void)
{
    threadedPointer node[10] = { NULL };
    for (int i = 0; i < 10; i++) {
        MALLOC(node[i], sizeof(*node[0]));
    }
    node[0]->leftThread = FALSE;
    node[0]->leftChild = node[1];
    node[0]->data = ' ';
    node[0]->rightChild = node[0];
    node[0]->rightThread = FALSE;

    node[1]->leftThread = FALSE;
    node[1]->leftChild = node[2];
    node[1]->data = 'A';
    node[1]->rightChild = node[3];
    node[1]->rightThread = FALSE;

    node[2]->leftThread = FALSE;
    node[2]->leftChild = node[4];
    node[2]->data = 'B';
    node[2]->rightChild = node[5];
    node[2]->rightThread = FALSE;

    node[3]->leftThread = FALSE;
    node[3]->leftChild = node[6];
    node[3]->data = 'C';
    node[3]->rightChild = node[7];
    node[3]->rightThread = FALSE;

    node[4]->leftThread = FALSE;
    node[4]->leftChild = node[8];
    node[4]->data = 'D';
    node[4]->rightChild = node[9];
    node[4]->rightThread = FALSE;

    node[5]->leftThread = TRUE;
    node[5]->leftChild = node[2];
    node[5]->data = 'E';
    node[5]->rightChild = node[1];
    node[5]->rightThread = TRUE;

    node[6]->leftThread = TRUE;
    node[6]->leftChild = node[1];
    node[6]->data = 'F';
    node[6]->rightChild = node[3];
    node[6]->rightThread = TRUE;

    node[7]->leftThread = TRUE;
    node[7]->leftChild = node[3];
    node[7]->data = 'G';
    node[7]->rightChild = node[0];
    node[7]->rightThread = TRUE;

    node[8]->leftThread = TRUE;
    node[8]->leftChild = node[0];
    node[8]->data = 'H';
    node[8]->rightChild = node[4];
    node[8]->rightThread = TRUE;

    node[9]->leftThread = TRUE;
    node[9]->leftChild = node[4];
    node[9]->data = 'I';
    node[9]->rightChild = node[2];
    node[9]->rightThread = TRUE;

    tinorder(node[0]);

    for (int i = 0; i < 10; i++) {
        free(node[i]);
    }
    return 0;
}

threadedPointer insucc(threadedPointer tree)
{
    threadedPointer temp;
    temp = tree->rightChild;
    if (!tree->rightThread)
        while (!temp->leftThread)
            temp = temp->leftChild;
    return temp;
}

void tinorder(threadedPointer tree)
{
    threadedPointer temp = tree;
    for (;;) {
        printf("%p(%d, %p, %c, %d, %p)\n", temp, temp->leftThread, temp->leftChild, temp->data, temp->rightThread, temp->rightChild);
        temp = insucc(temp);
        if (temp == tree)
            break;
        // printf("%c", temp->data);
    }
}