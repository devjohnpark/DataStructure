//
//  main.c
//  자료구조_이진트리_순회과제
//
//  Created by Junseo Park on 2022/05/24.
//

#include <stdio.h>
#include <stdlib.h>

typedef int Data;

typedef struct treeNode{
    Data data;
    struct treeNode *left;
    struct treeNode *right;
}treeNode;

int Foldernum = 0;

treeNode* makeRootNode(Data data, treeNode* leftNode, treeNode* rightNode)
{
    treeNode* root = (treeNode*)malloc(sizeof(treeNode));
    root->data = data;
    root->left = leftNode;
    root->right = rightNode;
    return root;
}

// 부모 순위의 따라 전위, 중위, 후위

Data preorder_Foldernum(treeNode* root)
{
    if(root) {
        printf("%d ", root->data);
        Foldernum += root->data;
        preorder_Foldernum(root->left);
        preorder_Foldernum(root->right);
    }
    return Foldernum;
}

Data inorder_Foldernum(treeNode* root)
{
    if(root) {
        inorder_Foldernum(root->left);
        Foldernum += root->data;
        inorder_Foldernum(root->right);
    }
    return Foldernum;
}

Data postorder_Foldernum(treeNode* root)
{
    if(root) {
        postorder_Foldernum(root->left);
        postorder_Foldernum(root->right);
        Foldernum += root->data;
    }
    return Foldernum;
}

void deleteTree(treeNode* root) {
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        printf("\ndelte = %d", root->data);
    }
    free(root);
}


int main()
{
    treeNode* F8 = makeRootNode(80, NULL, NULL);
    treeNode* F7 = makeRootNode(130, NULL, NULL);
    treeNode* F6 = makeRootNode(120, F7, F8);
    treeNode* F5 = makeRootNode(90, NULL, NULL);
    treeNode* F4 = makeRootNode(70, NULL, NULL);
    treeNode* F3 = makeRootNode(50, NULL, F6);
    treeNode* F2 = makeRootNode(30, F4, F5);
    treeNode* F1 = makeRootNode(20, F2, F3);
    
    int n;
    treeNode* head = NULL;
    
    scanf("%d", &n);
    getchar();
    
    switch (n) {
        case 1:
            head = F1;
            break;
        case 2:
            head = F2;
            break;
        case 3:
            head = F3;
            break;
        case 4:
            head = F4;
            break;
        case 5:
            head = F5;
            break;
        case 6:
            head = F6;
            break;
        case 7:
            head = F7;
            break;
        case 8:
            head = F8;
            break;
        default:
            break;
    }
    
    preorder_Foldernum(head);
    
    deleteTree(F1); // 노드 모두 삭제
    
    return 0;
}
