#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct stack {
   char ch[201];
   int top;
}stack;

//스텍엔 연산자만 넣을거다
void opPop(stack*, int);
void toPrint(char );
void freestack(stack*);
stack* initstack();
int isoperand(char);
char peek(stack*);
char pop(stack*);
void push(stack*, char);
int rank(char);

int main() {
   stack* s;
   int r, n;
   s = initstack();
   char str[101], a;
   scanf("%d", &n);
   for (int q = 0; q < n; q++) {
      scanf("%s", str);
      for (int i = 0; i < (int)strlen(str); i++) {
         if (isoperand(str[i])) printf("%c", str[i]);
         else if (str[i] == '(') push(s, '(');
         else if (str[i] == ')') {
            opPop(s, -2);
         }
         else {
            if ((i == 0 || ((str[i - 1] != ')' && isoperand(str[i - 1]) == 0)))) {
               if (str[i] == '+')
                  str[i] = '@';
               else if (str[i] == '-')
                  str[i] = '#';
            }
            r = rank(str[i]);
            opPop(s, r);
            if (r == 1 || r == 2) i++;
            push(s, str[i]);

         }
      }
      while (s->top >= 0) {
         a = pop(s);
         toPrint(a);
      }
      printf("\n");
   }
   freestack(s);

}
void opPop(stack* s,int r) {
   int a;
   while (peek(s)!='('&& s->top >= 0 && r <= rank(peek(s))) {
      a = pop(s);
      toPrint(a);
   }
   if (r == -2 && peek(s) == '(') pop(s);
}

void toPrint(char ch) {
   if (ch == '|' || ch == '&') printf("%c",ch);
   if (ch == '@') printf("+");
   else if (ch == '#') printf("-");
   else printf("%c", ch);
}

int rank(char a) {
   switch (a) {
   case '!':case'@':case'#':
      return 6;
   case'*':case'/':
      return 5;
   case'+':case'-':
      return 4;
   case'>':case'<':
      return 3;
   case'&':
      return 2;
   case'|':
      return 1;
   }
   return -1;
}

void freestack(stack* s) {
   free(s);
}

stack* initstack() {
   stack* s = (stack*)malloc(sizeof(stack));
   if (s == NULL) exit(0);
   s->top = -1;
   return s;
}
int isoperand(char a) {
   if (a >= 'A' && a <= 'Z') return 1;
   else return 0;
}

char peek(stack* s) {
   if (s->top >= 0) return s->ch[s->top];
   else return 0;
}
char pop(stack* s) {
   char a = 0;
   if (s->top >= 0) {
      a = s->ch[s->top];
      s->top -= 1;
   }
   return a;


}
void push(stack* s, char a) {
   if (s->top < 100) {
      s->top += 1;
      s->ch[s->top] = a;
   }
}
