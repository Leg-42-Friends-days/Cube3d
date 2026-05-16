/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 13:15:06 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/16 14:50:32 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    init_door(t_global *global)
{
    load_texture(global, &(global->door.texture), global->textures->door);
}

void    open_the_door(t_global *global)
{
	double	playerxx;
	double	playeryy;

	playerxx = global->raycast_data.player.x + (global->raycast_data.dir.x * 1.8);
	playeryy = global->raycast_data.player.y + (global->raycast_data.dir.y * 1.8);
	if (playerxx >= global->map.width || playerxx < 0)
		return ;
	if (playeryy >= global->map.height || playeryy < 0)
		return ;
	if (global->map.mapou[(int)playeryy][(int)playerxx] == 'D')
		global->map.mapou[(int)playeryy][(int)playerxx] = 'O';
    refresh_image(global);
}

void    close_the_door(t_global *global)
{
    double	playerxx;
	double	playeryy;

	playerxx = global->raycast_data.player.x + (global->raycast_data.dir.x * 1.5);
	playeryy = global->raycast_data.player.y + (global->raycast_data.dir.y * 1.5);
	if (playerxx >= global->map.width || playerxx < 0)
		return ;
	if (playeryy >= global->map.height || playeryy < 0)
		return ;
	if (global->map.mapou[(int)playeryy][(int)playerxx] == 'O')
		global->map.mapou[(int)playeryy][(int)playerxx] = 'D';
    refresh_image(global);
}
