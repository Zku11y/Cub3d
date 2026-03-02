
#ifndef HEAD_H
#define HEAD_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#include "libts/libts.h"

typedef enum e_key
{
    NO,
    SO,
    WE,
    EA,
    F,
    C
} t_key;

typedef struct s_plyr
{
    int x;
    int y;
    char who;
} t_plyr;

typedef struct s_mp
{
    char *val;
    struct s_mp *next;
} t_mp;

typedef struct s_teto
{
    char *val;
    struct s_teto *next;
    t_key key;
} t_teto;

typedef struct s_nc
{
    char *imgs[4];
    // mlx_texture_t *txtrs[4];
    struct s_nc *next;
    char **map;
    int x;
    int y;
    int flor_r;
    int flor_g;
    int flor_b;
    int ceil_r;
    int ceil_g;
    int ceil_b;
} t_nc;

int ts_spaces_skip(char *str); // 1
char *ts_get_val(char *str); // 1
char *ts_get_rgb_val(char *str); // 1
t_teto *ts_key(char *lain); // 1
int ts_rgb(char *val, int *r, int *g, int *b); // 1
int ts_mt(char *lain); // 1
char *get_lain(int fd); // 1
t_teto *ts_read(int fd); // 1
int ts_check_data(t_nc *nu); // 1
void ts_free_pear(t_teto *head); // 1
int ts_opn(char *path); // 1
int dot_chk(char *path); // 1
void ts_free_one_nomap(t_nc *nu); // 1
t_nc *ts_put(t_teto *teto);  // 1
void free_nu_map(char **nu); // 1
int get_map(int fd, t_nc *nu); // 1
int rec_map(char **map); // 1
t_nc *ts_pars(char **arg); // 1
void free_nu(t_nc *nu); // 1
t_nc *ts_make_one(int fd); // 1

// ig everything is fine


#endif // HEAD_H
