//
//  4.c
//  배열
//
//  Created by Junseo Park on 2022/04/06.
//


#include <stdio.h>

int main() {
    int n;
    int arr[100][100];
    int state = 0;
    int tmp = 1;

    int x = 0, y = 0;
    
    scanf("%d", &n);
    
    int row = n;
    
    while (n > 0) {
        switch(state) {
            case 0:
                // 윗변
                for (int i=0; i<n; i++) { // 1, 2
                    arr[x++][y++] = tmp++; // 13
                }
                x--;
                y--;
                n--; // 2
                break;
            case 1:
                // 오른쪽 변
                for (int i=0; i<n; i++) { // 1, 2
                    arr[x][--y] = tmp++; // 13
                }
                n--;
                break;
            case 2:
                // 아래 변
                for (int i=0; i<n; i++) { // 1, 2
                    arr[--x][y] = tmp++; // 13
                }
                n--;
                break;
        }
        
        
        
        if(state == 2) {
            state = 0;
            x++;
            y++;
        }
        else
            state++;
    }

    for (int i=0; i<row; i++) {
        for (int j=0; j<=i; j++) {
            // 위
            printf(" %d", arr[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}


