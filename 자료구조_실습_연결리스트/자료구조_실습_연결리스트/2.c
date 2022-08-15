#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __polynomial {
    int coef;
    int exp;
    struct __polynomial *next;
} Polynomial;

/*--- linked list ---*/
typedef struct {
    Polynomial* head;        /* pointer for head node */
} PList;

/*--- create node dynamically ---*/
static Polynomial* AllocNode(void)
{
    return calloc(1, sizeof(Polynomial));
}

void add(PList* pl, int coef, int exp) {
    Polynomial *newPolynomial = AllocNode();
    newPolynomial->coef = coef;
    newPolynomial->exp = exp;
    newPolynomial->next = NULL;
    if (pl->head == NULL) {
        pl->head = newPolynomial;
    } else {
        Polynomial *p;
        p = pl->head;
        while (p -> next != NULL) {
            p = p->next;
        }
        p->next = newPolynomial;
    }


}

void addPoly(PList *plist1, PList *plist2) {

    
    Polynomial *p1 = plist1->head;
    Polynomial *p2 = plist2->head;
    
    int coef, exp;
    int cnt = 0;
    
    while (p1 != NULL && p2 != NULL) {
        cnt++;
        if (p1->exp < p2->exp) {
            exp = p2->exp;
            coef = p2->coef;
            p2 = p2->next;
        }
        else if (p1->exp == p2->exp) {
            exp = p2->exp;
            coef = p1->coef + p2->coef;
            p1 = p1->next;
            p2 = p2->next;
        }
        else {
            exp = p1->exp;
            coef = p1->coef;
            p1 = p1->next;
        }
        if (coef != 0 && exp != 0)
            printf(" %d %d", coef, exp);
    }
    
    while (p1 != NULL) {
        exp = p1->exp;
        coef = p1->coef;
        printf(" %d %d", coef, exp);
        p1 = p1->next;
    }
    while (p2 != NULL) {
        exp = p2->exp;
        coef = p2->coef;
        printf(" %d %d", coef, exp);
        p2 = p2->next;
    }
    
    p1 = plist1->head;
    p2 = plist2->head;
    Polynomial *crnt;
    while (p1 != NULL) {
        crnt = p1;
        p1 = p1->next;
        free(crnt);
    }
    while (p2 != NULL) {
        crnt = p1;
        p2 = p2->next;
        free(crnt);
    }
    
}

int main() {
    int n1, n2;
    int coef, exp;
    
    PList plist1;
    PList plist2;
    
    plist1.head = NULL;
    plist2.head = NULL;
    
    scanf("%d", &n1);
    
    for (int i=0; i<n1; i++) {
        scanf("%d %d", &coef, &exp);
        add(&plist1, coef, exp);
    }
    
    scanf("%d", &n2);
    
    for (int i=0; i<n2; i++) {
        scanf("%d %d", &coef, &exp);
        add(&plist2, coef, exp);
    }
    
    addPoly(&plist1, &plist2);
    
    return 0;
}
