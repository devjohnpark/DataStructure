//
//  main.c
//  자료구조_이진트리_순회과제
//
//  Created by Junseo Park on 2022/05/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element;

typedef struct treeNode{
    element key;
    int id;
    struct treeNode *left;
    struct treeNode *right;
}treeNode;

treeNode* point = NULL;

// 삽입
treeNode* insertBSTNode(treeNode* p, element x) {
    treeNode* newNode;
    if (p == NULL) {
        newNode = (treeNode*)malloc(sizeof(treeNode));
        newNode->key = x;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
//    else if (x == p->key)
//        p->left = insertBSTNode(p->left, x);
//    else if (x < p->key)  p->left = insertBSTNode(p->left, x);
//    else if (x > p->key)  p->right = insertBSTNode(p->right, x);
//    else  printf("데이터가 이미 들어있습니다. \n");

    return p;
}


void searchBST(treeNode* root, element x) {
//    printf("찾는 데이터 = %d\n", x);
    if (root) {
        if (x == root->key) {
            point = root;
            return;
        }
        else {
            searchBST(root->left, x);
            searchBST(root->right, x);
        }
    }
}

// 부모 순위의 따라 전위, 중위, 후위
void preorder_Foldernum(treeNode* root)
{
    if(root) { // 아이디 같을시 스탑, 아이디 보다 클시 -1 출력
        printf("%d_", root->key);
        preorder_Foldernum(root->left);
        preorder_Foldernum(root->right);
    }
}

void inorder_Foldernum(treeNode* root)
{
    if(root) {
        inorder_Foldernum(root->left);
        printf("%d_", root->key);
        inorder_Foldernum(root->right);
    }
}

void postorder_Foldernum(treeNode* root)
{
    if(root) {
        postorder_Foldernum(root->left);
        postorder_Foldernum(root->right);
        printf("%d_", root->key);
    }
}

void searchOrderTree(treeNode* root, char order[]) {
    treeNode* p = root;
    printf(" %d", p->key);
    for (int i=0; i<strlen(order) && p != NULL; i++) {
        switch (order[i]) {
            case 'L':
                p = p->left;
                break;
            case 'R':
                p = p->right;
                break;
            default:
                break;
        }
        printf(" %d", p->key);
    }
    printf("\n");
}


// 전위노드 삭제
void preorder_deleteTree(treeNode* root) {
    if (root) {
//        printf("\ndelete = %d", root->data); // 삭제한 부모 노드 출력
        preorder_deleteTree(root->left);
        preorder_deleteTree(root->right);
    }
    free(root);
}

// 중위노드 삭제
void inorder_deleteTree(treeNode* root) {
    if (root) {
        inorder_deleteTree(root->left);
//        printf("\ndelete = %d", root->data); // 삭제한 부모 노드 출력
        inorder_deleteTree(root->right);
    }
    free(root);
}

// 후위노드 삭제
void postorder_deleteTree(treeNode* root) {
    if (root) {
        postorder_deleteTree(root->left);
        postorder_deleteTree(root->right);
//        printf("\ndelete = %d", root->data); // 삭제한 부모 노드 출력
    }
    free(root);
}


int main()
{
//    treeNode* F8 = makeRootNode(80, 8, NULL, NULL);
//    treeNode* F7 = makeRootNode(130, 7, NULL, NULL);
//    treeNode* F6 = makeRootNode(120, 6, F7, F8);
//    treeNode* F5 = makeRootNode(90, 5, NULL, NULL);
//    treeNode* F4 = makeRootNode(70, 4, NULL, NULL);
//    treeNode* F3 = makeRootNode(50, 3, NULL, F6);
//    treeNode* F2 = makeRootNode(30, 2, F4, F5);
//    treeNode* F1 = makeRootNode(20, 1, F2, F3);
    
    treeNode* root = NULL;
    int n;
    char order[101] = {'\0'};
    element a, b, c;
    
    scanf("%d", &n);
    
    for (int i=0; i<n; i++) {
        scanf("%d %d %d", &a, &b, &c);
        if (i == 0) {
            root = insertBSTNode(root, a);
            if (b != 0) {
                root->left = insertBSTNode(root->left, b);
            }
            if (c != 0) {
                root->right = insertBSTNode(root->right, c);
            }
        }
        else {
            searchBST(root, a);
            if (b != 0) {
                point->left = insertBSTNode(point->left, b);
            }
            if (c != 0) {
                point->right = insertBSTNode(point->right, c);
            }
        }
    }
    
    scanf("%d", &n);
    
    for (int i=0; i<n; i++) {
        scanf("%s", order);
        searchOrderTree(root, order);
    }
    
  
    postorder_deleteTree(root); // 후위 노드로 모두 삭제
    
    return 0;
}

//9
//5 3 9
//3 8 15
//8 0 2
//2 0 0
//15 0 0
//9 7 10
//7 12 0
//12 0 0
//10 0 0
//3
