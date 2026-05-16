/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wall_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 16:22:08 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/16 19:00:46 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	color_in_hexa(char *color)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(color);
	while (*color != ',')
		color ++;
	color ++;
	g = ft_atoi(color);
	while (*color != ',')
		color ++;
	color ++;
	b = ft_atoi(color);
	return ((r << 16) | (g << 8) | b);
}

t_xpm	wall_is_a_door(t_raycast_data *data, t_global *global)
{
	t_xpm	texture;

	if (data->hit == 2 && data->ray_dir.y >= 0 && data->side == 1)
	{
		texture = global->door.texture;
		data->print.tex_x = texture.width - 1 - data->print.tex_x;
		return (global->door.texture);
	}
	if (data->hit == 2 && data->ray_dir.y < 0 && data->side == 1)
		return (global->door.texture);
	if (data->hit == 2 && data->ray_dir.x >= 0 && data->side == 0)
	{
		texture = global->door.texture;
		data->print.tex_x = texture.width - 1 - data->print.tex_x;
		return (global->door.texture);
	}
	if (data->hit == 2 && data->ray_dir.x < 0 && data->side == 0)
	{
		return (global->door.texture);
	}
	return (global->door.texture);
}

int	check_door(t_global *global, int orientation, t_raycast_data *data)
{
	if (orientation == 1)
	{
		if (data->mapx > 0)
		{
			if (global->map.mapou[data->mapy][data->mapx -1] == 'O'
				&& data->side == 0)
				return (1);
		}
		return (0);
	}
	if (orientation == 2)
	{
		if (data->mapy + 1 < global->map.height)
		{
			if (global->map.mapou[data->mapy + 1][data->mapx] == 'O'
				&& data->side == 1)
				return (1);
		}
	}
	return (0);
}

t_xpm	which_wall(t_raycast_data *data, t_global *global)
{
	if (data->hit == 2)
		return (wall_is_a_door(data, global));
	if (check_door(global, 1, data))
		return (global->door.texture);
	if (check_door(global, 2, data))
		return (global->door.texture);
	if (data->side == 0)
	{
		if (data->ray_dir.x > 0)
			return (data->east);
		else
			return (data->west);
	}
	if (data->side == 1)
	{
		if (data->ray_dir.y < 0)
			return (data->south);
		else
			return (data->north);
	}
	return (data->north);
}

void	refresh_image(t_global *global)
{
	mlx_destroy_image(global->mlx, global->img.img);
	global->img.img = mlx_new_image(global->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	global->img.addr = mlx_get_data_addr(global->img.img,
			&global->img.bits_per_pixel, &global->img.line_length,
			&global->img.endian);
	go_though_all_rays(&(global->raycast_data), &(global->map), global);
	dessin(global);
	sprite(global);
	mlx_put_image_to_window(global->mlx, global->win, global->img.img, 0, 0);
}
