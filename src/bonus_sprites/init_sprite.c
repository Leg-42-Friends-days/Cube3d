/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:35:44 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/18 16:04:23 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_textures_frames(t_global *global, t_sprite *sprite)
{
	int	i;

	i = 0;
	while (i < sprite->anim.frame_count)
	{
		load_texture(global, &(sprite->anim.frame[i]), global->textures->sprite);
		i++;
	}
}

void	init_sprite(t_global *global, t_sprite *sprite, int x, int y)
{
	char	**map;

	sprite->anim.frame_count = 1;
	load_textures_frames(global, sprite);
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
