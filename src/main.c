/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:50:04 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/02 15:20:39 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_global	*global;
	
	if (error_gestion(ac, av) == 1)
		return (1);
	global = init_malloc();
	read_map(global, av[1]);
	if (start_map(global, av[1]) == 1)
		return (free_all(global), 1);
	global->mlx = mlx_init();
	if (!global->mlx)
		exit(1);
	global->win = mlx_new_window(global->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "42");
	global->img.img = mlx_new_image(global->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	global->img.addr = mlx_get_data_addr(global->img.img, &global->img.bits_per_pixel,
			&global->img.line_length, &global->img.endian);
	raycasting(global);
	mlx_put_image_to_window(global->mlx, global->win, global->img.img, 0, 0);
	mlx_key_hook(global->win, key_hook, (void *)global);
	//mlx_hook(global->win, 17, 0, (int (*)())close_window_hook, (void *)global);
	mlx_loop(global->mlx);
	free_all(global);
	return (0);
}
