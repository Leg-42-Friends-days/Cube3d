/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 10:36:02 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/19 11:16:44 by ibrouin-         ###   ########.fr       */
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
