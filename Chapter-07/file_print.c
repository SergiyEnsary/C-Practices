#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void filecopy(FILE *ifp, FILE *ofp){
    int c;

    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);
}

int main(int argc, char *argv[]){
	if (argc == 1) {
		fprintf(stdout, "Usage: ./prog.out file_1, file_2, ...\n");
		return 0;
	}
	char *prog = argv[0];
	FILE *fp;
	unsigned page = 1;
	char *title = "\f#################################################\n\tFile: %s Page: %u\t\t\n#################################################\n\n";

	 while (--argc > 0) {
        if ((fp = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "can't open %s\n", *argv);
            exit(1);
        } else {
            printf(title, *argv, page);
            filecopy(fp, stdout);
            fclose(fp);
            ++page;
        }
	}
    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }
    exit(0);
}
