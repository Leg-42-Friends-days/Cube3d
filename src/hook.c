/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 13:51:56 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/08 14:24:13 by ibrouin-         ###   ########.fr       */
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

int	key_hook(void *param)
{
	t_global *global;

    global = (t_global *)param;
    if (global->hook.left)
        rotate(LEFT, global);
    if (global->hook.right)
        rotate(RIGHT, global);
    if (global->hook.up)
        walk(UP, global);
    if (global->hook.down)
        walk(DOWN, global);
    //raycasting(global);
    //mlx_put_image_to_window(global->mlx, global->win,
    //    global->img.img, 0, 0);
    return (0);
}
int press_on(int keycode, void *param)
{
    t_global *global;

    global = (t_global *)param;
    if (keycode == ESC)
        close_window(global);
    if (keycode == LEFT)
        global->hook.left = 1;
    if (keycode == RIGHT)
        global->hook.right = 1;
    if (keycode == UP)
        global->hook.up = 1;
    if (keycode == DOWN)
        global->hook.down = 1;
    return (0);
}

int press_off(int keycode, void *param)
{
    t_global *global;

    global = (t_global *)param;
    if (keycode == LEFT)
        global->hook.left = 0;
    if (keycode == RIGHT)
        global->hook.right = 0;
    if (keycode == UP)
        global->hook.up = 0;
    if (keycode == DOWN)
        global->hook.down = 0;
    return (0);
}

