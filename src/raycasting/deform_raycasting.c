/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deform_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:41:42 by ibrouin-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/05/19 15:32:30 by ibrouin-         ###   ########.fr       */
=======
/*   Updated: 2026/05/19 14:59:45 by mickzhan         ###   ########.fr       */
>>>>>>> refs/remotes/origin/main
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	deform_dda(t_raycast_data *data, t_map *map)
{
	while (data->hit == 0)
	{
		if (data->side_dist.x < data->side_dist.y)
		{
			data->side_dist.x += data->delta_dist.x;
			data->mapx += data->step.x;
			data->side = 0;
		}
		else
		{
			data->side_dist.y += data->delta_dist.y;
			data->mapy += data->step.y;
			data->side = 1;
		}
		if (map->mapou[data->mapy][data->mapx] == '1')
		{
			data->hit = 1;
		}
		if (map->mapou[data->mapy][data->mapx] == 'D')
		{
			data->hit = 2;
		}
	}
}

void	calculate_deform_wall_dist(t_raycast_data *data)
{
	if (data->side == 0)
		data->perp_wall_dist = data->side_dist.x - data->delta_dist.x;
	else
		data->perp_wall_dist = data->side_dist.y - data->delta_dist.y;
}

void	change_fov(t_global *global)
{
	global->drunk.deform_plane.x = global->drunk.deform_plane.x * 1.3;
	global->drunk.deform_plane.y = global->drunk.deform_plane.y * 1.3;
}

void	deform_rays(t_raycast_data *data, t_map *map, t_global *global)
{
	int		x;
	int		w;
	double	camerax;

	x = 0;
	w = data->screen_width;
	global->drunk.deform_plane.x = data->plane.x;
	global->drunk.deform_plane.y = data->plane.y;
	change_fov(global);
	while (x < w)
	{
		camerax = 2 * x / (double)w - 1;
<<<<<<< HEAD
		data->ray_dir.x = data->dir.x + global->drunk.deform_plane.x * camerax;
		data->ray_dir.y = data->dir.y + global->drunk.deform_plane.y * camerax;
=======
		data->ray_dir.x = data->dir.x + data->plane.x * camerax;
		data->ray_dir.y = data->dir.y + data->plane.y * camerax;
>>>>>>> refs/remotes/origin/main
		data->delta_dist.x = sqrt(1 + (data->ray_dir.y * data->ray_dir.y)
				/ (data->ray_dir.x * data->ray_dir.x));
		data->delta_dist.y = sqrt(1 + (data->ray_dir.x * data->ray_dir.x)
				/ (data->ray_dir.y * data->ray_dir.y));
		init_raycasting(data);
		deform_dda(data, map);
		calculate_deform_wall_dist(data);
		data->perp_wall_buffer[x] = data->perp_wall_dist;
		print_wall(data, global, x);
		x ++;
	}
}

/* int	raycasting(t_global *global)
{
	init_player(global);
	raycast_init_data(&(global->raycast_data));
	go_though_all_rays(&(global->raycast_data), &(global->map), global);
	return (0);
} */
