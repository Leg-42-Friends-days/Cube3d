/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:20:02 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/20 18:31:24 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all_sprite(t_global *global, int j)
{
	int	i;

	i = 0;
	while (i < global->textures->beer)
	{
		mlx_destroy_image(global->mlx, global->sprite[i].anim.frame[j].img_ptr);
		i++;
	}
}

int	close_window(t_global *global)
{
	mlx_destroy_image(global->mlx, global->img.img);
	mlx_destroy_image(global->mlx, global->raycast_data.north.img_ptr);
	mlx_destroy_image(global->mlx, global->raycast_data.west.img_ptr);
	mlx_destroy_image(global->mlx, global->raycast_data.east.img_ptr);
	mlx_destroy_image(global->mlx, global->raycast_data.south.img_ptr);
	if (global->textures->bonus[2] == 1)
	{
		free_all_sprite(global, 1);
	}
	if (global->textures->bonus[1] == 1)
	{
		free_all_sprite(global, 0);
		free(global->sprite);
	}
	if (global->textures->bonus[0] == 1)
	{
		mlx_destroy_image(global->mlx, global->door.texture.img_ptr);
	}
	mlx_destroy_window(global->mlx, global->win);
	mlx_destroy_display(global->mlx);
	free(global->raycast_data.perp_wall_buffer);
	free(global->mlx);
	free_all(global);
	exit(0);
}

int	close_window_hook(void *param)
{
	t_global	*global;

	global = (t_global *)param;
	close_window(global);
	exit (0);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}
