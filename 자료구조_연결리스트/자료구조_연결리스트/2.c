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
    int arr1[100][100];
    int arr2[100][100];
    int arr3[100][100] ={0,};
    int p, r, q;
    scanf("%d %d", &p, &r);
    scanf("%d %d", &r, &q);
    for (int i=0; i<p; i++) {
        for(int j=0; j<r; j++) {
            scanf("%d", &arr1[i][j]);
        }
    }
    for (int i=0; i<r; i++) {
        for(int j=0; j<q; j++) {
            scanf("%d", &arr2[i][j]);
        }
    }
    
    for (int i=0; i<p; i++) {
        for(int j=0; j<q; j++) {
            for(int k=0; k<r; k++) {
                arr3[i][j] += arr1[i][k] * arr2[k][j]; // 00, 00 / 01, 10
            }
            printf("%d ", arr3[i][j]);
        }
        printf("\n");
    }
    return 0;
}


