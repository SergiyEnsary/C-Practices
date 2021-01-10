//
// Created by sergiy on 1/9/21.
//

#include <stdio.h>

/* count lines in input; */
int count_line(){
    int c, n1;
    n1 = 0;
    while ((c = getchar()) != EOF)
        if (c == '\n')
            ++n1;
    printf("%d\n", n1);
    return 1;
}