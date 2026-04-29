/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:41:42 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/29 15:39:14 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void	dda(t_raycast_data *data, t_map *map)
{
	printf("side_dist x = %f et side_dist y = %f\n", data->side_dist.x, data->side_dist.y);
	while (data->hit == 0)
	{
		if (data->side_dist.x < data->side_dist.y)
		{
			data->side_dist.x += data->delta_dist.x;
			data->mapx += data->step.x;
			data->side = 0;
			//printf("data->side_dist.x %f\n", data->side_dist.x);
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
			//printf("hihi\n");
			data->hit = 1;
		}
	}
}

void	go_though_all_rays(t_raycast_data *data, t_map *map)
{
	int 	x;
	int		w;
	double	camerax;

	(void)map;
	x = 0;
	w = data->screen_width;
	while(x < w)
	{
		camerax = 2 * x / (double)w - 1;
		//printf("%d : camera x = %f      ", x, camerax);
		data->ray_dir.x = data->dir.x + data->plane.x * camerax;
		data->ray_dir.y = data->dir.y + data->plane.y * camerax;
		printf("raydir x = %f et raydir y = %f\n", data->ray_dir.x, data->ray_dir.y);
		data->delta_dist.x = sqrt(1 + (data->ray_dir.y * data->ray_dir.y) / (data->ray_dir.x * data->ray_dir.x));
		data->delta_dist.y = sqrt(1 + (data->ray_dir.x * data->ray_dir.x) / (data->ray_dir.y * data->ray_dir.y));
		//printf("delta dist x = %f et delta dist y = %f\n", data->delta_dist.x, data->delta_dist.y);
		init_raycasting(data);
		//printf("x = %d et y = %d\n", data->mapx, data->mapy);
		dda(data, map);
		printf("x = %d et y = %d\n", data->mapx, data->mapy);
		x ++;
		//if (x > 5)
		//	break;
	}
}

int	raycasting(t_global *global)
{
	raycast_init_data(&(global->raycast_data));
	init_player(global);
	go_though_all_rays(&(global->raycast_data), &(global->map));
	//printf("%f\n", global->raycast_data.plane.x);
	//printf("%f\n", global->raycast_data.plane.y);
	//printf("x %f\n", global->raycast_data.player.x);
	//printf("y %f\n", global->raycast_data.player.y);
	return (0);
}
