/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:40:44 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/01 15:52:19 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "../cub3d.h"

typedef struct s_coordinates
{
	double	x;
	double	y;
}				t_coordinates;

typedef struct s_raycast_data
{
	int				screen_height;
	double			screen_width;
	int				unit_size;
	int				player_height;
	t_coordinates	dir;
	t_coordinates	plane;
	t_coordinates	player;
	t_coordinates	ray_dir;
	int				mapx;
	int				mapy;
	t_coordinates	side_dist;
	t_coordinates	delta_dist;
	t_coordinates	step;
	double			perp_wall_dist;
	int				hit;
	int				side;
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
void    print_line(t_global *global, int draw_start, int draw_end, int x);

// WALK.c
int		rotate(int keycode, t_global *global);
int		walk(int keycode, t_global *global);

#endif