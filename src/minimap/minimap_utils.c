/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:48:16 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/15 15:04:40 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	dessin(t_global *global)
{
	show_1(global);
	show_0(global);
	image_initiator_p(global, global->raycast_data.player.x,
		global->raycast_data.player.y);
	mlx_put_image_to_window(global->mlx, global->win, global->img.img, 0, 0);
	return (0);
}

void	add_tile(t_global *global)
{
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
}
