/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:50:04 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/18 16:50:40 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, int y, t_global *global)
{
	static int	memo_x = SCREEN_WIDTH / 2;
	int			delta_x;

	(void)y;
	(void) global;
	delta_x = x - memo_x;
	if (delta_x > 0)
		right_rotation(&(global->raycast_data));
	else if (delta_x < 0)
		left_rotation(&(global->raycast_data));
	memo_x = x;
	refresh_image(global);
	mlx_put_image_to_window(global->mlx, global->win, global->img.img, 0, 0);
	return (0);
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
	dessin(global);
	if (global->textures->beer > 0)
	{
		global->sprite = malloc(sizeof(t_sprite) * global->textures->beer);
		sprite(global);
	}
	mlx_put_image_to_window(global->mlx, global->win, global->img.img, 0, 0);
	mlx_hook(global->win, 2, 1L << 0, (int (*)())press_on, (void *)global);
	mlx_hook(global->win, 3, 1L << 1, (int (*)())press_off, (void *)global);
	mlx_hook(global->win, 17, 0, (int (*)())close_window_hook, (void *)global);
	mlx_hook(global->win, 6, 1L << 6, (int (*)())mouse_move, (void *)global);
	mlx_loop_hook(	global->mlx, (int (*)())key_hook, (void *)global);
	// mlx_key_hook(global->win, key_hook, (void *)global);
	// mlx_hook(global->win, 17, 0, (int (*)())close_window_hook,
	// (void *)global);
	mlx_loop(global->mlx);
	free_all(global);
	return (0);
}
