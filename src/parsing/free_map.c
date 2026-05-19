/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:12:56 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/19 15:16:39 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_map(t_global *global)
{
	int	i;

	i = 0;
	if (global->map.mapou)
	{
		while (global->map.mapou[i])
		{
			free(global->map.mapou[i]);
			i++;
		}
		free(global->map.mapou);
	}
	i = 0;
	if (global->map.fake_map)
	{
		while (global->map.fake_map[i])
		{
			free(global->map.fake_map[i]);
			i++;
		}
		free(global->map.fake_map);
	}
}

void	free_fake_map(t_map *map)
{
	int	i;

	if (!map || !map->fake_map)
		return ;
	i = 0;
	while (map->fake_map[i])
	{
		free(map->fake_map[i]);
		i++;
	}
	free(map->fake_map);
	map->fake_map = NULL;
}
