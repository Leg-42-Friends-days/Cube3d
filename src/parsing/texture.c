/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:08:53 by mickzhan          #+#    #+#             */
/*   Updated: 2026/04/24 15:24:30 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	convert_line3(t_global *global, char *line)
{
	if (ft_strncmp(is_space(line), "F", 1) == 0)
	{
		if (global->textures->stock[4] == 1)
			return (printf("Error\nTo much F"), exit(1));
		global->textures->stock[4] = 1;
		global->textures->floor = rgb_map(is_space(line) + 1);
		global->textures->start++;
	}
	else if (ft_strncmp(is_space(line), "C", 1) == 0)
	{
		if (global->textures->stock[5] == 1)
			return (printf("Error\nTo much C"), exit(1));
		global->textures->ceiling = rgb_map(is_space(line) + 1);
		global->textures->stock[5] = 1;
		global->textures->start++;
	}
	else
	{
		if (line_check(line))
			return (printf("Error\nMap invalid\n"), exit(1));
		if (nothing_slash(line) == 1)
			global->textures->end++;
		else
			global->textures->start++;
	}
}

void	convert_line2(t_global *global, char *line)
{
	if (ft_strncmp(is_space(line), "SO", 2) == 0)
	{
		if (global->textures->stock[2] == 1)
			return (printf("Error\nTo much SO"), exit(1));
		global->textures->stock[2] = 1;
		global->textures->south = texture_map(is_space(line) + 2);
		global->textures->start++;
	}
	else if (ft_strncmp(is_space(line), "EA", 2) == 0)
	{
		if (global->textures->stock[3] == 1)
			return (printf("Error\nTo much EA"), exit(1));
		global->textures->east = texture_map(is_space(line) + 2);
		global->textures->stock[3] = 1;
		global->textures->start++;
	}
	else
		convert_line3(global, line);
}

void	convert_line(t_global *global, char *line)
{
	if (stock_checker(global) == 1 && global->textures->end == 1)
		return ;
	if (ft_strncmp(is_space(line), "NO", 2) == 0)
	{
		if (global->textures->stock[0] == 1)
			return (printf("Error\nTo much NO\n"), exit(1));
		global->textures->stock[0] = 1;
		global->textures->north = texture_map(is_space(line) + 2);
		global->textures->start++;
	}
	else if (ft_strncmp(is_space(line), "WE", 2) == 0)
	{
		if (global->textures->stock[1] == 1)
			return (printf("Error\nTo much WE"), exit(1));
		global->textures->stock[1] = 1;
		global->textures->west = texture_map(is_space(line) + 2);
		global->textures->start++;
	}
	else
		convert_line2(global, line);
}

void	initiate_stock(t_global *global)
{
	global->textures->stock[0] = 0;
	global->textures->stock[1] = 0;
	global->textures->stock[2] = 0;
	global->textures->stock[3] = 0;
	global->textures->stock[4] = 0;
	global->textures->stock[5] = 0;
}

void	read_map(t_global *global, char *map_content)
{
	int		fd;
	char	*line;

	global->textures->start = 0;
	global->textures->end = 0;
	initiate_stock(global);
	fd = open(map_content, O_RDONLY);
	if (!fd)
		return (printf("Error\n"), exit(1));
	line = get_next_line(fd);
	while (line)
	{
		convert_line(global, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	// printf("CEILING :%s\n", global->textures->ceiling);
	// printf("FLOOR : %s\n", global->textures->floor);
	// printf("START POINT : %d\n", global->textures->start);
	// printf("NORTH : %s\n", global->textures->north);
	// printf("SOUTH : %s\n", global->textures->south);
	// printf("EAST : %s\n", global->textures->east);
	// printf("WEST : %s\n", global->textures->west);
}
