/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:40:44 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/23 12:13:51 by ibrouin-         ###   ########.fr       */
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
}				t_raycast_data;

typedef struct s_global	t_global;

int	raycasting(t_global *global);

#endif