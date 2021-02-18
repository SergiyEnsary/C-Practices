#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define DEFAULT 1

int main(int argc, char *argv[]){
	int state = 0;
	int c;
	int (* convert)(int);


	if (argc == 1) {
		printf("usage \"./program -lower\" to lower case or \"./program -upper\" to upper case and \"./program -default\" to no conversion\n");
		return 0;
	}
	else {
		if (strcmp("-lower", argv[1]) == 0)
			convert = tolower;
		else if (strcmp("-upper", argv[1]) == 0)
			convert = toupper;
		else if (strcmp("-default", argv[1]) == 0)
			state = DEFAULT;
		else {
			printf("Wrong option\n");
			return -1;
		}
	}
	if (state == DEFAULT)
		while ((c = getchar()) != EOF)
			putchar(c);
	else
		while ((c = getchar()) != EOF)
			putchar(convert(c));
	return 0;
}
