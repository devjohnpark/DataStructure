/* 연결리스트 1 - 1 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Data
typedef struct {
    int num;
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
    }
}

// insert node to middle
// 찾은 노드 위에 삽입
void InsertAfter(List *list, Data *x, int order) {
    // prev 뒤에 노드 삽입
    // prev 설정
    
    Node *prev = list->head;
    while (order > 2) {
        order--;
        prev = prev->next;
    }
    
    
    if (list->head == NULL || order == 1)
        InsertHead(list, x);
    else {
        Node *p = prev->next; // save next node
        prev->next = list->crnt = AllocNode(); // create new node to insert
        SetNode(prev->next, x, p);
    }
    
    list->cnt++;
}

// delete head node
void DeleteHead(List *list) {
    if (list->head != NULL) {
        Node *p = list->head->next;
        free(list->head);
        list->head = list->crnt = p;
    }
}

// delete tail node
void DeleteTail(List *list) {
    if (list->head != NULL) {
        if (list->head->next == NULL)
            DeleteHead(list);
        else {
            Node *prev = NULL; // null 아님
            Node *p = list->head; // null 아님
            while (p->next != NULL) {
                prev = p;
                p = p->next;
            }
            prev->next = NULL;
            free(p);
            list->crnt = prev;
        }
    }
}

void DeleteCurrent(List *list, int order) {
    // 삭제할 노드 list->crnt에 담는다.
        
    Node *p = list->head;
    while (order > 1) {
        order--;
        p = p->next;
    }
    list->crnt= p;
    
    if (list->crnt == list->head)
        DeleteHead(list);
    else {
        p = list->head;
        while (p->next != list->crnt) {
            p = p->next;
        }
        p->next = list->crnt->next;
        free(list->crnt);
        list->crnt = p;
    }
    
    list->cnt--;
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
            printf("%c", p->data.ch);
            p = p->next;
        }
        printf("\n");
    }
}

void PrintCurrent(List *list, int order) {
    // list->crnt 설정 후
    
    Node *p = list->head;
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

void Terminate(List *list) {
    while (list->head != NULL)    /* until empty */
        DeleteHead(list);    /* delete head node */
    list->crnt = NULL;
}

int main() {
    List list;

    int n, order;
    char instruction, element;
    
    scanf("%d", &n);
    getchar();
    
    list.cnt = 0;

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
            default:
                break;
        }
        getchar();
    }
    
    Terminate(&list);
    
    return 0;
}
