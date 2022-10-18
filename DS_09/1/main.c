#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s)                            \
    if (!((p) = malloc(s))) {                   \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE);                     \
    }

typedef struct element {
    char fruit[20];
    char country[20];
    int price;
} element;

typedef struct listNode* listPointer;
typedef struct listNode {
    element data;
    listPointer link;
};

listPointer first = NULL;

void add(listPointer* first, element data);
void printList(listPointer first);
void searchList(listPointer first, char country[]);
listPointer invert(listPointer lead);

int main(void)
{
    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");

    char S[20];

    element temp;
    while (fscanf_s(fp, "%s %s %d", temp.fruit, 19, temp.country, 19, &temp.price) != EOF) {
        add(&first, temp);
    }

    printf("순방향 출력\n");
    printList(first);

    printf("나라이름을 입력하세요 : ");
    scanf_s("%s", S, 19);
    searchList(first, S);

    first = invert(first);
    printf("역방향 출력\n");
    printList(first);

    fclose(fp);
    return 0;
}

void add(listPointer* first, element data)
{
    listPointer tmp = NULL;
    MALLOC(tmp, sizeof(*tmp));
    tmp->data = data;
    tmp->link = NULL;
    if (*first == NULL) {
        *first = tmp;
    } else {
        tmp->link = *first;
        *first = tmp;
    }
}

void printList(listPointer first)
{
    int i = 1;
    listPointer curr = first;
    while (curr != NULL) {
        printf("%p(%s, %s, %d, %p) => ", curr, curr->data.fruit, curr->data.country, curr->data.price, curr->link);
        if (i % 2 == 0)
            printf("\n");
        curr = curr->link;
        i++;
    }
    printf(" \n\n");
}

void searchList(listPointer first, char country[])
{
    listPointer curr = first;
    while (curr->link != NULL) {
        if (!strcmp(country, curr->data.country))
            printf("%s, ", curr->data.fruit);
        curr = curr->link;
    }
    printf("\n\n");
}

listPointer invert(listPointer lead)
{
    listPointer middle, trail;
    middle = NULL;
    while (lead) {
        trail = middle;
        middle = lead;
        lead = lead->link;
        middle->link = trail;
    }
    return middle;
}