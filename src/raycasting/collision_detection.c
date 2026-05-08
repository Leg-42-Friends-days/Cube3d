/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:28:09 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/07 15:45:29 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

int	is_a_wall(t_raycast_data *data, t_map *map, double raydirx, double raydiry)
{
	double  playerxx;
	double  playeryy;

	playerxx = data->player.x + (raydirx * 0.2);
	playeryy = data->player.y + (raydiry * 0.2);
	if (playerxx >= map->width || playerxx < 0)
		return (1);
	if (playeryy >= map->height || playeryy < 0)
		return (1);
	if (map->mapou[(int)playeryy][(int)playerxx] == '1')
			return (1);
	return (0);
}

int collision_detection(t_raycast_data *data, t_map *map)
{
	int 	x;
	int		w;
	double	camerax;
	double	raydirx;
	double	raydiry;
	
	x = 0;
	w = data->screen_width;
	while(x < w)
	{
		camerax = 2 * x / (double)w - 1;
		raydirx = data->dir.x + data->plane.x * camerax;
		raydiry = data->dir.y + data->plane.y * camerax;
		if (is_a_wall(data, map, raydirx, raydiry))
			return (1);
		x ++;
	}
	return (0);
}

int	is_a_wall_back(t_raycast_data *data, t_map *map, double raydirx, double raydiry)
{
	double  playerxx;
	double  playeryy;

	playerxx = data->player.x + -(raydirx * 0.2);
	playeryy = data->player.y + -(raydiry * 0.2);
	if (playerxx >= map->width || playerxx < 0)
		return (1);
	if (playeryy >= map->height || playeryy < 0)
		return (1);
	if (map->mapou[(int)playeryy][(int)playerxx] == '1')
		return (1);
	return (0);
}

int collision_detection_back(t_raycast_data *data, t_map *map)
{
	int 	x;
	int		w;
	double	camerax;
	double	raydirx;
	double	raydiry;
	
	x = 0;
	w = data->screen_width;
	while(x < w)
	{
		camerax = 2 * x / (double)w - 1;
		raydirx = data->dir.x + data->plane.x * camerax;
		raydiry = data->dir.y + data->plane.y * camerax;
		if (is_a_wall_back(data, map, raydirx, raydiry))
			return (1);
		x ++;
	}
	return (0);
}