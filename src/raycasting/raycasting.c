/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:41:42 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/06 10:53:42 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void	dda(t_raycast_data *data, t_map *map)
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
		/* if ((int)data->mapx < 0 || (int)data->mapx >= map->height
            || (int)data->mapy < 0 || (int)data->mapy >= map->width)
        {
            data->hit = 1;
            break ;
        } */
		if (map->mapou[data->mapy][data->mapx] == '1')
		{
			data->hit = 1;
		}
	}
}

void	calculate_perp_wall_dist(t_raycast_data *data)
{
	if (data->side == 0)
		data->perp_wall_dist = (data->mapx - data->player.x + (1 - data->step.x) / 2) / data->ray_dir.x;
	else
		data->perp_wall_dist = (data->mapy - data->player.y + (1 - data->step.y) / 2) / data->ray_dir.y;
}

void	go_though_all_rays(t_raycast_data *data, t_map *map, t_global *global)
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
		data->delta_dist.x = sqrt(1 + (data->ray_dir.y * data->ray_dir.y) / (data->ray_dir.x * data->ray_dir.x));
		data->delta_dist.y = sqrt(1 + (data->ray_dir.x * data->ray_dir.x) / (data->ray_dir.y * data->ray_dir.y));
		init_raycasting(data);
		dda(data, map);
		calculate_perp_wall_dist(data);
		print_wall(data, global, x);
		x ++;
	}
}

int	raycasting(t_global *global)
{
	init_player(global);
	raycast_init_data(&(global->raycast_data));
	go_though_all_rays(&(global->raycast_data), &(global->map), global);
	//printf("%f\n", global->raycast_data.plane.x);
	//printf("%f\n", global->raycast_data.plane.y);
	//printf("x %f\n", global->raycast_data.player.x);
	//printf("y %f\n", global->raycast_data.player.y);
	return (0);
}
