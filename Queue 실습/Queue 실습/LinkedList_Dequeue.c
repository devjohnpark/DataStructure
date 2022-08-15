//
//  2.c
//  Queue 실습
//
//  Created by Junseo Park on 2022/06/05.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef int Data;

typedef struct _node
{
    Data data;
    struct _node * next;
    struct _node * prev;
} Node;

typedef struct _dlDeque
{
    Node * front;
    Node * rear;
} DLDeque;

typedef DLDeque Deque;

void DequeInit(Deque * pdeq);
int DQIsEmpty(Deque * pdeq);

void DQAddFirst(Deque * pdeq, Data data);
void DQAddLast(Deque * pdeq, Data data);

void DQRemoveFirst(Deque * pdeq);
void DQRemoveLast(Deque * pdeq);

void Print(Deque * pdeq);

Data DQGetFirst(Deque * pdeq);
Data DQGetLast(Deque * pdeq);

int main(void)
{
    // Deque¿« ª˝º∫ π◊ √ ±‚»≠ ///////
    Deque deq;
    DequeInit(&deq);

    int n;
    Data data;
    char order[3];
    
    scanf("%d", &n);
    
    for (int i=0; i<n; i++) {
        scanf("%s", order);
        if (strcmp(order, "AF") == 0) {
            scanf("%d", &data);
            DQAddFirst(&deq, data);
        }
        else if (strcmp(order, "AR") == 0) {
            scanf("%d", &data);
            DQAddLast(&deq, data);
        }
        else if (strcmp(order, "DF") == 0) {
            DQRemoveFirst(&deq);
        }
        else if (strcmp(order, "DR") == 0) {
            DQRemoveLast(&deq);
        }
        else if (strcmp(order, "P") == 0) {
            Print(&deq);
        }
    }
    
    while(!DQIsEmpty(&deq))
        DQRemoveLast(&deq);

    return 0;
}

void DequeInit(Deque * pdeq)
{
    pdeq->front = NULL;
    pdeq->rear = NULL;
}

int DQIsEmpty(Deque * pdeq)
{
    if(pdeq->front == NULL)
        return TRUE;
    else
        return FALSE;
}

void DQAddFirst(Deque * pdeq, Data data)
{
    Node * newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    newNode->next = pdeq->front;

    if(DQIsEmpty(pdeq))
        pdeq->rear = newNode;
    else
        pdeq->front->prev = newNode;

    newNode->prev = NULL;
    pdeq->front = newNode;
}

void DQAddLast(Deque * pdeq, Data data)
{
    Node * newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    newNode->prev = pdeq->rear;

    if(DQIsEmpty(pdeq))
        pdeq->front = newNode;
    else
        pdeq->rear->next = newNode;

    newNode->next = NULL;
    pdeq->rear = newNode;
}

void DQRemoveFirst(Deque * pdeq)
{
    Node * rnode = pdeq->front;
//    Data rdata = pdeq->front->data;

    if(DQIsEmpty(pdeq))
    {
        printf("underflow");
        exit(-1);
    }

    pdeq->front = pdeq->front->next;
    free(rnode);

    if(pdeq->front == NULL)
        pdeq->rear = NULL;
    else
        pdeq->front->prev = NULL;

//    return rdata;
}

void DQRemoveLast(Deque * pdeq)
{
    Node * rnode = pdeq->rear;
//    Data rdata = pdeq->rear->data;

    if(DQIsEmpty(pdeq))
    {
        printf("underflow");
        exit(-1);
    }

    pdeq->rear = pdeq->rear->prev;
    free(rnode);

    if(pdeq->rear == NULL)
        pdeq->front = NULL;
    else
        pdeq->rear->next = NULL;

//    return rdata;
}

Data DQGetFirst(Deque * pdeq)
{
    if(DQIsEmpty(pdeq))
    {
        printf("Deque Memory Error!");
        exit(-1);
    }

    return pdeq->front->data;
}

Data DQGetLast(Deque * pdeq)
{
    if(DQIsEmpty(pdeq))
    {
        printf("Deque Memory Error!");
        exit(-1);
    }

    return pdeq->rear->data;
}

void Print(Deque * pdeq) {
    Node * pnode = pdeq->front;
    while (pnode != NULL) {
        printf(" %d", pnode->data);
        pnode = pnode->next;
    }
    printf("\n");
}
