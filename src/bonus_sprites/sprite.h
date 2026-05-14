/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:56:40 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/14 14:43:36 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include "../cub3d.h"

typedef struct s_sprite
{
	t_coordinates	sprite;
	t_coordinates	relative_sprite;
	t_coordinates	camera;
	int				sprite_screen_x;
	int				sprite_height;
	int				sprite_width;
	t_coordinates	draw_start;
	t_coordinates	draw_end;
	t_xpm			texture;
	int				tex_x;
	int				tex_y;
}				t_sprite;

typedef struct s_global	t_global;

void	sprite(t_global *global);
void	init_sprite(t_global *global);

#endif