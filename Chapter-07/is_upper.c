#include <stdio.h>

#define ISUPPER(c) (c >= 'A' && c <= 'Z') ? 1 : 0 /* time saving */

int is_upper(int c){ /* space saving */
    if(c >= 'A' && c <= 'Z')
        return 1;
    else
        return 0;
}

int main(void){
	printf("%d\n", ISUPPER('A'));
	printf("%d\n", ISUPPER('g'));
	printf("%d\n", is_upper('A'));
    printf("%d\n", is_upper('g'));

	return 0;
}
