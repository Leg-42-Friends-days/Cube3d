/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:50:04 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/22 15:58:49 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_malloc_error(t_global *global)
{
	mlx_destroy_image(global->mlx, global->img.img);
	mlx_destroy_image(global->mlx, global->raycast_data.north.img_ptr);
	mlx_destroy_image(global->mlx, global->raycast_data.west.img_ptr);
	mlx_destroy_image(global->mlx, global->raycast_data.east.img_ptr);
	mlx_destroy_image(global->mlx, global->raycast_data.south.img_ptr);
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

void	mlx_cub3d_loop(t_global *global)
{
	global->win = mlx_new_window(global->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"cub_3D");
	global->img.img = mlx_new_image(global->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	global->img.addr = mlx_get_data_addr(global->img.img,
			&global->img.bits_per_pixel, &global->img.line_length,
			&global->img.endian);
	raycasting(global);
	first_init_sprite(global);
	mlx_put_image_to_window(global->mlx, global->win, global->img.img, 0, 0);
	mlx_hook(global->win, 2, 1L << 0, (int (*)())press_on, (void *)global);
	mlx_hook(global->win, 3, 1L << 1, (int (*)())press_off, (void *)global);
	mlx_hook(global->win, 17, 0, (int (*)())close_window_hook, (void *)global);
	mlx_hook(global->win, 6, 1L << 6, (int (*)())mouse_move, (void *)global);
	mlx_loop_hook(global->mlx, (int (*)())key_hook, (void *)global);
	mlx_loop(global->mlx);
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
	mlx_cub3d_loop(global);
	return (0);
}
