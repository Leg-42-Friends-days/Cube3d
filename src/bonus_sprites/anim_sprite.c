/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 10:36:02 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/20 15:39:07 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    animation(t_global *global, t_sprite *sprite, long current_time)
{
	int 	i;
	t_anim	*anim;
	
	i = 0;
	while (i < global->textures->beer)
	{
		anim = &(sprite[i].anim);
		if (current_time - anim->last_update >= anim->frame_delay)
		{
			anim->current_frame ++;
			if (anim->current_frame >= anim->frame_count)
				anim->current_frame = 0;
			anim->last_update = current_time;
		}
		i++;
	}
}

void	drunk_or_not_drunk(t_global *global, long current_time)
{
	if (current_time - global->drunk.last_update >= global->drunk.frame_delay)
	{
		global->drunk.drunk = 0;
		init_drunk(global, current_time);
	}
}

void	drink_beer(t_global *global, long current_time)
{
	double	playerxx;
	double	playeryy;

	playerxx = global->raycast_data.player.x + (global->raycast_data.dir.x * 0.8);
	playeryy = global->raycast_data.player.y + (global->raycast_data.dir.y * 0.8);
	if (playerxx >= global->map.width || playerxx < 0)
		return ;
	if (playeryy >= global->map.height || playeryy < 0)
		return ;
	if (global->map.mapou[(int)playeryy][(int)playerxx])
	{
		if (global->map.mapou[(int)playeryy][(int)playerxx] == 'B')
		{
			if (global->drunk.drunk == 0)
				global->drunk.last_update = current_time;
			else
				global->drunk.frame_delay += DRUNK_TIME;
			global->drunk.rot += 0.2;
			global->drunk.color_speed += 1;
			global->drunk.drunk = 1;
			global->drunk.double_vision += 0.5;
			global->drunk.last_update = current_time;
			global->map.mapou[(int)playeryy][(int)playerxx] = '0';
			re_init_sprite(global);
		}
	}
}

void	init_drunk(t_global *global, long current_time)
{
	global->drunk.last_update = current_time;
	global->drunk.deform_plane.x = global->raycast_data.plane.x;
	global->drunk.deform_plane.y = global->raycast_data.plane.y;
	global->drunk.drunk = 0;
	global->drunk.frame_delay = DRUNK_TIME;
	global->drunk.double_vision = 0;
	global->drunk.filter = 10;
	global->drunk.rot = 0;
	global->drunk.color_speed = 0;
}

