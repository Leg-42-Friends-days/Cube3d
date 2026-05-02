/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:20:18 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/02 17:33:29 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void	init_player(t_global *global)
{
	char	**map;
	int	i;
	int	j;

	i = 0;
	j = 0;
	map = global->map.mapou;
	while(i < global->map.height)
	{
		while (j < global->map.width)
		{
			if (map[i][j] == 'N')
			{
				global->raycast_data.player.y = i + 0.5;
				global->raycast_data.player.x = j + 0.5;
				return ;
			}
			j++;
		}
		j = 0;
		i++;
	}
	global->raycast_data.mapx = global->raycast_data.player.x;
	global->raycast_data.mapy = global->raycast_data.player.y;
}

void	raycast_init_data(t_raycast_data *data)
{
	data->screen_height = SCREEN_HEIGHT;
	data->screen_width = SCREEN_WIDTH;
	data->unit_size = 64;
	data->player_height = 32;
	data->dir.x = -1;
	data->dir.y = 0;
	data->plane.x = 0;
	data->plane.y = 0.66;
	data->hit = 0;
}

void	init_raycasting(t_raycast_data *data)
{
	data->mapx = data->player.x;
	data->mapy = data->player.y;
	data->hit = 0;
	if (data->ray_dir.x < 0)
	{
		data->step.x = -1;
		data->side_dist.x = (data->player.x - data->mapx) * data->delta_dist.x;
	}
	else
	{
		data->step.x = 1;
		data->side_dist.x = (data->mapx + 1 - data->player.x) * data->delta_dist.x;
	}
	if (data->ray_dir.y < 0)
	{
		data->step.y = -1;
		data->side_dist.y = (data->player.y - data->mapy) * data->delta_dist.y;
	}
	else
	{
		data->step.y = 1;
		data->side_dist.y = (data->mapy + 1 - data->player.y) * data->delta_dist.y;
	}
}
