#include <stdio.h>

/* echo command-line arguments; 1st version */
int echo_one(int argc, cahr *argv[]){
    int i;

    for (i = 1; i < argc; i++)
        printf("%s%s", argv[i], (i < argc-1) ? " ": "");
    printf("\n");
    return 0;
}

/* echo command-line arguments; 2nd version */
int echo_two( int argc, char *argv[]){
    while (--argc > 0)
        printf("%s%s", *++argv, (argc > 1) ? " ": "");
    printf("\n");
    return 0;
}
