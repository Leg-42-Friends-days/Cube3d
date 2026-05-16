/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:28:09 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/16 18:49:36 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	collision_detection(t_raycast_data *data, t_map *map, int direction)
{
	int		x;
	int		w;
	double	camerax;
	double	raydirx;
	double	raydiry;

	x = 0;
	w = data->screen_width;
	while (x < w)
	{
		camerax = 2 * x / (double)w - 1;
		raydirx = data->dir.x + data->plane.x * camerax;
		raydiry = data->dir.y + data->plane.y * camerax;
		if (direction == 1 && is_a_wall(data, map, raydirx, raydiry))
			return (1);
		if (direction == 2 && is_a_wall_back(data, map, raydirx, raydiry))
			return (1);
		if (direction == 3 && is_a_wall_left(data, map, raydirx, raydiry))
			return (1);
		if (direction == 4 && is_a_wall_right(data, map, raydirx, raydiry))
			return (1);
		x ++;
	}
	return (0);
}

int	is_a_wall(t_raycast_data *data, t_map *map, double rx, double ry)
{
	double	playerxx;
	double	playeryy;

	playerxx = data->player.x + (rx * 0.2);
	playeryy = data->player.y + (ry * 0.2);
	if (playerxx >= map->width || playerxx < 0)
		return (1);
	if (playeryy >= map->height || playeryy < 0)
		return (1);
	if (map->mapou[(int)playeryy][(int)playerxx] == '1')
		return (1);
	if (map->mapou[(int)playeryy][(int)playerxx] == 'D')
		return (1);
	return (0);
}

int	is_a_wall_back(t_raycast_data *data, t_map *map, double rx, double ry)
{
	double	playerxx;
	double	playeryy;

	playerxx = data->player.x + -(rx * 0.2);
	playeryy = data->player.y + -(ry * 0.2);
	if (playerxx >= map->width || playerxx < 0)
		return (1);
	if (playeryy >= map->height || playeryy < 0)
		return (1);
	if (map->mapou[(int)playeryy][(int)playerxx] == '1')
		return (1);
	return (0);
}

int	is_a_wall_left(t_raycast_data *data, t_map *map, double rx, double ry)
{
	double	playerxx;
	double	playeryy;

	playerxx = data->player.x + -(ry * 0.2);
	playeryy = data->player.y + (rx * 0.2);
	if (playerxx >= map->width || playerxx < 0)
		return (1);
	if (playeryy >= map->height || playeryy < 0)
		return (1);
	if (map->mapou[(int)playeryy][(int)playerxx] == '1')
		return (1);
	return (0);
}

int	is_a_wall_right(t_raycast_data *data, t_map *map, double rx, double ry)
{
	double	playerxx;
	double	playeryy;

	playerxx = data->player.x + (ry * 0.2);
	playeryy = data->player.y + -(rx * 0.2);
	if (playerxx >= map->width || playerxx < 0)
		return (1);
	if (playeryy >= map->height || playeryy < 0)
		return (1);
	if (map->mapou[(int)playeryy][(int)playerxx] == '1')
		return (1);
	return (0);
}
