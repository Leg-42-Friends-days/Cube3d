/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:20:18 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/23 15:20:37 by ibrouin-         ###   ########.fr       */
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
	map = global->map.mapy;
	while(map[i][j] != '\n')
	{
		while (map[i][j] != '\n')
		{
			if (map[i][j] == '0')
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
}

void	raycast_init_data(t_raycast_data *data)
{
	data->screen_height = 480;
	data->screen_width = 640;
	data->unit_size = 64;
	data->player_height = 32;
	data->dir.x = -1;
	data->dir.y = 0;
	data->plane.x = 0;
	data->plane.y = 0.66;
}
