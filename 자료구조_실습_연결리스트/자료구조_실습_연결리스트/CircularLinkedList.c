//
//  CircularLinkeList.c
//  자료구조_실습_연결리스트
//
//  Created by Junseo Park on 2022/04/26.
//

/* Program using circular doubly linked list */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*--- Data data ---*/
typedef struct {
    int num;
    int numbers[100];
    char ch;
    char str[100];
} Data;

/*--- Node ---*/
typedef struct __node {
    Data data;            /* data */
    struct __node *next;    /* pointer to next node */
} Node;

/*--- List manage circular doubly linked list ---*/
typedef struct {
    Node *head;    /* pointer for head dummy node */
    Node *crnt;    /* pointer for selected node */
    Node *tail;
    int cnt;
} List;

/*--- Number comapre ---*/
int DataNumCmp(Data * x, Data * y)
{
    return x->num < y->num ? -1 : x->num > y->num ? 1 : 0;
}

/*--- Numbers comapre ---*/
int DataNumbersCmp(Data * x, Data * y)
{
    // 조정
    return 0;
}

/*--- Character compare ---*/
int DataChCmp(Data * x, Data * y)
{
    // 조정
    return 0;
}

/*--- String compare ---*/
int DataStrCmp(Data * x, Data * y)
{
    return strcmp(x->str, y->str);
}

/*--- search for a node equal to x with compare function ---*/
Node* search(List* list, Data* x, int compare(Data* x, Data* y))
{
    Node* p = list->head->next;
    while (p != list->head) {
        if (compare(&p->data, x) == 0) {
            list->crnt = p;
            return p;     /* searh sucess */
        }
        p = p->next;
    }
    return NULL;        /* searh fail */
}

/*--- create node dynamically ---*/
static Node* AllocNode(void)
{
    return calloc(1, sizeof(Node));
}

/*--- set a value each Data of node point to by n ---*/
static void SetNode(Node* n, Data* x, Node* next)
{
    n->data = *x;   /* data */
    n->next = next; /* next node pointer */
}

/*--- is empty? ---*/
static int IsEmpty(List* list)
{
    return list->head == NULL;
}

/*--- list initialize ---*/
void Initialize(List* list)
{
    list->head = NULL;
    list->crnt = NULL;
    list->cnt = 0;
}

// Search equal data
Node *Search(List *list, Data *x, int compare(Data *x, Data *y)) {
    Node *p = list->head;
    while (!IsEmpty(list) && p->next != list->head) {
        if (compare(&p->data, x) == 0) {
            list->crnt = p;
            return p;
        }
        p = p->next;
    }
    return NULL;
}

void InsertHead(List *list, Data *x) {
    Node *p = list->head;   // next node
    list->head = list->crnt = AllocNode();  // create head node
    if (p == NULL) {
        p = list->head;
        list->tail = p;
    }
    else {
        Node *tmp = p; // head 노드
        while (tmp->next != p)
            tmp = tmp->next;
        tmp->next = list->head;
        // p 마지막 노드
    }
    SetNode(list->head, x, p); // set head node (data, next node)
    list->cnt++;
}

// insert node to middle
// 찾은 노드 위에 삽입
void InsertAfter(List *list, Node *prev, Data *x) {
    // prev 뒤에 노드 삽입
    // prev 설정
    if (list->head == NULL) // 헤드 이미 있어도 헤드에 삽입할 경우 조건문에 코드 추가
        InsertHead(list, x);
    else {
        Node *p = prev->next; // save next node
        prev->next = list->crnt = AllocNode(); // create new node to insert
        SetNode(prev->next, x, p);
    }
}

// insert node to tail
void InsertTail(List *list, Data *x) {
    if (list->head == NULL)
        InsertHead(list, x);
    else {
        Node *p = list->head;
        while (p->next != list->head)
            p = p->next;
        InsertAfter(list, p, x);
    }
}

