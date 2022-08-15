#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_SIZE 101

typedef struct {
    char ch;
    int rank;
} Data;

typedef struct stackNode {
    Data data;
    struct stackNode *next;
} StackNode;

StackNode *top;

int isEmpty() {
    if (top == NULL)
        return 1;
    else
        return 0;
}

// Create Node dynamically
static StackNode* AllocNode(void) {
    return calloc(1, sizeof(StackNode));
}

void push(Data x) {
    StackNode *tmp = AllocNode(); // next stackNode
    tmp->data = x;
    tmp->next = top;
    top = tmp;
}

char pop() {
    if (!isEmpty()) {
        StackNode * tmp = top;
        Data x = tmp->data; // 0
        top = tmp->next;
        free(tmp);
        return x.ch;
    }
    return '\0';
}

Data* peek() {
    if (!isEmpty()) {
        return &(top->data);
    }
    return NULL;
}

void init() {
    top = NULL;
}

void Terminate() {
    char ch;
    while (!isEmpty())  {  /* until empty */
        ch = pop();
        if (ch == '|' || ch == '&')
            printf("%c", ch);
        printf("%c", ch);
    }
}

int getRank(char operator, int unary) {
    switch (operator) {
        case '!':
            return 6;
            break;
        case '*':
        case '/':
            return 5;
            break;
        case '+':
        case '-':
            if (unary)
                return 6;
            else
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

// 배열값과 스택 탑값 랭크 비교
int main() {
    int n;
    char arr[STACK_SIZE];
    int rankArr;
    Data data;
    int unary = 1;
    
    scanf("%d", &n);
    getchar();
    
    init();
    
    // 스택 안비면 ( 스택 들어오면 푸쉬 > 우선순위 자기 보다 높으면 푸쉬 같거나 낮으면 팝 스택에다가 따로 보관 ) 나타나면 팝 두번
    // 스택 비면 > 우선순위 자기 보다 높으면 푸쉬 같거나 낮으면 팝
    for (int i=0; i<n; i++) {
        scanf("%s", arr);
        for (int j=0; j<strlen(arr); j++) {
            if (arr[j] >= 'A' && arr[j] <= 'Z') {
                printf("%c", arr[j]);
                unary = 0;
            }
            else {
                rankArr = getRank(arr[j], unary); // 현재 우선순위
                if (arr[j] == '(') {
                      data.ch = arr[j];
                      data.rank = getRank(arr[j], unary);
                      push(data);
                }
                else if (arr[j] == ')') {
                    printf("%c", pop());
                    pop();
                }
                else {
                    while (!isEmpty() && peek()->ch != '(') {
                        data = *peek();
                        if (data.rank >= rankArr) {
                            if (data.ch == '|' || data.ch == '&')
                                printf("%c", data.ch);
                            printf("%c", pop());
                        }
                        else
                            break;
                            
                    }
                    data.ch = arr[j];
                    data.rank = rankArr;
                    push(data);
                    if (arr[j] == '|' || arr[j] == '&')
                        j++;
                }
                unary = 1;
            }
        }
        Terminate();
        printf("\n");
    }
    return 0;
}


