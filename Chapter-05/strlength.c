//
// Created by sergiy on 1/25/21.
//
#include <stdio.h>

int strlength(char *s){
    int n;
    for(n=0; *s != '\0'; n++, s++)
        ;
    return n;
}
int main(){
    printf("%d\n", strlength("hello, world"));
    return 0;
}