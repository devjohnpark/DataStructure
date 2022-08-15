#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE    0

typedef int Data;

typedef struct _node
{
    Data data;
    struct _node * next;
    struct _node * prev;
} Node;

typedef struct _dbLinkedList
{
    Node * head;
    Node * cur;
    int numOfData;
} DBLinkedList;

typedef DBLinkedList List;

void ListInit(List * plist)
{
    plist->head = NULL;
    plist->numOfData = 0;
}

void LInsert(List * plist, Data data)
{
    Node * newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    newNode->next = plist->head;
    if(plist->head != NULL)
        plist->head->prev = newNode;

    newNode->prev = NULL;
    plist->head = newNode;

    (plist->numOfData)++;
}

int LFirst(List * plist, Data * pdata)
{
    if(plist->head == NULL)
        return FALSE;

    plist->cur = plist->head;
    *pdata = plist->cur->data;

    return TRUE;
}

int LNext(List * plist, Data * pdata)
{
    if(plist->cur->next == NULL)
        return FALSE;

    plist->cur = plist->cur->next;
    *pdata = plist->cur->data;

    return TRUE;
}

int LPrevious(List * plist, Data * pdata)
{
    if(plist->cur->prev == NULL)
        return FALSE;

    plist->cur = plist->cur->prev;
    *pdata = plist->cur->data;

    return TRUE;
}

int LCount(List * plist)
{
    return plist->numOfData;
}

int main(void)
{
    // æÁπÊ«‚ ø¨∞· ∏ÆΩ∫∆Æ¿« ª˝º∫ π◊ √ ±‚»≠  ///////
    List list;
    int data;
    ListInit(&list);

    // 8∞≥¿« µ•¿Ã≈Õ ¿˙¿Â  ///////
    LInsert(&list, 1);  LInsert(&list, 2);
    LInsert(&list, 3);  LInsert(&list, 4);
    LInsert(&list, 5);  LInsert(&list, 6);
    LInsert(&list, 7);  LInsert(&list, 8);

    // ¿˙¿Âµ» µ•¿Ã≈Õ¿« ¡∂»∏  ///////
    if(LFirst(&list, &data))
    {
        printf("%d ", data);

        while(LNext(&list, &data))
            printf("%d ", data);
        
        while(LPrevious(&list, &data))
            printf("%d ", data);
        
        printf("\n\n");
    }

    return 0;
}
