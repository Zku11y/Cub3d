
#include "../head.h"

int ts_check_data(t_nc *nu)
{
    // int i;

    // i = NO;
    if (!nu)
        return 1;
    if (!nu->imgs[NO] || !nu->imgs[SO]
        || !nu->imgs[WE] || !nu->imgs[EA])
        return 1;
    // while (i <= EA)
    // {
    //     nu->txtrs[i] = mlx_load_png(nu->imgs[i]);
    //     if (!nu->txtrs[i])
    //         return 1;
    //     i++;
    // }
    return 0;
}
