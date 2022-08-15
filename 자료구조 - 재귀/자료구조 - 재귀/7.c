//
//  7.c
//  자료구조 - 재귀
//
//  Created by Junseo Park on 2022/04/01.
//

#include <stdio.h>

int findChar(char *str, char ch, int cnt) {
    if (*str == '\0') {
        return cnt;
    } else {
        if (*str == ch)
            cnt++;
        return findChar(str + 1, ch, cnt);
    }
}
int main() {
    char str[101] = "\0";
    char ch;
    
    scanf("%s", str);
    getchar();
    scanf("%c", &ch);
    
    printf("%d", findChar(str, ch, 0));
    
    return 0;
}
