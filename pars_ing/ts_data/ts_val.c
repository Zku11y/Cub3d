
#include "../../includes/cub3d.h"

int ts_spaces_skip(char *str)
{
    int i;

    i = 0;
    while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
        i++;
    return i;
}

char *ts_get_val(char *str)
{
    int i;
    int j;
    int l;

    j = 0;
    l = 0;
    if (!str)
        return NULL;
    i = ts_spaces_skip(str);
    if (!str[i])
        return NULL;
    l = i;
    while (str[l] && !(str[l] == ' ' || (str[l] >= 9 && str[l] <= 13)))
        l++;
    j = l + ts_spaces_skip(&str[l]);
    if (str[j])
        return NULL;
    return ts_strndup(&str[i], l - i);
}

int ts_ahh_chk(char *str)
{
    int i;
    int a;

    i = 0;
    if (!str)
        return 1;
    while (str[i])
    {
        a = 0;
        if (ts_isdigit(str[i]) && str[i + 1])
        {
            i++;
            a = ts_spaces_skip(&str[i]);
            i += a;
            if (a > 0  && str[i] && ts_isdigit(str[i]))
                return 1;
            continue ;
        }
        i++;
    }
    return 0;
}

char *ts_get_rgb_val(char *str)
{
    int (i), (n);
    char *nu;

    i = 0;
    n = 0;
    if (!str || ts_ahh_chk(str))
        return NULL;
    while (str[i])
    {
        if (!(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
            n++;
        i++;
    }
    nu = ts_calloc(n + 1, sizeof(char));
    if (!nu)
        return NULL;
    i = 0;
    n = 0;
    while (str[n])
    {
        if (str[n] && !(str[n] == ' ' || (str[n] >= 9 && str[n] <= 13)))
            nu[i++] = str[n];
        n++;
    }
    return nu;
}
