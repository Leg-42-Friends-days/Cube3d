/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 13:51:56 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/20 18:31:40 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, int y, t_global *global)
{
	static int	memo_x = SCREEN_WIDTH / 2;
	static long	fps_refresh = 0;
	int			delta_x;
	long		now;

	(void)y;
	delta_x = x - memo_x;
	if (delta_x > 0)
		right_rotation(&(global->raycast_data));
	else if (delta_x < 0)
		left_rotation(&(global->raycast_data));
	memo_x = x;
	now = get_time();
	if (now - fps_refresh >= 5000)
	{
		refresh_image(global);
		fps_refresh = now;
	}
	return (0);
}

void	key_hook(void *param)
{
	t_global	*global;

	global = (t_global *)param;
	if (global->hook.left)
		rotate(LEFT, global);
	if (global->hook.right)
		rotate(RIGHT, global);
	if (global->hook.w)
		walk(W, global);
	if (global->hook.a)
		crab_walk(A, global);
	if (global->hook.s)
		walk(S, global);
	if (global->hook.d)
		crab_walk(D, global);
	if (global->hook.e)
		open_the_door(global);
	if (global->hook.f)
		close_the_door(global);
	if (global->hook.t)
		drink_beer(global, get_time());
	if (global->drunk.drunk == 0)
		refresh_image(global);
	if (global->drunk.drunk == 1)
		refresh_drunk_image(global);
}

void	press_on_2(int keycode, t_global *global)
{
	if (keycode == F)
		global->hook.f = 1;
	if (keycode == T)
		global->hook.t = 1;
}

void	press_on(int keycode, void *param)
{
	t_global	*global;

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
	if (keycode == E)
		global->hook.e = 1;
	press_on_2(keycode, global);
}

void	press_off(int keycode, void *param)
{
	t_global	*global;

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
	if (keycode == E)
		global->hook.e = 0;
	if (keycode == F)
		global->hook.f = 0;
	if (keycode == T)
		global->hook.t = 0;
}
