//
//  2-1.c
//  DS_Stack_실습_스택2
//
//  Created by Junseo Park on 2022/05/31.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_SIZE 101

typedef int element;
int top = -1;
element stack[STACK_SIZE];

void push(element item) {
    if (top >= STACK_SIZE - 1) {
        printf("\n\n Stack is FULL! \n");
        return;
    }
    else
        stack[++top] = item;
}

element pop() {
    if (top == -1) {
        printf("\n\n Stack is Empty! \n");
        return 0;
    }
    else
        return stack[top--];
}

void del() {
    if (top == -1) {
        printf("\n\n Stack is Empty! \n");
        exit(1);
    }
    else
        top--;
}

element peek() {
    if (top == -1) {
        printf("\n\n Stack is Empty! \n");
        exit(1);
    }
    else
        return stack[top];
}

void printStack() {
    printf("스택 시작 ");
    for (int i=0; i<=top; i++) {
        printf("%d ", stack[i]);
    }
    printf("스택 끝\n");
}

element operand(element operator) {
    switch (operator) {
        case '*':
        case '/':
        case '+':
        case '-':
            return operator;
            break;
        default:
            return '\0';
            break;
    }
}

int main() {
    int n;
    int num1, num2;
    char arr[STACK_SIZE];
    scanf("%d", &n);
    for (int i=0; i<n; i++) {
        scanf("%s", arr);
        for (int j=0; j<strlen(arr); j++) {
            // 연산자면 팝 두번 후 연산자 계산
            if (arr[j] == '+') {
                num2 = pop();
                num1 = pop();
                push(num1 + num2);
            }
            else if (arr[j] == '-') {
                num2 = pop();
                num1 = pop();
                push(num1 - num2);
            }
            else if (arr[j] == '*') {
                num2 = pop();
                num1 = pop();
                push(num1 * num2);
            }
            else if (arr[j] == '/') {
                num2 = pop();
                num1 = pop();
                push(num1 / num2);
            }
            else {
                push(arr[j] - '0');
            }
        }
        printf("%d\n", pop());
    }
    return 0;
}
