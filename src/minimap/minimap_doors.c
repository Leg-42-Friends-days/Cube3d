/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_doors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:12:19 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/19 15:09:05 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


int	image_initiator_d(t_global *global, int x_map, int y_map)
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
			*(unsigned int *)global->img.dst = 0xFFD700;
			global->img.x++;
			x++;
		}
		global->img.y++;
		y++;
	}
	return (0);
}

int	show_d(t_global *global)
{
	int	x;
	int	y;

	y = 0;
	while (global->map.mapou[y])
	{
		x = 0;
		while (global->map.mapou[y][x])
		{
			if (global->map.mapou[y][x] == 'D')
				image_initiator_d(global, x, y);
			x++;
		}
		y++;
	}
	return (0);
}
