//
//  main.c
//  DS_Stack
//
//  Created by Junseo Park on 2022/05/06.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_SIZE 1001

typedef char element;    // 타입 설정

int top = -1;
int cnt = 0;
int error = 0;

void push(element *stack, element item) {
    if (top < STACK_SIZE - 1) 
        stack[++top] = item;
    else
        error = 1;
}

void pop(element *stack) {
    if (top != -1)
        top--;
}

element peek(element *stack) {
    if (top == -1) {
        error = 1;
        return '\0';
    }
    else
        return stack[top];
}

void isEmpty() {
    if (top == -1 && error == 0) // top 비었을때
        printf("OK_%d\n", cnt);
    else
        printf("Wrong_%d\n", cnt);
}

int main() {
    element *stack = NULL;
    element str[STACK_SIZE] = {'\0'};
    
    stack = (element*)malloc(sizeof(element) * STACK_SIZE);
    
    scanf("%[^\n]s", str);

    for (int i = 0; str[i] != '\0'; i++) {
        switch (str[i]) {
          
            case '(':
                push(stack, str[i]);
                cnt++;
                break;
            case '[':
                push(stack, str[i]);
                cnt++;
                break;
            case '{':
                push(stack, str[i]);
                cnt++;
                break;
            case ')':
                if (peek(stack) == '(')
                    pop(stack);
                cnt++;
                break;
            case ']':
                if (peek(stack) == '[')
                    pop(stack);
                cnt++;
                break;
            case '}':
                if (peek(stack) == '{')
                    pop(stack);
                cnt++;
                break;
            default:
                break;
        }
    }

    isEmpty();
    
    free(stack);
    
    return 0;
}

