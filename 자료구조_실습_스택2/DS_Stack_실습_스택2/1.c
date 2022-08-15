#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_SIZE 101

typedef char element;

typedef struct stackNode {
    element data;
    struct stackNode *next;
} stackNode;

stackNode *top;

int isEmpty() {
    if (top == NULL)
        return 1;
    else
        return 0;
}

// Create Node dynamically
static stackNode* AllocNode(void) {
    return calloc(1, sizeof(stackNode));
}

void push(element x) {
    stackNode *tmp = AllocNode(); // next stackNode
    tmp->data = x;
    tmp->next = top;
    top = tmp;
}

element pop() {
    if (!isEmpty()) {
        stackNode* tmp = top;
        element item = tmp->data;
        top = tmp->next;
        free(tmp);
        return item;
    }
    return '\0';
}

element peek() {
    if (!isEmpty()) {
        return top->data;
    }
    return '\0';
}

void init() {
    top = NULL;
}

void Terminate() {
    element tmp;
    element x;
    while (!isEmpty())  {  /* until empty */
        tmp = peek();
        if (tmp == '|' || tmp == '&') {
            printf("%c", tmp);
        }
        x = pop();
        if (x == '@') {
            x = '+';
        }
        else if (x == '#')
            x = '-';
        printf("%c", x); // +
    }
}

int getRank(element x) {
    switch (x) {
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

// 배열값과 스택 탑값 랭크 비교
int main() {
    int n;
    char arr[STACK_SIZE];
    element tmp;
    int rankStack;
    int rankArr;
    element x;
    
    scanf("%d", &n);
    getchar();
    
    init();
    
    // ( 스택 들어오면  ) 나타나야 팝
    // 우선순위 자기 보다 높으면 푸쉬 같거나 낮으면 팝
    for (int i=0; i<n; i++) {
        scanf("%s", arr);
        // 연산자 나올때 푸쉬 / 팝
        // 스택의 연산자가 배열의 연산자보다 우선 순위 낮으면 푸쉬(배열), 높으면 팝
        // 스택 비었을 어떡함 푸쉬
        // 나머지는 종료될떄 팝
        // 알파벳 제외 괄호는
        // 괄호 ( 최고 연산자
        // ( 푸쉬  > ) 만나면 팝 두번 연산자 한번 (한번
        // && || 처리 두개임
        for (int j=0; arr[j]!='\0'; j++) {
            if (arr[j] >= 'A' && arr[j] <= 'Z')
                printf("%c", arr[j]);
            else {
                tmp = peek();
                rankStack = getRank(tmp);
                if (j == 0 || (j > 0 && !(arr[j-1] >= 'A' && arr[j - 1] <= 'Z') && (arr[j] == '+' || arr[j] == '-'))) {
                    if (arr[j] == '+')
                        arr[j] = '@';
                    else if (arr[j] == '-')
                        arr[j] = '#';
                }
                rankArr = getRank(arr[j]);
                
                if (rankStack < rankArr) { // 스택의 연산자가 배열의 연산자보다 우선순위 낮으면 푸쉬
                    push(arr[j]);
                    if (arr[j] == '|' || arr[j] == '&')
                        j++;
                }
                else {
                    while (rankStack >= rankArr && !isEmpty()) {
                        if (tmp != '(') { // 탑 왼쪽 괄호 아닐때
                            if (tmp == '|' || tmp == '&') {
                                printf("%c", tmp);
                            }
                            x = pop();
                            if (x == '@') {
                                x = '+';
                            }
                            else if (x == '#')
                                x = '-';
                            printf("%c", x); // +
                        }
                        else { // 탑 ( 일때
                            if (arr[j] == ')') {
                                pop();
                                j++;
                            }
                            else
                                break;
                        }
                        tmp = peek(); // ( +
                        rankStack = getRank(tmp); // 7 4
                        rankArr = getRank(arr[j]);
                    }
                    if (arr[j] == '\0')
                        break;
                    if (arr[j] != ')') {
                        if (j == 0 || (j > 0 && !(arr[j-1] >= 'A' && arr[j - 1] <= 'Z') && (arr[j] == '+' || arr[j] == '-'))) {
                            if (arr[j] == '+')
                                arr[j] = '@';
                            else if (arr[j] == '-')
                                arr[j] = '#';
                        }
                        push(arr[j]);
                        if (arr[j] == '|' || arr[j] == '&')
                            j++;
                    }
                }
            }
        }
        Terminate();
        printf("\n");
    }
    return 0;
}
