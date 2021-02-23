#include "syscalls.h"

FILE _iob[OPEN_MAX] = {
        { 0, (char *) 0, (char *) 0, _READ, 0 },
        { 0, (char *) 0, (char *) 0, _WRITE, 1},
        { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2}
};
