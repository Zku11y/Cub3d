/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 17:46:53 by oel-mado          #+#    #+#             */
/*   Updated: 2026/03/08 20:06:29 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# include "libts/libts.h"

typedef enum e_key
{
	WA,
	FL,
	CI,
	PR,
	EN
}	t_key;

typedef struct s_elv
{
	int			x;
	int			y;
	char		who;
	char		door;
}				t_elv;

typedef struct s_mp
{
	char			*val;
	struct s_mp		*next;
}					t_mp;

typedef struct s_teto
{
	char			*val;
	struct s_teto	*next;
	t_key			key;
}					t_teto;

typedef struct s_nc
{
	char			*imgs[5];
	// mlx_texture_t	*txtrs[5];
	struct s_nc		*next;
	char			**map;
	t_elv			*start;
	t_elv			*end;
	int				x;
	int				y;
}					t_nc;

int			ts_spaces_skip(char *str);
char		*ts_get_val(char *str);
t_teto		*ts_key(char *lain);
int			ts_mt(char *lain);
char		*get_lain(int fd);
t_teto		*ts_read(int fd);
int			ts_check_data(t_nc *nu);
void		ts_free_pear(t_teto *head);
int			ts_opn(char *path);
int			dot_chk(char *path);
void		ts_free_one_nomap(t_nc *nu);
t_nc		*ts_put(t_teto *teto); 
void		free_nu_map(char **nu);
int			get_map(int fd, t_nc *nu);
int			rec_map(char **map, t_nc *nu);
t_nc		*ts_pars(char **arg);
void		free_nu(t_nc *nu);
t_nc		*ts_make_one(int fd);
void		free_mp(t_mp *mp);
void		map_cln(char **map, int x, int y, t_elv *hi);
void		put_door(char **map, t_elv *hi);
int			ts_check_door(char **map, int x, int y);
int			ts_check_elv(char **map);
int			get_path(char **map, t_elv *elv, int *m_s);
t_elv		*get_elv(char **map, char who);
int			chk_elv(char **map);
int			get_door(char **map, t_elv *hi);

#endif // HEAD_H
