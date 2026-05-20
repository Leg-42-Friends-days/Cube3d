/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:56:24 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/20 17:44:26 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_in_order(t_global *global)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i < global->textures->beer)
	{
		j = i + 1;
		while (j < global->textures->beer)
		{
			if (global->sprite[i].relative_dist
				< global->sprite[j].relative_dist)
			{
				tmp = global->sprite[i];
				global->sprite[i] = global->sprite[j];
				global->sprite[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_in_order(t_global *global)
{
	int	i;

	i = 0;
	while (i < global->textures->beer)
	{
		if (sprite_camera_position(&(global->sprite[i]),
				&(global->raycast_data)) == 0)
		{
			sprite_in_persp(&(global->sprite[i]));
			sprite_what_to_draw(&(global->sprite[i]));
			draw_sprite(global, &(global->sprite[i]), &(global->raycast_data));
		}
		i++;
	}
}

double	relative_distance(t_sprite *sprite, t_raycast_data *data)
{
	double	x;
	double	y;

	x = sprite->sprite.x - data->player.x;
	y = sprite->sprite.y - data->player.y;
	return ((x * x) + (y * y));
}

void	sprite_2(t_global *global)
{
	int	i;

	i = 0;
	while (i < global->textures->beer)
	{
		global->sprite[i].relative_dist
			= relative_distance(&(global->sprite[i]), &(global->raycast_data));
		i++;
	}
	put_in_order(global);
	print_in_order(global);
}

void	sprite(t_global *global)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (i < global->textures->beer)
	{
		init_sprite(global, &(global->sprite[i]), x, y);
		x = global->sprite[i].sprite.x + 1;
		y = global->sprite[i].sprite.y;
		i++;
	}
	sprite_2(global);
}
