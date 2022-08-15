
/* 이중연결리스트 1 - 1 */
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

/*--- list initialize ---*/
void Initialize(Dlist* list)
{
    list->head = NULL;
    list->crnt = NULL;
    list->cnt = 0;
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



/*--- search for a node equal to x with compare function ---*/
Dnode* Search(Dlist* list, Data* x, int compare(Data* x, Data* y))
{
    Dnode* ptr = list->head->next;
    while (ptr != list->head) {
        if (compare(&ptr->data, x) == 0) {
            list->crnt = ptr;
            return ptr;     /* searh sucess */
        }
        ptr = ptr->next;
    }
    return NULL;        /* searh fail */
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
    SetDNode(list->head, x, NULL, p); // set head node (data, prev node, next node)
    list->cnt++;
}


/*--- insert a node immediately after the p node ---*/
void InsertAfter(Dlist* list, Data* x, int order)
{
    Dnode *pre = list->head;
    while (order > 2) {
        order--;
        pre = pre->next;
    }
    
    if (pre == NULL || order == 1)
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
void InsertTail(Dlist* list, Data* x, int order)
{
    if (list->head == NULL)
        InsertHead(list, x);
    else {
        Dnode *p = list->head;
        while (p->next != NULL)
            p = p->next;
        InsertAfter(list, x, order);
    }
}

/*--- remove the node pointed to by p pointer ---*/
void Delete(Dlist* list, Dnode *p)
{
    // head node
    // middle node
    // tail node
    
    if (p == list->head) {
        if(p->next == NULL) { // head and tail node
            list->head = NULL;
        }
        else {  // head node인데 뒤에 노드 잇음
            list->head = p->next;
            p->next->prev = p->prev;
        }
    }
    else {
        if(p->next == NULL) // tail node
            p->prev->next = p->next;
        else { // 중간 노드
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }
    }
    
    list->crnt = p->prev;   /* select deleted node */
    free(p);
    list->cnt--;
   
}

/*--- remove head node ---*/
void DeleteHead(Dlist* list)
{
    if (!IsEmpty(list))
        Delete(list, list->head);
}

/*--- remove tail node ---*/
void DeleteTail(Dlist* list, int order)
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
void DeleteCurrent(Dlist* list, int order)
{
    Dnode *p = list->head;
    
    while (order > 1) {
        order--;
        p = p->next;
    }
 
    if (!IsEmpty(list))
        Delete(list, p);
}

/*--- print data of seleting node ---*/
void PrintCurrent(Dlist* list, int order)
{
    // list->crnt 설정 후
    
    Dnode *p = list->head;
    while (order > 1) {
        order--;
        p = p->next;
    }
    list->crnt= p;
    
    if (list->crnt == NULL) {
        // 노드 없을때 printf 구문
    }
    else {
        // printf 구문 list->crnt
        printf("%c\n", list->crnt->data.ch);
    }
}

/*--- print data of all nodes in list order ---*/
void PrintAll(Dlist* list)
{
    if (list->head == NULL) {
        // 노드 없을때 printf 구문
    }
    else {
        // 노드 있을때 printf 구문
        Dnode *p = list->head;
        while (p != NULL) {
            // printf 구문
            printf("%c", p->data.ch);
            p = p->next;
        }
        printf("\n");
    }
}

/*--- print data of all nodes list in reverse order ---*/
void PrintReverse(Dlist* list)
{
    if (list->head == NULL) {
        // df
    }
    else {
        Dnode* p = list->head;
        // 맨끝 찾기
        while (p->next != NULL) {
            p = p->next;    /* select next node */
        }
        // 맨끝에서 아래로
        while (p != NULL) {
            printf("%c", p->data.ch); // 출력
            p = p->prev;    /* select next node */
        }
        printf("\n"); // 출력
    }
}

/*--- remove circular doubly linked list ---*/
void Terminate(Dlist* list)
{
    while (!IsEmpty(list))  /* delete all node */
        DeleteHead(list);
}

/*--- main ---*/
int main(void)
{
    Dlist list;

    int n, order;
    char instruction, element;
    
    scanf("%d", &n);
    getchar();

    Initialize(&list);    /* initialize linear list */
    for (int i=0; i<n; i++) {
        scanf("%c", &instruction);
        
        switch (instruction) {
            case 'A':
                scanf("%d %c", &order, &element);
                Data x;
                x.ch = element;
                list.cnt + 1 >= order ? InsertAfter(&list, &x, order) : printf("invalid position\n");
                break;
            case 'D':
                scanf("%d", &order);
                list.cnt >= order ? DeleteCurrent(&list, order) : printf("invalid position\n");
                break;
            case 'G':
                scanf("%d", &order);
                list.cnt >= order ? PrintCurrent(&list, order) : printf("invalid position\n");
                break;
            case 'P':
                PrintAll(&list);
                break;
            case 'R':
                PrintReverse(&list);
                break;
            default:
                break;
        }
        getchar();
    }
    
    Terminate(&list);
    
    return 0;
}


