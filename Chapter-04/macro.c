//
// Created by sergiy on 1/22/21.
//
#include <stdio.h>
#define forever for(;;) /* infinite loop */
#define max(A, B) ((A) > (B) ? (A) : (B))

int main(){
    int num = max(4,9);
    printf("%d\n", num);
}