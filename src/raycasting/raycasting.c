/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:41:42 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/23 19:06:33 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void	go_though_all_rays(t_raycast_data *data)
{
	int 	x;
	int		w;
	double	camerax;

	x = 0;
	w = data->screen_width;
	while(x < w)
	{
		camerax = 2 * x / (double)w - 1;
		printf("%d : camera x = %f      ", x, camerax);
		data->ray_dir.x = data->dir.x + data->plane.x * camerax;
		data->ray_dir.y = data->dir.y + data->plane.y * camerax;
		printf("x = %f et y = %f\n", data->ray_dir.x, data->ray_dir.y);
		x ++;
	}
	data->delta_dist.x = sqrt(1 + (data->ray_dir.y * data->ray_dir.y) / (data->ray_dir.x * data->ray_dir.x))
	data->delta_dist.y = sqrt(1 + (data->ray_dir.x * data->ray_dir.x) / (data->ray_dir.y * data->ray_dir.y))
}

int	raycasting(t_global *global)
{
	raycast_init_data(&(global->raycast_data));
	init_player(global);
	go_though_all_rays(&(global->raycast_data));
	//printf("%f\n", global->raycast_data.plane.x);
	//printf("%f\n", global->raycast_data.plane.y);
	return (0);
}
