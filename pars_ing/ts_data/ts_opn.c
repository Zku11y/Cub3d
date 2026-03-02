
#include "../head.h"

int ts_opn(char *path)
{
    int fd;

    if (dot_chk(path))
        return -1;
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return -1;
    return fd;
}
