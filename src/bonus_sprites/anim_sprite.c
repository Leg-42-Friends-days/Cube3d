/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 10:36:02 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/19 18:42:00 by ibrouin-         ###   ########.fr       */
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
		global->drunk.last_update = current_time;
		printf("c'est fini\n");
		//global->drunk.deform_plane.x = global->raycast_data.plane.x;
		//global->drunk.deform_plane.y = global->raycast_data.plane.y;
		global->drunk.drunk = 0;
	}
}

void	drink_beer(t_global *global)
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
			printf("j'ai bu \n");
			//global->drunk.deform_plane.x = global->raycast_data.plane.x;
			//global->drunk.deform_plane.y = global->raycast_data.plane.y;
			change_fov(global);
			global->drunk.drunk = 1;
			global->map.mapou[(int)playeryy][(int)playerxx] = '0';
			re_init_sprite(global);
		}
	}
	refresh_image(global);
}
