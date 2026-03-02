
#include "head.h"

void ts_print_nu(t_nc *nu)
{
    t_nc *ts;
    int i;
    int x;

    ts = nu;
    i = 0;
    if (!ts)
        return ts_putstr_fd("nu is NULL\n", 2);
    ts_putstr_fd("\n", 1); 
    ts_putstr_fd("ts START::\n", 1);
    while (ts)
    {
        ts_putstr_fd("nu=", 1);
        ts_putnbr_fd(i, 1);
        ts_putstr_fd("|\n", 1);
        ts_putstr_fd("NO ", 1);
        ts_putstr_fd(ts->imgs[NO], 1);
        ts_putstr_fd("|\n", 1);
        ts_putstr_fd("SO ", 1);
        ts_putstr_fd(ts->imgs[SO], 1);
        ts_putstr_fd("|\n", 1);
        ts_putstr_fd("WE ", 1);
        ts_putstr_fd(ts->imgs[WE], 1);
        ts_putstr_fd("|\n", 1);
        ts_putstr_fd("EA ", 1);
        ts_putstr_fd(ts->imgs[EA], 1);
        ts_putstr_fd("|\n", 1);
        ts_putstr_fd("F::", 1);
        ts_putstr_fd("R", 1);
        ts_putnbr_fd(ts->flor_r, 1);
        ts_putstr_fd("G", 1);
        ts_putnbr_fd(ts->flor_g, 1);
        ts_putstr_fd("B", 1);
        ts_putnbr_fd(ts->flor_b, 1);
        ts_putstr_fd("|\n", 1);
        ts_putstr_fd("C::", 1);
        ts_putstr_fd("R", 1);
        ts_putnbr_fd(ts->ceil_r, 1);
        ts_putstr_fd("G", 1);
        ts_putnbr_fd(ts->ceil_g, 1);
        ts_putstr_fd("B", 1);
        ts_putnbr_fd(ts->ceil_b, 1);
        ts_putstr_fd("|\n", 1);
        ts_putstr_fd("x", 1);
        ts_putnbr_fd(ts->x, 1);
        ts_putstr_fd(" |", 1);
        ts_putstr_fd("y", 1);
        ts_putnbr_fd(ts->y, 1);
        ts_putstr_fd("|\n", 1);
        ts_putchar(ts->hi->who, 1);
        ts_putstr_fd("::", 1);
        ts_putstr_fd("x", 1);
        ts_putnbr_fd(ts->hi->x, 1);
        ts_putstr_fd("|y", 1);
        ts_putnbr_fd(ts->hi->y, 1);
        ts_putstr_fd("|\n", 1);
        x = 0;
        while (ts->map[x])
        {
            ts_putstr_fd("|", 1);
            ts_putstr_fd(ts->map[x], 1);
            ts_putstr_fd("|\n", 1);
            x++;
        }
        ts_putstr_fd("\n", 1);
        ts_putstr_fd("end.\n", 1);
        ts = ts->next;
        i++;
    }
    ts_putstr_fd("ts END.\n", 1);
}

// void feet()
// {
//     system("leaks cub-tst");
// }

int main(int ac, char **av)
{
    t_nc *nu;

    nu = NULL;
//     atexit(feet);
    if (ac < 2)
        return 1;
    nu = ts_pars(&av[1]);
    if (!nu)
        return 1;
    ts_print_nu(nu);
    free_nu(nu);
    return 0;
}
