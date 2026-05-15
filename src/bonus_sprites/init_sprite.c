/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:35:44 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/15 14:51:29 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_sprite(t_global *global, t_sprite *sprite, int x, int y)
{
	char	**map;

	load_texture(global, &(sprite->texture), global->textures->sprite);
	map = global->map.mapou;
	while (y < global->map.height)
	{
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'B')
			{
				sprite->sprite.y = y + 0.5;
				sprite->sprite.x = x + 0.5;
				return ;
			}
			x++;
		}
		x = 0;
		y++;
	}
}
