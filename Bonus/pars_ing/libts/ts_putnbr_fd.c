/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:42:18 by oel-mado          #+#    #+#             */
/*   Updated: 2026/01/15 05:07:51 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libts.h"

void	ts_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ts_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n <= 0)
	{
		if (n == 0)
		{
			ts_putchar_fd('0', fd);
			return ;
		}
		ts_putchar_fd('-', fd);
		ts_putnbr_fd(-n, fd);
	}
	if (n >= 10)
	{
		ts_putnbr_fd(n / 10, fd);
		ts_putnbr_fd(n % 10, fd);
	}
	else if (n >= 0 && n <= 9)
		ts_putchar_fd(n + '0', fd);
}
