//
// Created by sergiy on 1/14/21.
//

#include <stdio.h>

int binsearch(int x, int v[5], int n);

int main(){
    int x, n;
    int array[] = { 2, 3, 4, 10, 40 };

    printf(binsearch(10, array, 5));
}

int binsearch(int x, int v[], int n){
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high){
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}