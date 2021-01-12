//
// Created by sergiy on 1/10/21.
//

#include <stdio.h>

#define IN 1
#define OUT 0

/* count lines, words, and characters in input */
int main (){
    int c, n1, nw, nc, state;

    state = OUT;
    n1 = nw = nc = 0;
    while ((c = getchar()) != EOF){
        ++nc;
        if (c == '\n')
            ++n1;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT){
            state = IN;
            ++nw;
        }
    }
    printf("%d %d %d\n", n1, nw, nc);
    return 0;
}