/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:56:40 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/20 18:29:40 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include "../cub3d.h"

typedef struct s_drunk
{
	int					drunk;
	long				last_update;
	long				frame_delay;
	t_coordinates		deform_plane;
	double				double_vision;
	int					filter;
	double				rot;
	int					color_speed;
}						t_drunk;

typedef struct s_anim
{
	t_xpm				frame[2];
	int					frame_count;
	int					current_frame;
	long				last_update;
	long				frame_delay;
}						t_anim;

typedef struct s_sprite
{
	t_coordinates		sprite;
	t_coordinates		relative_sprite;
	double				relative_dist;
	t_coordinates		camera;
	int					sprite_screen_x;
	int					sprite_height;
	int					sprite_width;
	t_coordinates		draw_start;
	t_coordinates		draw_end;
	// t_xpm			texture;
	int					tex_x;
	int					tex_y;
	int					active;
	t_anim				anim;
}						t_sprite;

typedef struct s_global	t_global;

//ANIM_SPRITE.c
void	drink_beer(t_global *global, long current_time);
void	init_drunk(t_global *global, long current_time);
void	animation(t_global *global, t_sprite *sprite, long current_time);
void	drunk_or_not_drunk(t_global *global, long current_time);
void	init_drunk(t_global *global, long current_time);

//INIT_SPRITE.C
void	first_init_sprite(t_global *global);
void	init_sprite(t_global *global, t_sprite *sprite, int x, int y);
void	re_init_sprite(t_global *global);
void	load_textures_frames(t_global *global, t_sprite *sprite);

//SPRITE.c
void	sprite(t_global *global);
void	sprite_2(t_global *global);

//PRINT_SPRITE.c
void	sprite_what_to_draw(t_sprite *sprite);
void	sprite_in_persp(t_sprite *sprite);
int		sprite_camera_position(t_sprite *sprite, t_raycast_data *data);
void	draw_y(t_sprite *sprite, t_global *global, int x);
void	draw_sprite(t_global *global, t_sprite *sprite, t_raycast_data *data);

// DOOR.C
void	init_door(t_global *global);
void	open_the_door(t_global *global);
void	close_the_door(t_global *global);

#endif