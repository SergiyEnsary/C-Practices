//
// Created by sergiy on 1/9/21.
//

#include <stdio.h>

/* copy input to output; 1st version */

int copy_one(){
    int c;

    c = getchar();
    while (c != EOF){
        putchar(c);
        c = getchar();
    }
    return 1;
}

/* copy input to output; 2nd version */

int copy_two(){
    int c;
    while ((c = getchar()) != EOF) {
        putchar(c);
    }
    return 1;
}