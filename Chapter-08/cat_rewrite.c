#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BLOCKSIZE 1024

void filecopy(int fd1, int fd2){
	int n;
	char buff[BLOCKSIZE];

	while ((n = read(fd1, buff, BLOCKSIZE)) > 0) {
        if (write(fd2, buff, n) != n) {
            printf("Cat cannot write\n");
            exit(0);
        }
	}
    if (n == -1) {
    printf("Cat cannot read");
        exit(0);
    }
	return;
}

int main(int argc, char *argv[]){
	if (argc == 1) {
		printf("Usage: ./cat file1, ...\n");
		exit(0);
	}
	int fd, i;
	i = 1;
	while (--argc > 0) {
		if ((fd = open(argv[i], O_RDONLY)) == -1) {
			printf("Cat cannot open %s\n", argv[i]);
			exit(0);
		}
		else {
			filecopy(fd, 1);
			close(fd);
			++i;
		}
	}
	return 0;
}
