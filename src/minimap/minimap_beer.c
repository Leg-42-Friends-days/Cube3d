/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_beer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:22:31 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/19 18:24:21 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	image_initiator_b(t_global *global, int x_map, int y_map)
{
	int	x;
	int	y;

	y = 0;
	global->img.y = y_map * global->img.tile->height;
	while (y < global->img.tile->height)
	{
		global->img.x = x_map * global->img.tile->width;
		x = 0;
		while (x < global->img.tile->width)
		{
			global->img.offset = (global->img.y * global->img.line_length
					+ global->img.x * (global->img.bits_per_pixel / 8));
			global->img.dst = global->img.addr + global->img.offset;
			*(unsigned int *)global->img.dst = 0x0F3D2E;
			global->img.x++;
			x++;
		}
		global->img.y++;
		y++;
	}
	return (0);
}

int	show_b(t_global *global)
{
	int	x;
	int	y;

	y = 0;
	while (global->map.mapou[y])
	{
		x = 0;
		while (global->map.mapou[y][x])
		{
			if (global->map.mapou[y][x] == 'B')
				image_initiator_b(global, x, y);
			x++;
		}
		y++;
	}
	return (0);
}
