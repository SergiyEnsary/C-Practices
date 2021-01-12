//
// Created by sergiy on 1/9/21.
//

#include <stdio.h>

/* count characters in input; 1st version */
int count_one(){
    long nc;

    nc = 0;
    while (getchar() != EOF){
        ++nc;
    }
    printf("%1d\n", nc);
    return 0;
}

/* count characters in input; 1st version */
int count_two(){
    double nc;

    for (nc = 0; getchar() != EOF; ++nc)
        ;
    printf("%.0f\n", nc);
    return 0;
}