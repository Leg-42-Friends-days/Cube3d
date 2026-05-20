/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:24:18 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/20 16:24:48 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "minimap/minimap.h"
# include "parsing/parsing.h"
# include "raycasting/raycasting.h"
# include "bonus_sprites/sprite.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_tile
{
	int				width;
	int				height;
}					t_tile;

typedef struct s_hook
{
	int				left;
	int				right;
	int				up;
	int				down;
	int				w;
	int				a;
	int				s;
	int				d;
	int				e;
	int				f;
	int				t;
}					t_hook;

typedef struct s_img
{
	int				x;
	int				y;
	int				offset;
	char			*dst;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_tile			*tile;
}					t_img;

typedef struct s_global
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_textures		*textures;
	t_map			map;
	t_raycast_data	raycast_data;
	t_hook			hook;
	t_sprite		*sprite;
	t_door			door;
	t_drunk			drunk;
}					t_global;

# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 900
# define ESC 65307
# define LEFT 65361
# define RIGHT 65363
# define UP 65362
# define DOWN 65364
# define W 119
# define A 97
# define S 115
# define D 100
# define E 101
# define F 102
# define T 116
# define DRUNK_TIME 4000

void				create_map(t_map *map, char *str);
int					mouse_move(int x, int y, t_global *global);
long				get_time(void);

// HOOK.c
int					close_window(t_global *global);
int					key_hook(void *param);
int					close_window_hook(void *param);
int					press_on(int keycode, void *param);
int					press_off(int keycode, void *param);

// LOAD_TEXTURES.C
void				load_all_textures(t_global *global);
void				load_texture(t_global *global, t_xpm *tex, char *path);

#endif