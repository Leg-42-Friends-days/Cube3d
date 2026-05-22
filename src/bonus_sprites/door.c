/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 13:15:06 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/22 17:11:24 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_door(t_global *global)
{
	if (global->textures->bonus[0] == 1)
	{
		if (load_texture(global, &(global->door.texture),
				global->textures->door))
		{
			mlx_destroy_image(global->mlx, global->raycast_data.north.img_ptr);
			mlx_destroy_image(global->mlx, global->raycast_data.east.img_ptr);
			mlx_destroy_image(global->mlx, global->raycast_data.west.img_ptr);
			mlx_destroy_image(global->mlx, global->raycast_data.south.img_ptr);
			free_if_error(global);
		}
	}
}

void	open_the_door(t_global *global)
{
	double	playerxx;
	double	playeryy;

	playerxx = global->raycast_data.player.x + (global->raycast_data.dir.x
			* 1.8);
	playeryy = global->raycast_data.player.y + (global->raycast_data.dir.y
			* 1.8);
	if (playerxx >= global->map.width || playerxx < 0)
		return ;
	if (playeryy >= global->map.height || playeryy < 0)
		return ;
	if (global->map.mapou[(int)playeryy][(int)playerxx])
	{
		if (global->map.mapou[(int)playeryy][(int)playerxx] == 'D')
			global->map.mapou[(int)playeryy][(int)playerxx] = 'O';
	}
	refresh_image(global);
}

void	close_the_door(t_global *global)
{
	double	playerxx;
	double	playeryy;

	playerxx = global->raycast_data.player.x + (global->raycast_data.dir.x
			* 1.5);
	playeryy = global->raycast_data.player.y + (global->raycast_data.dir.y
			* 1.5);
	if (playerxx >= global->map.width || playerxx < 0)
		return ;
	if (playeryy >= global->map.height || playeryy < 0)
		return ;
	if (global->map.mapou[(int)playeryy][(int)playerxx])
	{
		if (global->map.mapou[(int)playeryy][(int)playerxx] == 'O')
			global->map.mapou[(int)playeryy][(int)playerxx] = 'D';
	}
	refresh_image(global);
}
