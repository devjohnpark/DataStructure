//
//  main.c
//  자료구조_이진트리_순회과제
//
//  Created by Junseo Park on 2022/05/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Data;

typedef struct treeNode{
    Data data;
    int id;
    struct treeNode *left;
    struct treeNode *right;
}treeNode;

int TOF = 0;

treeNode* makeRootNode(Data data, int id, treeNode* leftNode, treeNode* rightNode)
{
    treeNode* root = (treeNode*)malloc(sizeof(treeNode));
    root->data = data;
    root->id = id;
    root->left = leftNode;
    root->right = rightNode;
    return root;
}

// 부모 순위의 따라 전위, 중위, 후위
void preorder_Foldernum(treeNode* root)
{
    if(root) { // 아이디 같을시 스탑, 아이디 보다 클시 -1 출력
        printf(" %d", root->data);
        preorder_Foldernum(root->left);
        preorder_Foldernum(root->right);
    }
    
}

void inorder_Foldernum(treeNode* root)
{
    if(root) {
        inorder_Foldernum(root->left);
        printf(" %d", root->data);
        inorder_Foldernum(root->right);
    }
}

void postorder_Foldernum(treeNode* root)
{
    if(root) {
        postorder_Foldernum(root->left);
        postorder_Foldernum(root->right);
        printf(" %d", root->data);
    }
}

void searchTree(treeNode* root, int order, int id) {
    if (root) {
        if (root->id < id) {
            searchTree(root->left, order, id);
            searchTree(root->right, order, id);
        }
        else if (root->id == id) {
            // 순회 시작
            switch (order) {
                case 1:
                    preorder_Foldernum(root);
                    break;
                case 2:
                    inorder_Foldernum(root);
                    break;
                case 3:
                    postorder_Foldernum(root);
                    break;
                default:
                    break;
            }
            
            TOF = 1;
            return;
        }
    }
    
    
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
    treeNode* F8 = makeRootNode(80, 8, NULL, NULL);
    treeNode* F7 = makeRootNode(130, 7, NULL, NULL);
    treeNode* F6 = makeRootNode(120, 6, F7, F8);
    treeNode* F5 = makeRootNode(90, 5, NULL, NULL);
    treeNode* F4 = makeRootNode(70, 4, NULL, NULL);
    treeNode* F3 = makeRootNode(50, 3, NULL, F6);
    treeNode* F2 = makeRootNode(30, 2, F4, F5);
    treeNode* F1 = makeRootNode(20, 1, F2, F3);
    
    treeNode* tree = F1;
    int order;
    int id;
    
    scanf("%d %d", &order, &id);
    
    searchTree(tree, order, id);
    
    if (!TOF)
        printf("-1");
    
    
    postorder_deleteTree(tree); // 후위 노드로 모두 삭제
    
    return 0;
}
