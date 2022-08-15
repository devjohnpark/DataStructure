//
//  main.c
//  자료구조_연결리스트
//
//  Created by Junseo Park on 2022/04/13.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int n;
    int tmp;
    int arr1[100][100];
    int arr2[100][100];
    // 5
    scanf("%d", &n);
    for (int i=0; i<n; i++) {
        scanf("%d", &tmp);
        for (int j=n-1; j>=0; j--) {
            arr1[i][j] = tmp % 2;
            tmp /= 2;
        }
    } // 6/2
    for (int i=0; i<n; i++) {
        scanf("%d", &tmp);
        for (int j=n-1; j>=0; j--) {
            arr2[i][j] = tmp % 2;
            tmp /= 2;
        }
    }
    
    for (int i=0; i<n; i++) {
        int result = 0;
        for (int j=n-1, num = 1; j>=0; j--, num*=2) {
            if(arr2[i][j] == 1) {
                arr1[i][j] = 1;
            }
            result += arr1[i][j] * num;
        }
        printf("%d ", result);
    }
    
    return 0;
}


