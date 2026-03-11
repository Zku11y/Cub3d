/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lerp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:14:44 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/08 14:14:45 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

uint8_t	ft_lerp_pixels(uint8_t new, uint8_t old, double lerp_rate)
{
	return ((new * lerp_rate) + (old * (1.0 - lerp_rate)));
}

double	ft_lerp_speed(double dst, double current)
{
	return ((dst * SPEED_LERP) + (current * (1.0 - SPEED_LERP)));
}

double	ft_lerp_tilt(double dst, double current)
{
	return ((dst * TILT_LERP) + (current * (1.0 - TILT_LERP)));
}

double	ft_lerp_fov(double dst, double current, double lerp_rate)
{
	return ((dst * lerp_rate) + (current * (1.0 - lerp_rate)));
}

double	ft_lerp_move(double dst, double current, double lerp_rate)
{
	return ((current * lerp_rate) + (dst * (1.0 - lerp_rate)));
}
