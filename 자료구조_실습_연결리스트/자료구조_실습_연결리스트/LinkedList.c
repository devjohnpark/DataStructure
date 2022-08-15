/* 연결 리스트 */
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

// Node
typedef struct node {
    Data data;
    struct node *next;
} Node;

// Linked List
typedef struct list {
    Node *head;
    Node *crnt;
    int cnt;
} List;

// Linked List initailize
void Initialize(List *list) {
    list->head = NULL;
    list->crnt = NULL;
    list->cnt = 0;
}

// Create Node dynamically
static Node* AllocNode(void) {
    return calloc(1, sizeof(Node));
}

// Set Node
static void SetNode(Node *node, Data *data, Node *next) {
    node->data = *data;
    node->next = next;
}

/*--- is empty? ---*/
static int IsEmpty(List* list)
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


// Search equal data
Node *Search(List *list, Data *x, int compare(Data *x, Data *y)) {
    Node *p = list->head;
    while (p != NULL) {
        if (compare(&p->data, x) == 0) {
            list->crnt = p;
            return p;
        }
        p = p->next;
    }
    return NULL;
}

// insert node to head
void InsertHead(List *list, Data *x) {
    Node *p = list->head;   // next node
    list->head = list->crnt = AllocNode();  // create head node
    SetNode(list->head, x, p); // set head node (data, next node)
    list->cnt++;
}

// insert node to tail
void InsertTail(List *list, Data *x) {
    if (list->head == NULL)
        InsertHead(list, x);
    else {
        Node *p = list->head;
        while (p->next != NULL)
            p = p->next;
        p->next = list->crnt = AllocNode();
        SetNode(p->next, x, NULL);
        list->cnt++;
    }
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
        list->cnt++;
    }
}

// delete head node
void DeleteHead(List *list) {
    if (list->head != NULL) {
        Node *p = list->head->next;
        free(list->head);
        list->head = list->crnt = p;
        list->cnt--;
    }
}

// delete tail node
void DeleteTail(List *list) {
    if (list->head != NULL) {
        if (list->head->next == NULL)
            DeleteHead(list);
        else {
            Node *prev = NULL;
            Node *p = list->head;
            while (p->next != NULL) {
                prev = p;
                p = p->next;
            }
            prev->next = NULL; /* in front of tail node */
            free(p);    // free tail node
            list->crnt = prev;
            list->cnt--;
        }
    }
}

//// 해당 노드 뒤 삭제
//void DeleteAfter(List *list, Node * prev) {
//    if (list->head != NULL) {
//        if (prev != NULL) {
//            Node *p = prev->next;
//            if (p != NULL)
//                prev->next = p->next;
//            free(p);
//            prev = list->crnt;
//
//        }
//    }
//}

void DeleteCurrent(List *list) {
    // 삭제할 노드 list->crnt에 담는다.
    if (list->head != NULL) {
        if (list->crnt == list->head)
            DeleteHead(list);
        else {
            Node *p = list->head;
            while (p->next != list->crnt && p->next != NULL) {
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
    
    list->cnt--;
}

void Reverse(List *list) {
    Node *p = list->head;
    Node *q = NULL;
    Node *r = NULL;

    while (p != NULL) {
        r = q;
        q = p;
        p = p->next;    // 다음 노드 이동
        q->next = r;    // 그 전 노드 가리킴
    }
    list->head = q; // last node
}

void PrintAll(List *list) {
    if (list->head == NULL) {
        // 노드 없을때 printf 구문
    }
    else {
        // 노드 있을때 printf 구문
        Node *p = list->head;
        while (p != NULL) {
            // printf 구문
            p = p->next;
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

int main() {
    
    List list;
    Data x;
    x.num = 5;
    Initialize(&list);
    
    Terminate(&list);
    return 0;
}
