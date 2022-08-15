//
//  Practice_Array_Stack.c
//  Stack
//
//  Created by Junseo Park on 2022/06/10.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE    1
#define FALSE    0
#define STACK_SIZE 101 // 정해진 스택 사이즈

typedef char Data;

typedef struct arrStack {
    Data *stack;
    int topIndex;
    int stackSize;
    int num;
} ArrStack;

typedef ArrStack Stack;

void initStack(Stack *pstack, int stackSize);
int isEmpty(Stack *pstack);
void print(Stack *pstack);
void push(Stack *pstack, Data data);
void terminate(Stack *pstack);
int getRank(Data data);
int isAlphabet(Data data);

Data pop(Stack *pstack);
Data peek(Stack *pstack);

int main() {
    Stack stack;
    Data data[STACK_SIZE] = {'\0'};
    int dataRank;
    int stackRank;
    int n;
    
    scanf("%d", &n);
    
    initStack(&stack, STACK_SIZE);
    
    for (int i=0; i<n; i++) {
        scanf("%s", data);
        for (int j=0; data[j] != '\0'; j++) {
            if (isAlphabet(data[j])) {
                printf("%c", data[j]);
            }
            else { // 연산자이거나 괄호
                if (data[j] == '(')  // ( 괄호
                    push(&stack, data[j]);
                else if (data[j] == ')') { // ) 괄호
                    if (peek(&stack) == '(')
                        pop(&stack);
                }
                else { // 연산자
                    if ((j > 0 && data[j - 1] ) || (j > 0 && data[j - 1] == '(') || j == 0) {
                        if (data[j] == '+') {
                            data[j] = '@';
                        }
                        else if (data[j] == '-') {
                            data[j] = '-';
                        }
                    }
                    dataRank = getRank(data[j]);
                    stackRank = getRank(peek(&stack));
                    if (stackRank >= dataRank && !isEmpty(&stack))
                        printf("%c", pop(&stack));
                    else
                        push(&stack, data[j]);
                }
            }
        }
    }
    
    // 연산자 아니면 출력
    // 연산자면 스택 연산자와 비교해서 우선순위 크면 팝, 아니면 푸쉬
    // ( 나오면 푸쉬, 탑 ( 이면 팝 금지, 배열 ) 나오면 팝
    // 단항 연산자: 앞에 연산자거나 ( > @, # 으로 바꿔서 스택에 푸쉬
    
    
    terminate(&stack);
    
    return 0;
}

int isAlphabet(Data data) {
    if (data >= 'A' && data <= 'Z')
        return 1;
    else
        return 0;
}

int getRank(Data data) {
    switch (data) {
        case '(':
            return 7;
            break;
        case '!':
        case '@':
        case '#':
            return 6;
            break;
        case '*':
        case '/':
            return 5;
            break;
        case '+':
        case '-':
            return 4;
            break;
        case '>':
        case '<':
            return 3;
            break;
        case '&':
            return 2;
            break;
        case '|':
            return 1;
            break;
        default:
            return 0;
            break;
    }
}


void initStack(Stack *pstack, int size) {
    pstack->topIndex = -1;
    pstack->stackSize = size;
    pstack->num = 0;
    pstack->stack = (Data *)malloc(sizeof(Data) * pstack->stackSize);
}

int isEmpty(Stack *pstack) {
    if (pstack->topIndex == -1)
        return TRUE;
    else
        return FALSE;
}

int isFULL(Stack *pstack) {
    if (pstack->topIndex == pstack->stackSize - 1)
        return TRUE;
    else
        return FALSE;
}

void push(Stack *pstack, Data data) {
    if (isFULL(pstack)) {
        printf("overflow\n");
        exit(-1);
    }
    else {
        pstack->num++;
        pstack->stack[++pstack->topIndex] = data;
    }
}

Data pop(Stack *pstack) {
    if (isEmpty(pstack)) {
        return '\0';
//        printf("underflow\n");
//        exit(-1);
    }
    else {
        pstack->num--;
        return pstack->stack[pstack->topIndex--];
    }
}

Data peek(Stack *pstack) {
    if (isEmpty(pstack)) {
        return '\0';
//        printf("underflow\n");
//        exit(-1);
    }
    else
        return pstack->stack[pstack->topIndex];
}

void print(Stack *pstack) {
    if (!isEmpty(pstack)) {
        for (int i=pstack->topIndex; i>=0; i--) {
            printf("%c", pstack->stack[i]);
        }
        printf("\n");
    }
}

void terminate(Stack *pstack) {
    free(pstack->stack);
}

