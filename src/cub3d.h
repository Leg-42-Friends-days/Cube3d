/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:24:18 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/01 14:09:34 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "parsing/parsing.h"
# include "raycasting/raycasting.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_global
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_textures		*textures;
	t_map			map;
	t_raycast_data	raycast_data;
}				t_global;

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define ESC 65307
# define LEFT 65361
# define RIGHT 65363
# define UP 65362
# define DOWN 65364

void    create_map(t_map *map, char *str);

// HOOK.c
int	close_window(t_global *global);
int	key_hook(int keycode, void *param);
int	close_window_hook(void *param);

#endif