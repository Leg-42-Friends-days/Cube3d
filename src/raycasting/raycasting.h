/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:40:44 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/07 14:50:34 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "../cub3d.h"

typedef	struct s_xpm
{
	void	*img_ptr;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}			t_xpm;

typedef struct s_coordinates
{
	double	x;
	double	y;
}				t_coordinates;

typedef	struct s_print
{
	int 	line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	int     tex_y;
	double  tex_pos;
    double  step;
}				t_print;

typedef struct s_raycast_data
{
	int				screen_height;
	double			screen_width;
	t_coordinates	dir;
	t_coordinates	plane;
	t_coordinates	player;
	char			dir_player;
	t_coordinates	ray_dir;
	int				mapx;
	int				mapy;
	t_coordinates	side_dist;
	t_coordinates	delta_dist;
	t_coordinates	step;
	double			perp_wall_dist;
	int				hit;
	int				side;
	t_xpm			north;
	t_xpm			west;
	t_xpm			east;
	t_xpm			south;
	t_print			print;
}				t_raycast_data;

typedef struct s_global	t_global;

// RAYCASTING.c
int		raycasting(t_global *global);
void	go_though_all_rays(t_raycast_data *data, t_map *map, t_global *global);
void	calculate_perp_wall_dist(t_raycast_data *data);

// INIT_RAYCASTING.C
void	init_player(t_global *global);
void	raycast_init_data(t_raycast_data *data);
void	init_raycasting(t_raycast_data *data);

// PRINT_WALL.c
void    print_wall(t_raycast_data *data, t_global *global, int x);
void	put_pixel(t_global *global, int x, int y, int color);
void    print_line(t_global *global, t_raycast_data *data, int x);

// WALK.c
int		rotate(int keycode, t_global *global);
int		walk(int keycode, t_global *global);

// COLLISION_DETECTION.c
int 	collision_detection(t_raycast_data *data, t_map *map);

#endif