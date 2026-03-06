
#include "../../includes/cub3d.h"

int ts_mt(char *lain)
{
    int i;

    i = ts_spaces_skip(lain);
    if (lain[i])
        return 0;
    return 1;
}

char *get_lain(int fd)
{
    char *lain;

    if (fd < 0)
        return NULL;
    lain = gnl(fd);
    while (lain)
    {
        if (!ts_mt(lain))
            return lain;
        free(lain);
        lain = gnl(fd);
    }
    return NULL;
}

void ts_free_pear(t_teto *head)
{
    t_teto *pear;

    while (head)
    {
        pear = head;
        head = head->next;
        free(pear->val);
        free(pear);
    }
}

t_teto *ts_read_head(int fd)
{
    t_teto *head;
    char *lain;

    head = NULL;
    lain = get_lain(fd);
    if (!lain)
        return NULL;
    head = ts_key(lain);
    free(lain);
    if (!head)
        return NULL;
    return head;
}

t_teto *ts_read(int fd)
{
    t_teto *pear;
    t_teto *head;
    char *lain;
    int yes;

    yes = 1;
    head = ts_read_head(fd);
    if (!head)
        return NULL;
    pear = head;
    while (yes < 6)
    {
        lain = get_lain(fd);
        if (!lain)
            return (ts_free_pear(head), NULL);
        pear->next = ts_key(lain);
        free(lain);
        if (!pear->next)
            return (ts_free_pear(head), NULL);
        pear = pear->next;
        yes++;
    }
    return head;
}
