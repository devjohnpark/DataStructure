// 이중 연결리스트
/* Program using circular doubly linked list */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Data

typedef struct {
    int num;
    int numbers[100];
    char ch;
    char str[100];
} Data;

// Dnode
typedef struct node {
    Data data;            /* data */
    struct node *prev;    /* pointer to previous node */
    struct node *next;    /* pointer to next node */
} Dnode;

/*--- Dlist manage circular doubly linked list ---*/
typedef struct {
    Dnode *head;    /* pointer for head dummy node */
    Dnode *crnt;    /* pointer for selected node */
    int cnt;
} Dlist;

/*--- list initialize ---*/
void Initialize(Dlist* list)
{
    list->head = NULL;
    list->crnt = NULL;
    list->cnt = 0;
}

/*--- create node dynamically ---*/
static Dnode* AllocDNode(void)
{
    return calloc(1, sizeof(Dnode));
}

/*--- set a value each member of node point to by n ---*/
static void SetDNode(Dnode* n, Data * x, Dnode* prev, Dnode* next)
{
    n->data = *x;   /* data */
    n->prev = prev; /* previous node pointer */
    n->next = next; /* next node pointer */
}

/*--- is empty? ---*/
static int IsEmpty(Dlist* list)
{
    return list->head == NULL;
}

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

/*--- move the current node next one ---*/
int Next(Dlist* list)
{
    if (IsEmpty(list) || list->crnt->next == list->head)
        return 0;
    list->crnt = list->crnt->next;
    return 1;
}

/*--- move the current node previous one ---*/
int Prev(Dlist* list)
{
    if (IsEmpty(list) || list->crnt->prev == list->head)
        return 0;
    list->crnt = list->crnt->prev;
    return 1;
}

/*--- insert node into a head ---*/
// 헤드 노드 이미 있어도 상관없음
void InsertHead(Dlist* list, Data* x)
{
    Dnode *p = list->head;   // next node
    list->head = list->crnt = AllocDNode();  // create head node
    if(p != NULL)
        p->prev = list->head;
    SetDNode(list->head, x, NULL, p); // set head node (data, next node)
    list->cnt++;
}

/*--- insert a node immediately after the p node ---*/
void InsertAfter(Dlist* list, Dnode* pre, Data* x)
{
    if (pre == NULL)
        InsertHead(list, x);
    else {
        Dnode *p = list->crnt = AllocDNode();
        SetDNode(p, x, pre, pre->next);
        if (pre->next != NULL)
            pre->next->prev = p; // pre next
        pre->next = p;
        list->cnt++;
    }
}

/*--- insert node into a tail ---*/
void InsertTail(Dlist* list, Data* x)
{
    if (list->head == NULL)
        InsertHead(list, x);
    else {
        Dnode *p = list->head;
        while (p->next != NULL)
            p = p->next;
        InsertAfter(list, p, x);
    }
}

/*--- remove the node pointed to by p pointer ---*/
void Delete(Dlist* list, Dnode* p)
{
    // head node
    // middle node
    // tail node
    // p : 삭제할 노드 설정
    if (p != NULL) {
        if (p == list->head) {
            if(p->next == NULL) {
                list->head = NULL;
            }
            else {
                list->head = p->next;
                p->next->prev = p->prev;
            }
        }
        else {
            if(p->next == NULL)
                p->prev->next = p->next;
            else {
                p->prev->next = p->next;
                p->next->prev = p->prev;
            }
        }
        list->crnt = p->prev;   /* select deleted node */
        free(p);
        list->cnt--;
    }
   
}

/*--- remove head node ---*/
void DeleteHead(Dlist* list)
{
    if (!IsEmpty(list))
        Delete(list, list->head);
}

/*--- remove tail node ---*/
void DeleteTail(Dlist* list)
{
    if (!IsEmpty(list)) {
        Dnode *p = list->head;
        while (p->next != NULL) {
            p = p->next;
        }
        Delete(list, p);
    }
}

/*--- remove selected node ---*/
void DeleteCurrent(Dlist* list)
{
    if (list->crnt != list->head)
        Delete(list, list->crnt);
}

/*--- search for a node equal to x with compare function ---*/
Dnode* search(Dlist* list, Data* x, int compare(Data* x, Data* y))
{
    Dnode* p = list->head->next;
    while (p != list->head) {
        if (compare(&p->data, x) == 0) {
            list->crnt = p;
            return p;     /* searh sucess */
        }
        p = p->next;
    }
    return NULL;        /* searh fail */
}

/*--- print data of seleting node ---*/
void PrintCurrent(Dlist* list)
{
    if (list->crnt == NULL)
        printf("There is no node.");
    else
        printf("출력");
}

/*---  print data of selecting nodes in list order(including \n) ---*/
void PrintLnCurrent(Dlist* list)
{
    PrintCurrent(list);
    putchar('\n');
}

/*--- print data of all nodes in list order ---*/
void PrintAll(Dlist* list)
{
    if (list->head == NULL) {
        // ㅇㄹㅇ
    }
    else {
        Dnode* p = list->head;
        while (p != NULL) {
            printf("%d", p->data.num); // 출력
            p = p->next;    /* select next node */
        }
        printf("\n"); // 출력
    }
}

/*--- print data of all nodes list in reverse order ---*/
void PrintReverse(Dlist* list)
{
    if (list->head == NULL) {
        // ㅇㄹㅇ
    }
    else {
        Dnode* p = list->head;
        // 맨끝 찾기
        while (p->next != NULL) {
            p = p->next;    /* select next node */
        }
        // 맨끝에서 아래로
        while (p != NULL) {
//            printf("%d", p->data.num); // 출력
            p = p->prev;    /* select next node */
        }
//        printf("\n"); // 출력
    }
}

/*--- remove circular doubly linked list ---*/
void Terminate(Dlist* list)
{
    while (!IsEmpty(list))  /* delete all node */
        DeleteHead(list);
    free(list->head);   /* dummy node memory area */
}


/*--- main ---*/
int main(void)
{
    Dlist list;
    Data x;
    Initialize(&list);
    x.num = 0;
    for (int i = 0; i < 10; i++) {
        x.num = i;
        InsertTail(&list, &x);
//        InsertHead(&list, &x);
    }
    
    PrintAll(&list);
    
    PrintReverse(&list);
    
    PrintAll(&list);
    
    PrintReverse(&list);
    
    
    Terminate(&list);   /* terminate circular doubly linked list */

    return 0;
}

