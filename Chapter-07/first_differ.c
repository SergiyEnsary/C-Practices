#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX_SIZE 1024

int main(int argc, char *argv[]){
    FILE *fp;
    char line_1[LINE_MAX_SIZE];
    char line_2[LINE_MAX_SIZE];
    char *prog = argv[0];

    if (argc == 1) {
        while (1) {
            if ((fgets(line_1, LINE_MAX_SIZE, stdin) != NULL) && (fgets(line_2, LINE_MAX_SIZE, stdin) != NULL)) {
                if (strcmp(line_1, line_2) != 0) {
                    fputs(line_1, stdout);
                    fputs(line_2, stdout);
                    break;
                }
            }
            else {
                break;
            }
        }
    }
    else {
        if ((fp = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "%s: can't open %s\n", prog, *argv);
            exit(1);
        }
        else {
            FILE *fp_2;
            if (*++argv == NULL) {
                fp_2 = stdin;
            }
            else if ((fp_2 = fopen(*argv, "r")) == NULL) {
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(1);
            }
            while (1) {
                if ((fgets(line_1, LINE_MAX_SIZE, fp) != NULL) && (fgets(line_2, LINE_MAX_SIZE, fp_2) != NULL)) {
                    if (strcmp(line_1, line_2) != 0) {
                        fputs(line_1, stdout);
                        fputs(line_2, stdout);
                        break;
                    }
                }
                else {
                    break;
                }
            }
        }
    }
    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }
    exit(0);
}
