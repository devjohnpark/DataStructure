//
//  6.c
//  자료구조 - 재귀
//
//  Created by Junseo Park on 2022/04/01.
//

#include <stdio.h>

int gcd(int a, int b) {
    if (b > 0)
        return gcd(b, a % b);
    else
        return a;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d", gcd(a, b));
    return 0;
}



