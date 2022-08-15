//
//  5.c
//  자료구조 - 재귀
//
//  Created by Junseo Park on 2022/04/01.
//

#include <stdio.h>

void towersOfHanoi(int n, char from, char by, char to) {
    if (n == 1) { // exit condition
        printf("%c %c\n", from, to); // 맨 위(가장 작은) 디스크 이동
    }
    else {
        towersOfHanoi(n - 1, from, to, by); // a b로 이동 나머지(n - 1) 디스크 이동
        printf("%c %c\n", from, to);    // 맨 아래 디스크 이동
        towersOfHanoi(n - 1, by, from, to); // b c로 이동 (n - 1개) 나머지 디스크 이동
    }
}

int main() {
    int n;
    scanf("%d", &n);
    towersOfHanoi(n, 'A', 'B', 'C');
    return 0;
}
