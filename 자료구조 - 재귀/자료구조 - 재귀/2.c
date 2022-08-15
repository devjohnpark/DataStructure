//
//  main.c
//  자료구조 - 재귀
//
//  Created by Junseo Park on 2022/03/23.
//

#include <stdio.h>

void digit_separation(int n) {
    if (n > 0) {
        digit_separation(n / 10);
        printf("%d\n", n % 10);
    }
}

int main() {
    int n;
    
    scanf("%d", &n);

    digit_separation(n);
    
    return 0;
}
