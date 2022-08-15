//
//  main.c
//  자료구조_연결리스트
//
//  Created by Junseo Park on 2022/04/13.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void palindrome(char *str, int st, int en) {
    if (st < en) {
        if (str[st] == str[en])
            palindrome(str, ++st, --en);
        else
            printf("none");
    }
    else  { // st > en
        printf("palindrome");
    }
    
}

int main() {
    char *str = NULL;
    
    str = (char *)malloc(sizeof(char) * 100);
    
    scanf("%s", str);
    
    palindrome(str, 0, strlen(str) - 1);
    
    free(str);
    
    return 0;
}


