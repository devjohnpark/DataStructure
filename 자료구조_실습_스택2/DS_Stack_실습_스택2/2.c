#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int stackSize, top;

void push(char *stack, char value) {
    stack[++(top)] = value;
}

char pop(char *stack) {
    return stack[(top)--];
}

int operand(char inArray){
    if (inArray == '+'){
        return 1;
    }
    else if (inArray == '-'){
        return 2;
    }
    else if (inArray == '*'){
        return 3;
    }
    else if (inArray == '/'){
        return 4;
    }
    else{
        return 0;
    }
}

int main(){
    int number, calculateNumber1, calculateNumber2, calculateSize;
    char inArray[100], stack[100];
    scanf("%d", &calculateSize);
    for (int i = 0; i < calculateSize; i++){
        top = -1;
        number = 0;
        scanf("%s", inArray);
        getchar();
        while (number != strlen(inArray)){
            if (operand(inArray[number]) == 0){
                push(stack, inArray[number] - '0');
            }
            else{
                if (operand(inArray[number]) == 1){
                    calculateNumber1 = pop(stack);
                    calculateNumber2 = pop(stack);
                    push(stack, calculateNumber1 + calculateNumber2);
                }
                else if (operand(inArray[number]) == 2){
                    calculateNumber1 = pop(stack);
                    calculateNumber2 = pop(stack);
                    push(stack, calculateNumber2 - calculateNumber1);
                }
                else if (operand(inArray[number]) == 3){
                    calculateNumber1 = pop(stack);
                    calculateNumber2 = pop(stack);
                    push(stack, calculateNumber2 * calculateNumber1);
                }
                else if (operand(inArray[number]) == 4){
                    calculateNumber1 = pop(stack);
                    calculateNumber2 = pop(stack);
                    push(stack, calculateNumber2 / calculateNumber1);
                }
            }
            number++;
        }
        printf("%d\n", pop(stack));
    }
}
