
#include "../head.h"

t_nc *ts_make_one(int fd)
{
    t_teto *ts;
    t_nc *nu;

    ts = ts_read(fd);
    if (!ts)
        return NULL;
    nu = ts_put(ts);
    ts_free_pear(ts);
    if (!nu)
        return NULL;
    if (ts_check_data(nu))
        return (ts_free_one_nomap(nu), NULL);
    if (get_map(fd, nu))
        return (ts_free_one_nomap(nu), NULL);
    if (rec_map(nu->map, nu))
    {
        free_nu_map(nu->map);
        ts_free_one_nomap(nu);
        ts_putstr_fd("ASS MAP\n", 2);
        return NULL;
    }
    return nu;
}

// void t()
// {
//     system("leaks a.out");
// }

// int main(int ac, char **av)
// {
//     if (ac != 2)
//         return 1;
//     atexit(t);
//     int fd = ts_opn(av[1]);
//     t_nc *nu;
//     nu = ts_make_one(fd);
//     close(fd);
//     if (!nu)
//         return 1;
//     ts_putstr_fd(nu->imgs[NO], 2);
//     ts_putstr_fd("|\n", 2);
//     ts_putstr_fd(nu->imgs[SO], 2);
//     ts_putstr_fd("|\n", 2);
//     ts_putstr_fd(nu->imgs[WE], 2);
//     ts_putstr_fd("|\n", 2);
//     ts_putstr_fd(nu->imgs[EA], 2);
//     ts_putstr_fd("|\n", 2);
//     printf("F0x%08x\n", nu->flor);
//     printf("C0x%08x\n", nu->ceil);
//     printf("x%dy%d\n", nu->x, nu->y);
//     ts_putstr_fd("\n", 2);
//     int i = 0;
//     while (nu->map[i])
//     {
//         ts_putstr_fd("|", 2);
//         ts_putstr_fd(nu->map[i], 2);
//         ts_putstr_fd("|\n", 2);
//         i++;
//     }
//     ts_putstr_fd("\n", 2);
//     ts_free_one_nomap(nu);
//     free_nu_map(nu->map);
//     return 0;
// }