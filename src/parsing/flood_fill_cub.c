/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_cub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:08:12 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/15 15:08:47 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*reformat_line(char *line, int width)
{
	char	*ref;
	int		j;

	ref = malloc(sizeof(char) * (width + 1));
	if (!ref)
		return (NULL);
	j = 0;
	while (j < width)
	{
		ref[j] = ' ';
		j++;
	}
	j = 0;
	while (line[j] && line[j] != '\n' && j < width)
	{
		ref[j] = line[j];
		j++;
	}
	ref[width] = '\0';
	return (ref);
}

bool	build_fake_map(t_global *global)
{
	int	i;

	if (!global->map.mapou)
		return (true);
	global->map.fake_map = malloc(sizeof(char *) * (global->map.height + 1));
	if (!global->map.fake_map)
		return (true);
	i = 0;
	while (i <= global->map.height)
	{
		global->map.fake_map[i] = NULL;
		i++;
	}
	i = 0;
	while (i < global->map.height)
	{
		global->map.fake_map[i] = reformat_line(global->map.mapou[i],
				global->map.width);
		if (!global->map.fake_map[i])
			return (free_fake_map(&global->map), true);
		i++;
	}
	return (false);
}

void	flood_fill(t_global *global, int x, int y)
{
	if (x < 0 || y < 0 || x >= global->map.width || y >= global->map.height)
	{
		global->map.wopen = 1;
		return ;
	}
	if (global->map.fake_map[y][x] == ' ')
	{
		global->map.wopen = 1;
		return ;
	}
	if (global->map.fake_map[y][x] == 'x' || global->map.fake_map[y][x] == '1')
		return ;
	global->map.fake_map[y][x] = 'x';
	flood_fill(global, x - 1, y);
	flood_fill(global, x + 1, y);
	flood_fill(global, x, y - 1);
	flood_fill(global, x, y + 1);
}

int	map_flood(t_global *global)
{
	int	x;
	int	y;
	int	found;

	found = 0;
	y = 0;
	while (y < global->map.height)
	{
		x = 0;
		while (x < global->map.width)
		{
			if (direction_check(global->map.fake_map[y][x]))
			{
				found = 1;
				flood_fill(global, x, y);
				return (global->map.wopen);
			}
			x++;
		}
		y++;
	}
	if (!found)
		return (1);
	return (global->map.wopen);
}
