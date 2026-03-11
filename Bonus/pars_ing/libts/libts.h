/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libts.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:12:07 by oel-mado          #+#    #+#             */
/*   Updated: 2026/03/07 23:09:52 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBTS_H
# define LIBTS_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

size_t		ts_strlen(const char *who);
size_t		ts_strlcpy(char *dst, const char *src, size_t n);
size_t		ts_strlcat(char *dst, const char *src, size_t n);

int			ts_memcmp(const void *s1, const void *s2, size_t n);
void		*ts_memset(void	*ptr, int n, size_t num);
void		ts_bzero(void *s, size_t len);
void		*ts_memcpy(void *dst, const void *src, size_t n);
void		*ts_memmove(void *dst, const void *src, size_t len);
void		*ts_memchr(const void *s, int c, size_t n);

int			ts_isalpha(int c);
int			ts_isdigit(int c);
int			ts_isalnum(int c);
int			ts_isascii(int c);
int			ts_isprint(int c);
int			ts_toupper(int c);
int			ts_tolower(int c);

int			ts_strncmp(const char *s1, const char *s2, size_t n);
char		*ts_strchr(const char *str, int c);
char		*ts_strrchr(const char *str, int c);
char		*ts_strnstr(const char *haystack, const char *needle, size_t n);

long		ts_atoi(const char *str);
char		*ts_itoa(int n);

char		*ts_strdup(const char *s1);
char		*ts_strndup(const char *s1, size_t n);
char		**ts_split(char const *s, char c);
void		*ts_calloc(size_t count, size_t size);

char		*ts_substr(char const *s, unsigned int start, size_t len);
char		*ts_strjoin(char const *s1, char const *s2);
char		*ts_strtrim(char const *s1, char const *set);
void		ts_striteri(char *s, void (*f)(unsigned int, char*));

char		*ts_strmapi(const char *s, char (*f)(unsigned int, char));

void		ts_putchar_fd(char c, int fd);
void		ts_putstr_fd(char *s, int fd);
void		ts_putendl_fd(char *s, int fd);
void		ts_putnbr_fd(int n, int fd);

int			ts_lstsize(t_list *lst);
void		ts_lstadd_front(t_list **lst, t_list *new);
void		ts_lstadd_back(t_list **lst, t_list *new);
void		ts_lstdelone(t_list *lst, void (*del)(void *));
void		ts_lstclear(t_list **lst, void (*del)(void *));
void		ts_lstiter(t_list *lst, void (*f)(void *));
t_list		*ts_lstnew(void *content);
t_list		*ts_lstlast(t_list *lst);
t_list		*ts_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// GNL

char		*gnl(int fd);

char		*rdd(char *buff, int fd);
char		*one_line(const char *buff);
char		*updtt(char *buff);

char		*gnl_strdup(const char *s1);
char		*gnl_strchr(const char *str, int c);
void		*gnl_calloc(size_t count, size_t size);
char		*gnl_strjoin(char const *s1, char const *s2);
size_t		gnl_strlen(const char *who);
size_t		gnl_strlcpy(char *dst, const char *src, size_t n);

#endif // LIBTS_H
