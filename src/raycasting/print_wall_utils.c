/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wall_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 16:22:08 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/16 14:38:44 by ibrouin-         ###   ########.fr       */
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

t_xpm	which_wall(t_raycast_data *data, t_global *global)
{
	if (data->hit == 2)
		return (global->door.texture);
	if (global->map.mapou[data->mapy][data->mapx -1] == 'O' && data->side == 0)
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
	sprite(global);
	mlx_put_image_to_window(global->mlx, global->win, global->img.img, 0, 0);
}
