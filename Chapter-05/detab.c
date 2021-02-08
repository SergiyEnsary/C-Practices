#include <stdio.h>

#define DEFSTOP  8
#define MAXSTOPS 100

int getstop(char *s);

int main(int argc, char *argv[])
{
	int c, n;
	unsigned char col;
	unsigned char stop[MAXSTOPS];

	if (argc-- > MAXSTOPS)
		return 2;
	for (c = n = 0; n < argc; n++) {
		int temp;
		temp = getstop(*++argv);
		if (temp <= c)
			return 1;
		stop[n] = temp - c;
		c = temp;
	}
	if (n == 0)
		stop[n++] = DEFSTOP;
	stop[n] = 0;
	col = n = 0;
	while ((c = getchar()) != EOF) {
		switch (c) {
		case '\t':
			do {
				putchar(' ');
			} while (stop[n] > ++col);
			if (stop[n] && stop[1])
				n++;
			col = 0;
			break;
		case '\n':
			putchar(c);
			col = n = 0;
			break;
		default:
			putchar(c);
			if (col == stop[n] - 1) {
				col = 0;
				if (stop[n] && stop[1])
					n++;
			}
			else
				++col;
			break;
		}
	}
	return 0;
}

int getstop(char *cp){
	int n;
	for (n = 0; *cp != '\0'; cp++) {
		if (*cp < '0' || *cp > '9')
			return -1;
		n = 10 * n + *cp - '0';
	}
	return n;
}
