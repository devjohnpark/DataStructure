//
//  4.c
//  자료구조 - 재귀
//
//  Created by Junseo Park on 2022/03/29.
//

#include <stdio.h>

int findMax(int arr[], int n) {
    
    if (n == 0)
        return arr[n];
    
    int max = findMax(arr, n - 1); // max 값 초기화
    
    return max > arr[n] ? max : arr[n]; // 큰 값 저장
}

int main() {
    int n;
    int arr[20];
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("%d", findMax(arr, n - 1));
    
    return 0;
}
