/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:16:18 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/18 17:00:25 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	add_bonus_map(t_global *global, char *str)
{
	if (ft_strncmp(str, "D", 1) == 0)
	{
		global->textures->stock[6] = 0;
		global->textures->bonus[0] = 1;
	}
	else if (ft_strncmp(str, "B", 1) == 0)
	{
		global->textures->stock[7] = 0;
		global->textures->bonus[1] = 1;
	}
	else if (ft_strncmp(str, "R", 1) == 0)
	{
		global->textures->stock[8] = 0;
		global->textures->bonus[2] = 1;
	}
}

bool		bonus_reader(t_global *global, char *map_content, char *str)
{
	int		fd;
	int		n;
	char	*line;

	n = 0;
	fd = open(map_content, O_RDONLY);
	if (fd == -1)
		return (true);
	line = get_next_line(fd);
	if (!line)
		return (true);
	while (line)
	{
		n += added_name(line, str);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (n > 1)
		return (true);
	if (n == 1)
		add_bonus_map(global, str);
	return (false);
}

bool	build_true_map(t_global *global)
{
	int	i;

	global->map.true_map = malloc(sizeof(char *) * (global->map.height + 1));
	if (!global->map.true_map)
		return (true);
	i = 0;
	while (i <= global->map.height)
	{
		global->map.true_map[i] = NULL;
		i++;
	}
	i = 0;
	while (i < global->map.height)
	{
		global->map.true_map[i] = reformat_line(global->map.mapou[i],
				global->map.width);
		if (!global->map.true_map[i])
			return (free_true_map(&global->map), true);
		i++;
	}
	return (false);
}
