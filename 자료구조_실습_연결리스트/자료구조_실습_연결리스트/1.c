/* Linked List using pointer(source) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*--- Data data ---*/
typedef struct {
    char element;
} Data;

/*--- node ---*/
typedef struct __Dnode {
    Data data;        /* data */
    struct __Dnode* prev;
    struct __Dnode* next;    /* pointer for next node */
} DNode;

/*--- linked list ---*/
typedef struct {
    DNode* head;        /* pointer for head node */
    int cnt;
} DList;



/*--- create node dynamically ---*/
static DNode* AllocNode(void)
{
    return calloc(1, sizeof(DNode));
}

/*--- initialize linked list ---*/
void Initialize(DList* list)
{
    list->head = NULL;    /* head node */
}

int errorCmp(int listCnt, int range, char instruction) {
    if (instruction == 'A') {
        if (listCnt + 1 < range) {
            printf("invalid position\n");
            return 0;
        }
        else
            return 1;
    } else {
        if (listCnt < range) {
            printf("invalid position\n");
            return 0;
        }
        else
            return 1;
    }
}

void add(DList* list, int order, char element) {
    if (errorCmp(list->cnt, order, 'A') == 0)
        return;
    DNode *newDnode = AllocNode();
    newDnode->data.element = element;
    newDnode->prev = NULL;
    newDnode->next = NULL;
    if (list->head == NULL) {
        list->head = newDnode;
    }
    else {
        DNode *p = list->head;
        // 기본 뒤에 넣고, 순위 원래 있으면 요소 바꿈
        // 순위가 개수와 같으면 앞에 넣고
        // 순위가 개수보다 크면 뒤에 넣고
        for (int i = 1; i < order - 1; i++)
            p = p->next;
        if (order == 1) {
            newDnode->next = p;
            p->prev = newDnode;
            list->head = newDnode;
        } else {
            newDnode->next = p->next;
            if (p->next != NULL) {
                newDnode->next->prev = newDnode;
            }
            p->next = newDnode;
            newDnode->prev = p;
        }

//        if (order <= list->cnt) { // 2
//            newDnode->data.element = p->data.element;
//            p->data.element = element;
//        }

    }
    list->cnt++;
}

void delete(DList* list, int order) {
    if (errorCmp(list->cnt, order, 'D') == 0)
        return;
    DNode *p = list->head;
    // 현재 노드 이동
    for (int i = 1; i < order; i++)
        p = p->next;
    // 앞 뒤 연결
    
    if (order == 1) { // 첫번재 노드 삭제
        list->head = p->next;
    }
    
    if (p->next != NULL) {
        p->next->prev = p->prev;
    }
    
    if (p->prev != NULL) {
        p->prev->next = p->next; // 마지막 노드 가능
    }
//    if (p->next == NULL) { // 마지막 노드 삭제
//        p->prev->next = p->next; // 마지막 노드 가능
//    } else {
//        p->prev->next = p->next; // 마지막 노드 가능
//        p->next->prev = p->prev; // 첫번째 노드 가능
//    }
//    // 헤드 노드 삭제
//    if (order == 1)
//        list->head = p->next;
//
//    // 테일 노드 삭제
//    else if (p->next == NULL) {
//        p->prev->next = p->next;
//    }
    
    free(p);
    p = NULL;
    list->cnt--;
}

void get(DList* list, int order) {
    if (errorCmp(list->cnt, order, 'G') == 0)
        return;
    DNode *p = list->head;
    for (int i = 1; i < order; i++)
        p = p->next;
    printf("%c\n", p->data.element);
}

void print(DList *list) {
    DNode *p = list->head;
    while (p != NULL) {
        printf("%c", p->data.element);
        p = p->next;
    }
    printf("\n");
}

int main() {
    DList list;

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
                add(&list, order, element);
                break;
            case 'D':
                scanf("%d", &order);
                delete(&list, order);
                break;
            case 'G':
                scanf("%d", &order);
                get(&list, order);
                break;
            case 'P':
                print(&list);
                break;
            default:
                break;
        }
        getchar();
    }
    
    // NULL 만들고 메모리 해제
    DNode *p = list.head;
    while (p != NULL) {
        free(p);
        p = p->next;
    }
    
    return 0;
}
