
#include "../head.h"

void free_mp(t_mp *mp)
{
    t_mp *ts;

    while (mp)
    {
        if (mp->val)
            free(mp->val);
        ts = mp;
        mp = mp->next;
        free(ts);
    }
}

void free_nu_map(char **nu)
{
    int i;

    i = 0;
    while (nu[i])
    {
        free(nu[i]);
        i++;
    }
    free(nu);
}

char *get_mp_lain(char *lain, int x_min, int x_max)
{
    char *nu;
    int i;

    i = 0;
    nu = ts_calloc(x_max - x_min + 2, sizeof(char));
    if (!nu)
        return NULL;
    while (lain[x_min + i] && lain[x_min + i] != '\n' && i < (x_max - x_min + 1))
    {
        nu[i] = lain[x_min + i];
        i++;
    }
    while (i < x_max - x_min + 1)
        nu[i++] = ' ';
    return nu;
}

int get_mapsize(t_mp *mp)
{
    t_mp *ts;
    int i;

    i = 0;
    ts = mp;
    while (ts)
    {
        i++;
        ts = ts->next;
    }
    return i;
}

int get_long(t_mp *mp, int *x_min, int *x_max)
{
    int i;
    t_mp *ts;

    ts = mp;
    *x_min = INT_MAX;
    *x_max = INT_MIN;
    while (ts)
    {
        i = 0;
        while (ts->val[i])
        {
            if (ts->val[i] != ' ' && !(ts->val[i] >= 9 && ts->val[i] <= 13))
            {
                if (i < *x_min)
                    *x_min = i;
                if (i > *x_max)
                    *x_max = i;
            }
            i++;
        }
        ts = ts->next;
    }
    return *x_max - *x_min + 1;
}

t_mp *ts_read_map(int fd)
{
    t_mp *head;
    t_mp *ts;
    char *lain;

    lain = get_lain(fd);
    if (!lain)
        return NULL;
    head = ts_calloc(1, sizeof(t_mp));
    if (!head)
        return (free(lain), NULL);
    head->val = lain;
    ts = head;
    while (1)
    {
        lain = get_lain(fd);
        if (!lain)
            break;
        ts->next = ts_calloc(1, sizeof(t_mp));
        if (!ts->next)
            return (free_mp(head), NULL);
        ts = ts->next;
        ts->val = lain;
    }
    return head;
}

int get_map(int fd, t_nc *nu)
{
    t_mp *mp;
    t_mp *ts;
    int x[2];
    int i;

    i = 0;
    mp = ts_read_map(fd);
    if (!mp)
        return 1;
    nu->x = get_long(mp, &x[0], &x[1]);
    nu->y = get_mapsize(mp);
    nu->map = ts_calloc(nu->y + 1, sizeof(char *));
    if (!nu->map)
        return (free_mp(mp), 1);
    ts = mp;
    while (ts)
    {
        nu->map[i] = get_mp_lain(ts->val, x[0], x[1]);
        if (!nu->map[i])
            return (free_mp(mp), free_nu_map(nu->map), 1);
        i++;
        ts = ts->next;
    }
    free_mp(mp);
    return 0;
}
