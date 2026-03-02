
#include "../head.h"

int rec(char **map, int x, int y, int m_x, int m_y)
{
    if (x < 0 || y < 0 || x >= m_x || y >= m_y)
        return 1;
    if (map[x][y] == ' ' || map[x][y] == '\0')
        return 1;
    if (map[x][y] == '8' || map[x][y] == '1')
        return 0;
    if (map[x][y] == '0' || map[x][y] == 'N'  || map[x][y] == 'S'
            || map[x][y] == 'E' || map[x][y] == 'W')
        map[x][y] = '8';
    else
        return 0;
    if (rec(map, x + 1, y, m_x, m_y) == 1)
        return 1;
    if (rec(map, x, y + 1, m_x, m_y) == 1)
        return 1;
    if (rec(map, x - 1, y, m_x, m_y) == 1)
        return 1;
    if (rec(map, x, y - 1, m_x, m_y) == 1)
        return 1;
    return 0;
}

int chk_plyr(char **map)
{
    int (i), (j), (s);

    i = 0;
    s = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'S'
                || map[i][j] == 'E' || map[i][j] == 'W')
                s++;
            else if (map[i][j] != '0' && map[i][j] != '1'
                && map[i][j] != ' ' && !(map[i][j] >= 9 && map[i][j] <= 13))
                return 1;
            if (s > 1)
                return 1;
            j++;
        }
        i++;
    }
    if (s == 0)
        return 1;
    return 0;
}

t_plyr *get_plyr(char **map)
{
    t_plyr *hi;

    if (chk_plyr(map))
        return NULL;
    hi = ts_calloc(1, sizeof(t_plyr));
    if (!hi)
        return NULL;
    hi->y = 0;
    while (map[hi->y])
    {
        hi->x = 0;
        while (map[hi->y][hi->x])
        {
            if (map[hi->y][hi->x] == 'N' || map[hi->y][hi->x] == 'S'
                || map[hi->y][hi->x] == 'E' || map[hi->y][hi->x] == 'W')
            {
                hi->who = map[hi->y][hi->x];
                return hi;
            }
            hi->x++;
        }
        hi->y++;
    }
    free(hi);
    return NULL;
}

void map_cln(char **map, int x, int y, t_plyr *hi)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == '8')
                map[i][j] = '0';
            j++;
        }
        i++;
    }
    map[x][y] = hi->who;
}

int rec_map(char **map)
{
    int m_x;
    int m_y;
    t_plyr *hi;
    int ret;

    m_x = 0;
    while (map[m_x])
        m_x++;
    m_y = ts_strlen(map[0]);
    if (m_x < 3 || m_y < 3)
        return 1;
    hi = get_plyr(map);
    if  (!hi)
        return 1;
    ret = rec(map, hi->y, hi->x, m_x, m_y);
    map_cln(map, hi->y, hi->x, hi);
    free(hi);
    return ret;
}
