
#include "../../includes/cub3d.h"

int dot_chk(char *path)
{
    int l;

    l = ts_strlen(path);
    if (l < 5)
        return (1);
    if (path[l - 4] == '.' && path[l - 3] == 'c' &&
        path[l - 2] == 'u' && path[l - 1] == 'b')
        return 0;
    return 1;
}