// delete head node
void DeleteHead(List *list) {
    if (list->head != NULL) {
        Node *p = list->head;
        if (list->head->next == list->head)
            list->head = NULL;
        else {
            list->head = list->head->next;
            Node *tmp = p; // head 노드
            while (tmp->next != p)
                tmp = tmp->next;
            tmp->next = list->head;
        }
        list->cnt--;
        free(p);
    }
    else {
        // printf
    }
}

// delete tail node
void DeleteTail(List *list) {
    if (list->head != NULL) {
        if (list->head == list->head->next)
            DeleteHead(list);
        else {
            Node *prev = NULL;
            Node *p = list->head;
            while (p->next != list->head) {
                prev = p;
                p = p->next;
            }
            prev->next = list->head; /* in front of tail node */
            free(p);    // free tail node
            list->crnt = prev;
            list->cnt--;
        }
    }
}

// 해당 노드 뒤 삭제
void DeleteAfter(List *list, Node * prev) {
    if (list->head != NULL) {
        Node *p = prev->next;
        prev->next = p->next;
        // 첫번째 노드 삭제시
        if (p == list->head) {
            list->head = p->next;
        }
        free(p);
        list->crnt = prev;
        list->cnt--;
    }
    else {
        // printf
    }
}

void DeleteCurrent(List *list) {
    // 삭제할 노드 list->crnt에 담는다.
    if (list->head != NULL) {
        if (list->crnt == list->head)
            DeleteHead(list);
        else {
            Node *p = list->head;
            while (p->next != list->crnt && p->next != list->head) {
                p = p->next;
            }
            if (p->next == list->crnt) {
                p->next = list->crnt->next;
                free(list->crnt);
                list->crnt = p;
                list->cnt--;
            }
        }
    }
    else {
        // printf
    }
}

void Reverse(List *list) {
    if (list->head != NULL) {
        Node *p = list->head->next;
        Node *q = NULL;
        Node *r = NULL;
        while (p != list->head) {
            r = q;
            q = p;
            p = p->next;    // 다음 노드 이동
            q->next = r;    // 그 전 노드 가리킴
        }
        list->head->next = q; // head node
        list->head = q; // last node
    }
}


void PrintAll(List *list) {
    if (list->head == NULL) {
        // 노드 없을때 printf 구문
    }
    else {
        // 노드 있을때 printf 구문
        Node *p = list->head;
//        while (p->next != list->head) {
//            printf("%d\n", p->data.num);
//            p = p->next;
//        }
//        printf("%d\n", p->data.num);
        int cnt = 0;
        while (cnt < 20) {
            printf("%d\n", p->data.num);
            p = p->next;
            cnt++;
        }
    }
}

void PrintCurrent(List *list) {
    // list->crnt 설정 후
    if (list->crnt == NULL) {
        // 노드 없을때 printf 구문
    }
    else {
        // printf 구문 list->crnt
        printf("%d\n", list->crnt->data.num);
    }
}

/*--- print data of all nodes list in reverse order ---*/
void PrintReverse(List* list)
{
    Reverse(list);
    PrintAll(list);
}

void Terminate(List *list) {
    while (list->head != NULL)    /* until empty */
        DeleteHead(list);    /* delete head node */
    list->crnt = NULL;
}

/*--- main ---*/
int main(void)
{
    Data x;
    List list;
    Initialize(&list);  /* initialize circular doubly linked list */
    x.num = 0;
    for (int i = 0; i < 10; i++) {
        x.num = i;
        InsertTail(&list, &x);
//        InsertHead(&list, &x);
    }
    
    PrintAll(&list);
    
    Reverse(&list);
    
    PrintAll(&list);
    
//    PrintAll(&list);
//
//    DeleteTail(&list);
//
//    PrintAll(&list);
//
//    DeleteTail(&list);
//
//    PrintAll(&list);
    
    Terminate(&list);   /* terminate circular doubly linked list */

    return 0;
}



