//
//  main.c
//  자료구조_연결리스트_실습_7주차
//
//  Created by Junseo Park on 2022/05/06.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct __node {
    int data;
    struct __node* next;
} Node;

typedef struct list {
    Node *head;
} List;

static Node* AllocNode(void) {
    return calloc(1, sizeof(Node));
}

// Set Node
static void SetNode(Node *node, int data, Node *next) {
    node->data = data;
    node->next = next;
}

void init(List *list) {
    list->head = NULL;
}

// insert node to head
void InsertHead(List *list, int x) {
    Node *p = list->head;   // next node
    list->head = AllocNode();  // create head node
    SetNode(list->head, x, p); // set head node (data, next node)
}

// insert node to tail
void InsertTail(List *list, int x) {
    if (list->head == NULL)
        InsertHead(list, x);
    else {
        Node *p = list->head;
        while (p->next != NULL)
            p = p->next;
        p->next = AllocNode();
        SetNode(p->next, x, NULL);
    }
}

List Union(List* listA, List* listB) {
    List list;
    init(&list);
    Node *p = listA->head;
    Node *q = listB->head;
    
    while (p != NULL && q != NULL) {
        if (p->data == q->data) {
            InsertTail(&list, p->data);
            p = p->next;
            q = q->next;
        }
        else if (p->data < q->data) {
            InsertTail(&list, p->data);
            p = p->next;
        }
        else {
            InsertTail(&list, q->data);
            q = q->next;
        }
    }
    
    while (p != NULL) {
        InsertTail(&list, p->data);
        p = p->next;
    }
    
    while (q != NULL) {
        InsertTail(&list, q->data);
        q = q->next;
    }
    
    return list;
}

List Intersect(List* listA, List* listB) {
    List list;
    init(&list);
    Node *p = listA->head;
    Node *q = listB->head;
    
    while (p != NULL && q != NULL) {
        if (p->data == q->data) {
            InsertTail(&list, p->data);
            p = p->next;
            q = q->next;
        }
        else if (p->data < q->data) {
            p = p->next;
        }
        else {
            q = q->next;
        }
    }

    return list;
}

// delete head node
void DeleteHead(List *list) {
    if (list->head != NULL) {
        Node *p = list->head->next;
        free(list->head);
        list->head = p;
    }
}

void PrintAll(List *list) {
    if (list->head == NULL) {
        printf("0\n");
    }
    else {
        // 노드 있을때 printf 구문
        Node *p = list->head;
        while (p != NULL) {
            printf(" %d", p->data);
            p = p->next;
        }
        printf("\n");
    }
}

void Terminate(List *list) {
    while (list->head != NULL)    /* until empty */
        DeleteHead(list);    /* delete head node */
}

int main() {
    int n, m;
    int data;
    List listA;
    List listB;
    List list;
    
    init(&listA);
    init(&listB);
    init(&list);
    
    scanf("%d", &n);
    
    for (int i=0; i<n; i++) {
        scanf("%d", &data);
        InsertTail(&listA, data);
    }
    
    
    scanf("%d", &m);
    
    for (int i=0; i<m; i++) {
        scanf("%d", &data);
        InsertTail(&listB, data);
    }
    
    
    list = Union(&listA, &listB);
    PrintAll(&list);
    
    Terminate(&list);
    
    init(&list);

    list = Intersect(&listA, &listB);
    PrintAll(&list);
    
    Terminate(&list);
    
//    while (a != NULL) {
//        free(a);
//        a = a->next;
//    }
//
//    while (b != NULL) {
//        free(b);
//        b = b->next;
//    }
    
    return 0;
}
