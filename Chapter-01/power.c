//
// Created by sergiy on 1/11/21.
//

#include <stdio.h>

int power(int m, int n);
int power_two(int m, int n);

/* test power function */
int main(){
    int i;
    for (i = 0; i < 10; i++)
        printf("%d %d %d", i, power(2, i), power(-3, i));
    for (i = 0; i < 10; i++)
        printf("%d %d %d", i, power_two(2, i), power_two(-3, i));
    return 0;
}

/* power: raise base to n-th power; n >= 0 */
int power(int base, int n){
    int i, p;
    p = 1;
    for (i = 1; i <= n; ++i)
        p *= base;
    return p;
}

int power_two(int base, int n){
    int p;
    for (p = 1; n > 0; --n)
        p += base;
    return p;
}