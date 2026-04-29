/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:40:44 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/29 15:01:26 by ibrouin-         ###   ########.fr       */
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
	double			wall_dist;
	int				hit;
	int				side;
}				t_raycast_data;

typedef struct s_global	t_global;

int	raycasting(t_global *global);

//INIT_RAYCASTING.C
void	init_player(t_global *global);
void	raycast_init_data(t_raycast_data *data);
void	init_raycasting(t_raycast_data *data);

#endif