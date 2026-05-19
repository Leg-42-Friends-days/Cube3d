/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:56:40 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/19 15:35:19 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include "../cub3d.h"

typedef	struct s_drunk
{
	int				drunk;
	long			last_update;
	long			frame_delay;
	t_coordinates	deform_plane;
}			t_drunk;

typedef	struct s_anim
{
	t_xpm	frame[2];
	int		frame_count;
	int		current_frame;
	long	last_update;
	long	frame_delay;
}			t_anim;

typedef struct s_sprite
{
	t_coordinates	sprite;
	t_coordinates	relative_sprite;
	double			relative_dist;
	t_coordinates	camera;
	int				sprite_screen_x;
	int				sprite_height;
	int				sprite_width;
	t_coordinates	draw_start;
	t_coordinates	draw_end;
	//t_xpm			texture;
	int				tex_x;
	int				tex_y;
	int				active;
	t_anim			anim;
}				t_sprite;

typedef struct s_global	t_global;

void	sprite(t_global *global);
void	init_sprite(t_global *global, t_sprite *sprite, int x, int y);
void	sprite_2(t_global *global);
void    animation(t_global *global, t_sprite *sprite, long current_time);
void	drink_beer(t_global *global);
void	re_init_sprite(t_global *global);
void	drunk_or_not_drunk(t_global *global, long current_time);

// DOOR.C
void    init_door(t_global *global);
void    open_the_door(t_global *global);
void    close_the_door(t_global *global);

#endif