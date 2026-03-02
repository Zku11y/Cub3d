/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 11:04:15 by oel-mado          #+#    #+#             */
/*   Updated: 2026/01/15 17:43:44 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libts.h"

char	*rdd(char *buff, int fd)
{
	int		i;
	char	*yup;
	char	*wait;

	yup = gnl_calloc(BUFFER_SIZE + 1, 1);
	if (!yup)
		return (free(buff), buff = NULL, NULL);
	i = 1;
	while (!gnl_strchr(yup, '\n') && i != 0)
	{
		i = read(fd, yup, BUFFER_SIZE);
		if (i == -1)
			return (free(yup), yup = NULL, NULL);
		yup[i] = '\0';
		wait = buff;
		buff = gnl_strjoin(buff, yup);
		if (!buff)
			return (free(yup), yup = NULL, free(wait), NULL);
		free(wait);
	}
	return (free(yup), yup = NULL, buff);
}

char	*one_line(const char *buff)
{
	size_t	i;
	char	*lain;

	lain = NULL;
	i = 0;
	if (!buff || buff[i] == '\0')
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\0')
		i += 1;
	else
		i += 2;
	lain = gnl_calloc(i, 1);
	if (!lain)
		return (NULL);
	gnl_strlcpy(lain, buff, i);
	return (lain);
}

char	*updtt(char *buff)
{
	size_t	i;
	size_t	j;
	char	*neo;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\0')
		return (free(buff), buff = NULL, NULL);
	j = gnl_strlen(buff + i + 1);
	if (j <= 0)
		return (free(buff), buff = NULL, NULL);
	neo = gnl_calloc(j + 1, 1);
	if (!neo)
		return (free(buff), buff = NULL, NULL);
	gnl_strlcpy(neo, buff + i + 1, j + 1);
	return (free(buff), buff = NULL, neo);
}

char	*gnl(int fd)
{
	static char	*buff[10240];
	char		*lain;
	int			i;

	i = fd;
	lain = NULL;
	if (i > 10240)
		return (NULL);
	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, buff[i], 0) == -1)
	{
		if (buff[i])
			return (free(buff[i]), buff[i] = NULL, NULL);
		return (NULL);
	}
	buff[i] = rdd(buff[i], fd);
	if (!buff[i])
		return (NULL);
	lain = one_line(buff[i]);
	if (!lain)
		return (free(buff[i]), buff[i] = NULL, NULL);
	buff[i] = updtt(buff[i]);
	return (lain); 
}

char	*gnl_strdup(const char *s1)
{
	size_t	ln;
	char	*s2;

	ln = gnl_strlen(s1) + 1;
	s2 = malloc(sizeof(char) * ln);
	if (!s2)
		return (NULL);
	gnl_strlcpy(s2, s1, ln);
	return (s2);
}
