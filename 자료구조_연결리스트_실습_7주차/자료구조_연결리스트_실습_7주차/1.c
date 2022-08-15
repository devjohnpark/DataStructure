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

static Node* AllocNode(void) {
    return calloc(1, sizeof(Node));
}

// Set Node
static void SetNode(Node *node, int data, Node *next) {
    node->data = data;
    node->next = next;
}

// 53 7 10
// 7 10 15 45
int subset(Node *a, Node *b, int n) {
    Node* tmp;
    int cnt= 0;
    while (a != NULL) {
        cnt++;
        if (cnt > n)
            break;
        tmp = b;
        while (tmp != NULL) {
            if (a->data == tmp->data) {
                break;
            }
            tmp = tmp->next;
        }
        if (tmp == NULL) {
            break;
        }
        else {
            a = a->next;
        }
    }
    
    if (a == NULL)
        return 0;
    else {
        int min = a->data;
        a = a->next;
        while (a != NULL) {
            if (min > a->data)
                min = a->data;
            a = a->next;
        }
        return min;
    }
}


int main() {
    Node *a = NULL, *b = NULL, *tmp = NULL;
    int n, m;
    int data;
    
    scanf("%d", &n);
    if (n != 0) {
        a = AllocNode();
        tmp = a;
        scanf("%d", &data);
        SetNode(tmp, data, NULL);
    }
    for (int i=1; i<n; i++) {
        tmp->next = AllocNode();
        scanf("%d", &data);
        SetNode(tmp->next, data, NULL);
        tmp = tmp->next;
    }
    
    scanf("%d", &m);
    if (m != 0) {
        b = AllocNode();
        tmp = b;
        scanf("%d", &data);
        SetNode(tmp, data, NULL);
    }
    for (int i=1; i<m; i++) {
        tmp->next = AllocNode();
        scanf("%d", &data);
        SetNode(tmp->next, data, NULL);
        tmp = tmp->next;
    }
    
    printf("%d", subset(a, b, n));
    
    while (a != NULL) {
        free(a);
        a = a->next;
    }
    
    while (b != NULL) {
        free(b);
        b = b->next;
    }
    
    return 0;
}
