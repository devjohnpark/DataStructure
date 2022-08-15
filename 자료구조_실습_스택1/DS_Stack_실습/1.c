//
//  main.c
//  DS_Stack
//
//  Created by Junseo Park on 2022/05/06.
//



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element;    // 타입 설정

int top = -1;
int stackSize = 0;

void push(element *stack, element item) {
    if (top >= stackSize - 1) { // 4 >= 5
        printf("Stack FULL\n");
        return;
    }
    else
        stack[++top] = item;
}

element pop(element *stack) {
    if (top == -1) {
        printf("Stack Empty\n");
        return '\0';
    }
    else
        return stack[top--];
}

void duplicate(element *stack) {
    element pushItem = pop(stack);
    push(stack, pushItem);
    push(stack, pushItem);
}

void upRotate(element *stack, int n) {
    if (n <= top + 1) { // n > top + 1 n <= tio
        element pushItem = pop(stack);
        element *tmp = NULL;
        tmp = (element*)malloc(sizeof(element) * n);
        for (int i=0; i<n-1; i++)
            tmp[i] = pop(stack); // 0 1
        push(stack, pushItem);
        for (int i=n-2; i>=0; i--)
            push(stack, tmp[i]);
        free(tmp);
    }
}

void downRotate(element *stack, int n) {
    if (n <= top + 1) {
        element *tmp = NULL;
        tmp = (element*)malloc(sizeof(element) * n);
        for (int i=0; i<n-1; i++)
            tmp[i] = pop(stack); // 0 1
        element pushItem = pop(stack);
        for (int i=n-2; i>=0; i--)
            push(stack, tmp[i]);
        push(stack, pushItem);
        free(tmp);
    }
}


void peek(element *stack) {
    if (top == -1) {
        printf("Stack Empty");
    }
    else
        printf("%c", stack[top]);
}

void printStack(element *stack) {
    for (int i=top; i>=0; i--) {
        printf("%c", stack[i]);
    }
    printf("\n");
}

int main() {
    element *stack = NULL;
    int operNum;
    int n;
    element item;
    char instruction[6];
    
    
    scanf("%d", &stackSize);
    scanf("%d", &operNum);
    
    stack = (element*)malloc(sizeof(element) * stackSize);
    
    for (int i=0; i<operNum; i++) {
        scanf("%s", instruction);
        getchar();
        if (strcmp(instruction, "POP") == 0) {
            pop(stack);
        }
        else if (strcmp(instruction, "PUSH") == 0) {
            scanf("%c", &item);
            push(stack, item);
            getchar();
        }
        else if (strcmp(instruction, "PEEK") == 0) {
            peek(stack);
        }
        else if (strcmp(instruction, "DUP") == 0) {
            duplicate(stack);
        }
        else if (strcmp(instruction, "UpR") == 0) {
            scanf("%d", &n);
            upRotate(stack, n);
        }
        else if (strcmp(instruction, "DownR") == 0) {
            scanf("%d", &n);
            downRotate(stack, n);
        }
        else if (strcmp(instruction, "PRINT") == 0) {
            printStack(stack);
        }
    }
    
    free(stack);
    
    return 0;
}
