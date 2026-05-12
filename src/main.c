/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:50:04 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/12 11:45:17 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	image_initiator_1(t_global *global, int x_map, int y_map)
{
	int	x;
	int	y;

	y = 0;
	global->img.y = y_map * global->img.tile->height;
	while (y < global->img.tile->height)
	{
		global->img.x = x_map * global->img.tile->width;
		x = 0;
		while (x < global->img.tile->width)
		{
			global->img.offset = (global->img.y * global->img.line_length
					+ global->img.x * (global->img.bits_per_pixel / 8));
			global->img.dst = global->img.addr + global->img.offset;
			*(unsigned int *)global->img.dst = 0x00FF00;
			global->img.x++;
			x++;
		}
		global->img.y++;
		y++;
	}
	mlx_put_image_to_window(global->mlx, global->win, global->img.img, 0, 0);
	return (0);
}

int	show_1(t_global *global)
{
	int	row;
	int	col;
	int	x;
	int	y;

	y = 0;
	row = global->map.width;
	col = global->map.height;
	while (y < col)
	{
		x = 0;
		while (x < row)
		{
			if (global->map.mapou[y][x] == '1')
				image_initiator_1(global, x, y);
			x++;
		}
		y++;
	}
	return (0);
}

int	dessin(t_global *global)
{
	show_1(global);
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
	printf("%d\n", global->map.height);
	printf("%d\n", global->map.width);
	global->img.tile = malloc(sizeof(t_tile));
	global->img.tile->height = (SCREEN_HEIGHT / 3) / global->map.height;
	global->img.tile->width = (SCREEN_WIDTH / 3) / global->map.width;
	global->img.x = 0;
	global->img.y = 0;
	global->img.dst = NULL;
	if (global->img.tile->height < global->img.tile->width)
		global->img.tile->width = global->img.tile->height;
	else
		global->img.tile->height = global->img.tile->width;
	global->mlx = mlx_init();
	if (!global->mlx)
		exit(1);
	load_all_textures(global);
	global->win = mlx_new_window(global->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "42");
	global->img.img = mlx_new_image(global->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	global->img.addr = mlx_get_data_addr(global->img.img, &global->img.bits_per_pixel,
			&global->img.line_length, &global->img.endian);
	raycasting(global);
	dessin(global);
	mlx_put_image_to_window(global->mlx, global->win, global->img.img, 0, 0);
	mlx_hook(global->win, 2, 1L << 0, (int (*)())press_on, (void *)global);
	mlx_hook(global->win, 3, 1L << 1, (int (*)())press_off, (void *)global);
	mlx_hook(global->win, 17, 0, (int (*)())close_window_hook, (void *)global);
	mlx_loop_hook(global->mlx, (int (*)())key_hook, (void *)global);
	// mlx_key_hook(global->win, key_hook, (void *)global);
	//mlx_hook(global->win, 17, 0, (int (*)())close_window_hook, (void *)global);
	mlx_loop(global->mlx);
	free_all(global);
	return (0);
}
