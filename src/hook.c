/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 13:51:56 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/11 11:58:12 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_global *global)
{
	mlx_destroy_image(global->mlx, global->img.img);
    mlx_destroy_image(global->mlx, global->raycast_data.north.img_ptr);
    mlx_destroy_image(global->mlx, global->raycast_data.west.img_ptr);
    mlx_destroy_image(global->mlx, global->raycast_data.east.img_ptr);
    mlx_destroy_image(global->mlx, global->raycast_data.south.img_ptr);
	mlx_destroy_window(global->mlx, global->win);
	mlx_destroy_display(global->mlx);
	free(global->mlx);
	free_all(global);
	exit (8);
}

int	close_window_hook(void *param)
{
	t_global    *global;

	global = (t_global *)param;
	mlx_destroy_image(global->mlx, global->img.img);
    mlx_destroy_image(global->mlx, global->raycast_data.north.img_ptr);
    mlx_destroy_image(global->mlx, global->raycast_data.west.img_ptr);
    mlx_destroy_image(global->mlx, global->raycast_data.east.img_ptr);
    mlx_destroy_image(global->mlx, global->raycast_data.south.img_ptr);
	mlx_destroy_window(global->mlx, global->win);
	mlx_destroy_display(global->mlx);
	free(global->mlx);
	free_all(global);
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
    //if (global->hook.up)
   //     walk(UP, global);
    //if (global->hook.down)
    //    walk(DOWN, global);
    if (global->hook.w)
        walk(W, global);
    if (global->hook.a)
        crab_walk(A, global);
    if (global->hook.s)
        walk(S, global);
    if (global->hook.d)
        crab_walk(D, global);
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
    if (keycode == W)
        global->hook.w = 1;
    if (keycode == A)
        global->hook.a = 1;
    if (keycode == S)
        global->hook.s = 1;
    if (keycode == D)
        global->hook.d = 1;
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
    if (keycode == W)
        global->hook.w = 0;
    if (keycode == A)
        global->hook.a = 0;
    if (keycode == S)
        global->hook.s = 0;
    if (keycode == D)
        global->hook.d = 0;
    return (0);
}

