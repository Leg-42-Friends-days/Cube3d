/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 15:20:14 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/15 14:39:07 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	image_initiator_1(t_global *global, int x_map, int y_map)
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
			*(unsigned int *)global->img.dst = 0x00FF00;
			global->img.x++;
			x++;
		}
		global->img.y++;
		y++;
	}
	return (0);
}

int	image_initiator_p(t_global *global, int x_map, int y_map)
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
			*(unsigned int *)global->img.dst = 0x0000FF;
			global->img.x++;
			x++;
		}
		global->img.y++;
		y++;
	}
	return (0);
}

int	image_initiator_0(t_global *global, int x_map, int y_map)
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
			*(unsigned int *)global->img.dst = 0xFF0000;
			global->img.x++;
			x++;
		}
		global->img.y++;
		y++;
	}
	return (0);
}

int	show_1(t_global *global)
{
	int	row;
	int	col;
	int	x;
	int	y;

	y = 0;
	row = global->map.width;
	col = global->map.height;
	while (y < col)
	{
		x = 0;
		while (x < row)
		{
			if (global->map.fake_map[y][x] == '1')
				image_initiator_1(global, x, y);
			x++;
		}
		y++;
	}
	return (0);
}

int	show_0(t_global *global)
{
	int	row;
	int	col;
	int	x;
	int	y;

	y = 0;
	row = global->map.width;
	col = global->map.height;
	while (y < col)
	{
		x = 0;
		while (x < row)
		{
			if (global->map.fake_map[y][x] == 'x'
				|| direction_check(global->map.fake_map[y][x])
				|| global->map.fake_map[y][x] == '0')
				image_initiator_0(global, x, y);
			x++;
		}
		y++;
	}
	return (0);
}

int	dessin(t_global *global)
{
	show_1(global);
	show_0(global);
	image_initiator_p(global, global->raycast_data.player.x,
		global->raycast_data.player.y);
	mlx_put_image_to_window(global->mlx, global->win, global->img.img, 0, 0);
	return (0);
}

void	add_tile(t_global *global)
{
	global->img.tile = malloc(sizeof(t_tile));
	global->img.tile->height = (SCREEN_HEIGHT / 3) / global->map.height;
	global->img.tile->width = (SCREEN_WIDTH / 3) / global->map.width;
	global->img.x = 0;
	global->img.y = 0;
	global->img.dst = NULL;
	if (global->img.tile->height < global->img.tile->width)
		global->img.tile->width = global->img.tile->height;
	else
		global->img.tile->height = global->img.tile->width;
}