/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:50:04 by mickzhan          #+#    #+#             */
/*   Updated: 2026/04/23 13:10:11 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_start(t_global *global, char *map_content)
{
	int		i;
	int		len;
	int		fd;
	char	*line;

	i = 0;
	len = 0;
	fd = open(map_content, O_RDONLY);
	while (len < global->textures->start)
	{
		line = get_next_line(fd);
		free(line);
		len++;
	}
	line = get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

void	add_map(t_global *global, char *line, int index)
{
	global->map.mapy[index] = ft_strdup(line);
	global->map.mapy[index + 1] = NULL;
}

void	map_index(t_global *global, char *map_content)
{
	int		i;
	int		len;
	int		fd;
	char	*line;

	i = 0;
	len = 0;
	fd = open(map_content, O_RDONLY);
	while (len < global->textures->start)
	{
		line = get_next_line(fd);
		free(line);
		len++;
	}
	line = get_next_line(fd);
	while (line)
	{
		add_map(global, line, i);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}

void	start_map(t_global *global, char *map_content)
{
	int	map_len;

	map_len = map_start(global, map_content);
	printf("start line : %d\n", map_len);
	global->map.mapy = malloc(sizeof(char *) * (map_len + 1));
	map_index(global, map_content);

}

int	main(int ac, char **av)
{
	t_global	*global;

	if (error_gestion(ac, av) == 1)
		return (1);
	global = malloc(sizeof(t_global));
	global->textures = malloc(sizeof(t_textures));
	read_map(global, av[1]);
	// printf("map start point : %d", global->textures->start);
	start_map(global, av[1]);
	int i;
	i = 0;
	while (global->map.mapy[i])
	{
		printf("Map : %s", global->map.mapy[i]);
		i++;
	}
	// free_all(global);
	return (0);
}
