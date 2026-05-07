/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:50:04 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/07 16:28:14 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// int	image_initiator_1(t_global *global, int x_map, int y_map)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	global->map.game->y = y_map * global->map.tile->height;
// 	while (y < global->map.tile->height)
// 	{
// 		global->map.game->x = x_map * global->map.tile->width;
// 		x = 0;
// 		while (x < global->map.tile->width)
// 		{
// 			global->map.game->offset = (global->map.game->y * global->map.game->line_length
// 					+ global->map.game->x * (global->map.game->bits_per_pixel / 8));
// 			global->map.game->dst = global->map.game->addr + global->map.game->offset;
// 			*(unsigned int *)global->map.game->dst = 0x440E03;
// 			global->map.game->x++;
// 			x++;
// 		}
// 		global->map.game->y++;
// 		y++;
// 	}
// 	mlx_put_image_to_window(global->mlx, global->win, global->img.img, 0, 0);
// 	return (0);
// }

// int	show_1(t_global *global)
// {
// 	int	row;
// 	int	col;
// 	int	x;
// 	int	y;

// 	y = 0;
// 	row = global->map.width;
// 	col = global->map.height;
// 	while (y < col)
// 	{
// 		x = 0;
// 		while (x < row)
// 		{
// 			if (global->map.mapou[y][x] == '1')
// 				image_initiator_1(global, x, y);
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (0);
// }

// int	dessin(t_global *global)
// {
// 	show_1(global);
// 	return (0);
// }

int	main(int ac, char **av)
{
	t_global	*global;
	
	if (error_gestion(ac, av) == 1)
		return (1);
	global = init_malloc();
	read_map(global, av[1]);
	if (start_map(global, av[1]) == 1)
		return (free_all(global), 1);
	// global->map.mini_x = SCREEN_WIDTH / 10;
	// global->map.mini_y = SCREEN_HEIGHT / 10;
	// printf("HERE mini_x : %d\n", global->map.mini_x);
	// printf("HERE mini_y : %d\n", global->map.mini_y);
	// global->map.tile->width = global->map.mini_x / global->map.width;
	// global->map.tile->height = global->map.mini_y / global->map.height;
	// if (global->map.tile->height < global->map.tile->width)
	// 	global->map.tile->width = global->map.tile->height;
	// else
	// 	global->map.tile->height = global->map.tile->width;
	// printf("HERE WIDTH: %d\n", global->map.tile->width);
	// printf("HERE HEIGHT: %d\n", global->map.tile->height);
	// global->map.game->x = 0;
	// global->map.game->y = 0;
	// global->map.game->dst = NULL;
	global->mlx = mlx_init();
	if (!global->mlx)
		exit(1);
	load_all_textures(global);
	global->win = mlx_new_window(global->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "42");
	global->img.img = mlx_new_image(global->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	global->img.addr = mlx_get_data_addr(global->img.img, &global->img.bits_per_pixel,
			&global->img.line_length, &global->img.endian);
	raycasting(global);
	// dessin(global);
	mlx_put_image_to_window(global->mlx, global->win, global->img.img, 0, 0);
	mlx_key_hook(global->win, key_hook, (void *)global);
	//mlx_hook(global->win, 17, 0, (int (*)())close_window_hook, (void *)global);
	mlx_loop(global->mlx);
	free_all(global);
	return (0);
}
