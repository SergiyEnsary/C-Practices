#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "syscalls.h"

int _flushbuf(int c, FILE *file){
	if (file < _iob || file >= _iob + OPEN_MAX) {
        return EOF;
    }
	int bufsize;
	bufsize = (file->flag.is_unbuf == 1) ? 1 : BUFSIZ;
	if (file->flag.is_write != 1) {
		return EOF;
	}
	if (file->flag.is_eof == 1 || file->flag.is_err == 1) {
		return EOF;
	}
	if (file->base == NULL && file->flag.is_unbuf == 0) {
        if ((file->base = (char *) malloc(bufsize)) == NULL) {
			file->flag.is_unbuf = 1;
			file->flag.is_err = 1;
            file->cnt = 0;
			file->ptr = file->base;
			return EOF;
		}
	}
	else {
		if (write(file->fd, file->base, bufsize) == -1) {
			file->flag.is_err = 1;
			return EOF;
		}
	}
	file->cnt = 0;
	file->ptr = file->base;
	*file->ptr++ = c;
	return c;
}

int fflush(FILE *stream){
	if (stream < _iob || stream >= _iob + OPEN_MAX) {
		return EOF;
	}
	int retval;
    FILE *fp;

    retval = 0;

    if (stream == NULL) {
        for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
            if (fp->flag.is_write == 0 && fflush(fp) == -1)
                retval = -1;
    }
	else {
        if (stream->flag.is_write == 0) {
            return -1;
		}
        _flushbuf(EOF, stream);
        if (stream->flag.is_err) {
            retval = -1;
		}
   	 }
    return retval;
}

int fclose(FILE *file){
	int fd;

    if (file == NULL) {
        return -1;
	}
    fd = file->fd;
    fflush(file);
    file->cnt = 0;
    file->ptr = NULL;
    if (file->base != NULL) {
       	free(file->base);
	}
    file->base = NULL;
    file->flag.is_write = 0;
	file->flag.is_read = 0;
	file->flag.is_unbuf = 0;
	file->flag.is_eof = 0;
	file->flag.is_err = 0;
    file->fd = -1;
    return close(fd);
}

int main(void)
{
	return 0;
}
