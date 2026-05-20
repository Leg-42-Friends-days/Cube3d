/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:50:04 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/20 14:59:13 by mickzhan         ###   ########.fr       */
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

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

int	main(int ac, char **av)
{
	t_global	*global;

	if (error_gestion(ac, av) == 1)
		return (1);
	global = init_malloc();
	read_map(global, av[1]);
	if (start_map(global, av[1]) == 1)
		return (free_all(global), 1);
	add_tile(global);
	global->mlx = mlx_init();
	if (!global->mlx)
		exit(1);
	load_all_textures(global);
	init_door(global);
	global->win = mlx_new_window(global->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"42");
	global->img.img = mlx_new_image(global->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	global->img.addr = mlx_get_data_addr(global->img.img,
			&global->img.bits_per_pixel, &global->img.line_length,
			&global->img.endian);
	raycasting(global);
	if (global->textures->beer > 0)
	{
		global->sprite = malloc(sizeof(t_sprite) * global->textures->beer);
		sprite(global);
		animation(global, global->sprite, get_time());
	}
	global->drunk.drunk = 0;
	global->drunk.frame_delay = 50000;
	// mlx_mouse_hide(global->mlx, global->win);
	mlx_put_image_to_window(global->mlx, global->win, global->img.img, 0, 0);
	mlx_hook(global->win, 2, 1L << 0, (int (*)())press_on, (void *)global);
	mlx_hook(global->win, 3, 1L << 1, (int (*)())press_off, (void *)global);
	mlx_hook(global->win, 17, 0, (int (*)())close_window_hook, (void *)global);
	mlx_hook(global->win, 6, 1L << 6, (int (*)())mouse_move, (void *)global);
	mlx_loop_hook(global->mlx, (int (*)())key_hook, (void *)global);
	// mlx_key_hook(global->win, key_hook, (void *)global);
	// mlx_hook(global->win, 17, 0, (int (*)())close_window_hook,
	// (void *)global);
	mlx_loop(global->mlx);
	free_all(global);
	return (0);
}
