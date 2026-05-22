/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:35:44 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/22 17:11:46 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	first_init_sprite(t_global *global)
{
	if (global->textures->bonus[1] == 1)
	{
		global->sprite = malloc(sizeof(t_sprite) * global->textures->beer);
		if (!global->sprite)
		{
			free_malloc_error(global);
			write(2, "malloc error\n", 13);
			exit(1);
		}
		sprite(global);
		animation(global, global->sprite, get_time());
	}
	init_drunk(global, get_time());
}

void	load_textures_frames(t_global *global, t_sprite *sprite)
{
	if (load_texture(global, &(sprite->anim.frame[1]),
			global->textures->sprite2))
	{
		mlx_destroy_image(global->mlx, sprite->anim.frame[0].img_ptr);
		free(global->sprite);
		free_malloc_error(global);
		exit(1);
	}
	if (load_texture(global, &(sprite->anim.frame[0]),
			global->textures->sprite))
	{
		free(global->sprite);
		free_malloc_error(global);
		exit(1);
	}
}

void	init_sprite(t_global *global, t_sprite *sprite, int x, int y)
{
	char	**map;

	sprite->anim.last_update = get_time();
	sprite->anim.frame_count = 2;
	sprite->anim.frame_delay = 100;
	sprite->anim.current_frame = 0;
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

void	init_sprite_2(t_global *global, t_sprite *sprite, int x, int y)
{
	char	**map;

	sprite->anim.last_update = get_time();
	sprite->anim.frame_count = 2;
	sprite->anim.frame_delay = 100;
	sprite->anim.current_frame = 0;
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

void	re_init_sprite(t_global *global)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (i < global->textures->beer)
	{
		global->sprite[i].sprite.y = 0;
		global->sprite[i].sprite.x = 0;
		i++;
	}
	i = 0;
	while (i < global->textures->beer)
	{
		init_sprite_2(global, &(global->sprite[i]), x, y);
		x = global->sprite[i].sprite.x + 1;
		y = global->sprite[i].sprite.y;
		i++;
	}
	sprite_2(global);
}
