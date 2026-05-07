/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:28:09 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/07 15:11:19 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

int	is_a_wall(t_raycast_data *data, t_map *map)
{
	double  playerxx;
	double  playeryy;

	playerxx = data->player.x + (data->ray_dir.x * 0.2);
	playeryy = data->player.y + (data->ray_dir.y * 0.2);
	if (playerxx >= map->width)
		return (1);
	if (playeryy >= map->height)
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
	
	x = 0;
	w = data->screen_width;
	while(x < w)
	{
		camerax = 2 * x / (double)w - 1;
		data->ray_dir.x = data->dir.x + data->plane.x * camerax;
		data->ray_dir.y = data->dir.y + data->plane.y * camerax;
		data->delta_dist.x = sqrt(1 + (data->ray_dir.y * data->ray_dir.y)
			/ (data->ray_dir.x * data->ray_dir.x));
		data->delta_dist.y = sqrt(1 + (data->ray_dir.x * data->ray_dir.x)
			/ (data->ray_dir.y * data->ray_dir.y));
		if (is_a_wall(data, map))
			return (1);
		x ++;
	}
	return (0);
}