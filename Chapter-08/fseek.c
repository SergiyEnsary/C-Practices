#include "syscalls.h"
#include <unistd.h>

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2


int fseek(FILE *fp, long offset, int origin){
	if (fp->flag.is_read == 0) {
		return -1;
	}
	if (origin == SEEK_SET) {
		if (offset < fp->cnt) {
			fp->ptr = fp->base + offset;
			fp->cnt = offset;
			lseek(fp->fd, offset, origin);
			fp->flag.is_eof = 0;
		}
		else {
			return fp->cnt - offset;
		}
	}
	else if (origin == SEEK_CUR) {
	    if (offset < fp->cnt) {
			fp->ptr += fp->cnt - (fp->cnt - offset);
            fp->cnt = offset;
            lseek(fp->fd, offset, origin);
            fp->flag.is_eof = 0;
		}
		else {
			return fp->cnt - offset;
		}
	}
	else if (origin == SEEK_END) {
		if (offset <= 0 && fp->ptr + offset >= fp->base) {
			fp->ptr += offset;
            fp->cnt = lseek(fp->fd, offset, origin);
            fp->flag.is_eof = 0;
		}
	}
	else {
		return -1;
	}
	return 0;
}
