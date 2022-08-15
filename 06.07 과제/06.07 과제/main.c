/* Program using Binary Search */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMBER_NO 1

/*--- member data ---*/
typedef struct {
    int no;         /* no */
} Member;

/*--- Node ---*/
typedef struct binnode {
    Member data;            /* data */
    struct binnode *left;    /* left child node pointer */
    struct binnode *right;    /* right child node pointer */
} BinNode;

/*--- member no compare function ---*/
int MemberNoCmp(const Member* x, const Member* y)
{
    return x->no < y->no ? -1 : x->no > y->no ? 1 : 0;
}

/*--- represent member data ---*/
void PrintMember(const Member* x)
{
    printf("%d", x->no);
}

/*--- represent member data(including \n) ---*/
void PrintLnMember(const Member* x)
{
    printf("%d\n", x->no);
}

/*--- read member data ---*/
Member ScanMember(const char* message, int sw)
{
    Member temp;
    printf("Enter the data to %s.\n", message);
    if (sw & MEMBER_NO) { printf("no : "); scanf("%d", &temp.no); }
    return temp;
}

/*--- Allocate node dynamically ---*/
static BinNode *AllocBinNode(void)
{
    return calloc(1, sizeof(BinNode));
}

/*--- Set member of node ----*/
static void SetBinNode(BinNode *n, const Member *x, const BinNode *left, const BinNode *right)
{
    n->data = *x;            /* data */
    n->left = left;            /* left pointer */
    n->right = right;
}

/*--- Search ---*/
BinNode *Search(BinNode *p, const Member *x)
{
    int cond;
    
    if (p != NULL) {
        if ((cond = MemberNoCmp(x, &p->data)) == 0)
            return p;       /* search sucess */
        else if (cond < 0)
            Search(p->left, x);     /* search in left sub tree*/
        else
            Search(p->right, x);
    }
    
    return NULL;
}


/*--- Add node ---*/
BinNode *Add(BinNode *p, const Member *x)
{
    int cond;
    if (p == NULL) {
        p = AllocBinNode();
        SetBinNode(p, x, NULL, NULL);
    }
    else if ((cond = MemberNoCmp(x, &p->data)) == 0)
        printf("【Error】 %d is already exist.\n", x->no);
    else if (cond < 0)
        p->left = Add(p->left, x);
    else
        p->right = Add(p->right, x);
    return p;
}

/*--- Delete node ---*/
int Remove(BinNode **root, const Member *x)
{
    BinNode *next, *temp;
    BinNode **left;
    BinNode **p = root;
    
    /* Search for nodes to delete */
    while (1) {
        int cond;
        if (*p == NULL) {
            printf("【Error】 %d is not enrolled.\n", x->no);
            return -1;        /* There is no key */
        }
        else if ((cond = MemberNoCmp(x, &(*p)->data)) == 0)
            break;            /* Search sucess */
        else if (cond < 0)
            p = &((*p)->left);    /* Search on left sub tree */
        else
            p = &((*p)->right);    /* Search on right sub tree */
    }
    
    /* Delete node and move node */
    if ((*p)->left == NULL) /* There is no left sub tree */
        next = (*p)->right;
    else {
        left = &((*p)->left); /* The top node of the left subtree */
        while ((*left)->right != NULL)    /* Search rightmost child node in the subtree.(Largesrt value) */
            left = &(*left)->right;
        next = *left;    /* Save address of moved node */
        *left = (*left)->left; /* move to left child node of rightmost child node */

        /* link the deleted child node to the moved node */
        next->left = (*p)->left;
        next->right = (*p)->right;
    }

    temp = *p; /* save memory to free */
    *p = next; /* set moved node to deleted node location */
    free(temp); /* free memory */
    
    return 0;
}

void minNode(BinNode *p) {
    printf("기준노드의 좌측서브트리에서 가장 큰 노드는 ");
    if (p->left == NULL)
        printf("");
    else {
        while (p->left != NULL)
            p = p->left;
        printf("%d",  p->data.no);
    }
    printf(", ");
}

void maxNode(BinNode *p) {
    printf("기준노드의 우측서브트리에서 가장 작은 노드는 ");
    if (p->right == NULL)
        printf("");
    else {
        while (p->right != NULL)
            p = p->right;
        printf("%d",  p->data.no);
    }
    printf("입니다.\n");
}

/*--- Print data of all node ---*/
void PrintTree(const BinNode* p)
{
    if (p != NULL) {
        PrintTree(p->left);
        PrintLnMember(&p->data);
        PrintTree(p->right);
    }
}

/*--- Delete all node ---*/
void FreeTree(BinNode* p)
{
    if (p != NULL) {
        FreeTree(p->left);
        FreeTree(p->right);
        free(p);
    }
}

/*--- Menu ---*/
typedef enum {
    TERMINATE, ADD, REMOVE, SEARCH, PRINT
} Menu;

/*--- Select menu ---*/
Menu SelectMenu(void)
{
    int ch;
    do {
        printf("(1) Insert (2) Delete (3) Search (4) Print (0) Exit : ");
        scanf("%d", &ch);
    } while (ch < TERMINATE || ch > PRINT);
    return (Menu)ch;
}

/*--- Main fuction ---*/
int main(void)
{
    Menu menu;
    BinNode* root = NULL;    /* root pointer of BST */
    do {
        Member x;
        BinNode* temp;
        switch (menu = SelectMenu()) {

        /*--- Insert node ---*/
        case ADD:
            x = ScanMember("insert", MEMBER_NO);
            root = Add(root, &x);
            break;

        /*--- Remove node ---*/
        case REMOVE:
            x = ScanMember("delete", MEMBER_NO);
            Remove(&root, &x);
            break;

        /*--- Search node ---*/
        case SEARCH:
            x = ScanMember("Search", MEMBER_NO);
            if ((temp = Search(root, &x)) != NULL) {
                maxNode(temp);
                minNode(temp);
            }
            break;

        /*--- Print all node ---*/
        case PRINT:
            puts("【 View All 】");
            PrintTree(root);
            break;
        }
    } while (menu != TERMINATE);

    FreeTree(root);

    return 0;
}
