/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 13:51:56 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/07 15:23:11 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_global *global)
{
	mlx_destroy_image(global->mlx, global->img.img);
	mlx_destroy_window(global->mlx, global->win);
	mlx_destroy_display(global->mlx);
	//free(global->mlx);
	//free_map(global->map);
	exit (8);
}

int	close_window_hook(void *param)
{
	t_global    *global;

	global = (t_global *)param;
	mlx_destroy_image(global->mlx, global->img.img);
	mlx_destroy_window(global->mlx, global->win);
	mlx_destroy_display(global->mlx);
	//free(global->mlx);
	//free_map(global->map);
	exit (8);
}

int	key_hook(int keycode, void *param)
{
	t_global    *global;

	global = (t_global *)param;
	if (keycode == ESC)
		close_window(global);
	if (keycode == LEFT || keycode == RIGHT)
		rotate(keycode, global);
	if (keycode == UP || keycode == DOWN)
		walk(keycode, global);
	return (0);
}
