//
//  CircleQueue.c
//  Queue
//
//  Created by Junseo Park on 2022/06/03.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element;

/*--- 큐를 구현하는 구조체 ---*/
typedef struct {
    int max;    /* 큐의 최대 용량 */
    int front;    /* 프론트 */
    int rear;    /* 리어 */
    element *que;    /* 큐의 첫 요소에 대한 포인터 */
} Queue;


void initialize(Queue *q, int max) {
    q->front = q->rear = 0;
    if ((q->que = calloc(max, sizeof(element))) == NULL) {
        q->max = 0;
    }
    else
        q->max = max;
}

int isFull(Queue *q) {
    return q->front == (q->rear + 1) % q->max;
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

void print(Queue *q) {
    for (int i=0; i<q->max; i++)
        printf(" %d", q->que[i]);
    printf("\n");
}

void terminate(Queue *q) {
    q->max = q->front = q->rear = 0;
    if (q->que != NULL)
        free(q->que); // free memory to allocate
}

void enqueue(Queue *q, element item) {
    if (isFull(q)) {
        printf("overflow");
        print(q);
        terminate(q);
        exit(-1);
    }
    else {
        q->rear = (q->rear + 1) % q->max;
        q->que[q->rear] = item;
    }
    
}

void dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("underflow");
        terminate(q);
        exit(-1);
    }
    else {
        q->front = (q->front + 1) % q->max;
        q->que[q->front] = 0;
    }
}

/*--- 큐의 최대 용량 ---*/
int capacity(Queue *q)
{
    return q->max;
}

int main() {
    int qNum, orderNum;
    int num;
    char order;
    Queue q;
    
    scanf("%d", &qNum);
    scanf("%d", &orderNum);
    
    initialize(&q, qNum);
    
    for (int i=0; i<orderNum; i++) {
        getchar();
        scanf("%c", &order);
        switch (order) {
            case 'I':
                scanf("%d", &num);
                enqueue(&q, num);
                break;
            case 'D':
                dequeue(&q);
                break;
            case 'P':
                print(&q);
                break;
            default:
                break;
        }
    }
    
    terminate(&q);
    
    return 0;
}
