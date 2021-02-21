#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX_SIZE 1024

int find(char *pattern, FILE *fp){
    int found = 0;
    char line[LINE_MAX_SIZE];

    while (fgets(line, LINE_MAX_SIZE, fp) != NULL) {
        if (strstr(line, pattern) != NULL) {
            fprintf(stdout, "%s", line);
            ++found;
        }
    }
    return (found == 0) ? 0 : 1;
}

int main(int argc, char *argv[]){
    char *pattern;
    int found = 0;

    if (argc == 1) {
        printf("Pattern program usage: Pattern file_1, file_2, ...\n\n");
        return 0;
    }
    pattern = *++argv;
    if (*++argv == NULL) {
        found = find(pattern, stdin);
        if (found == 1) {
            printf("\nPattern found in stdin file\n");
        }
        exit(0);
    }
    else {
        FILE *fp;
        char *prog;
        while (--argc > 1) {
            prog = *argv;
            if ((fp = fopen(*argv++, "r")) == NULL) {
                fprintf(stderr, "can't open %s\n", prog);
                exit(1);
            }
            else {
                found = find(pattern, fp);
                if (found == 1) {
                    printf("Pattern found in %s file\n\n", prog);
                }
            }
        }
    }
    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", argv[0]);
        exit(2);
    }
    exit(0);
}
