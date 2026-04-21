/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:50:04 by mickzhan          #+#    #+#             */
/*   Updated: 2026/04/21 19:19:01 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*is_space(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
			return (str + i);
	}
	return (str);
}

char	*texture_map(char *str)
{
	int		i;
	char	*cpy;

	i = 0;
	while (str[i] == ' ')
		i++;
	cpy = ft_strdup(str + i);
	return (cpy);
}

void	convert_line(t_global *global, char *line)
{
	if (ft_strncmp(is_space(line), "NO", 2) == 0)
		global->t_textures->north = texture_map(is_space(line) + 2);
	if (ft_strncmp(is_space(line), "WE", 2) == 0)
		global->t_textures->west = texture_map(is_space(line) + 2);
	if (ft_strncmp(is_space(line), "SO", 2) == 0)
		global->t_textures->south = texture_map(is_space(line) + 2);
	if (ft_strncmp(is_space(line), "EA", 2) == 0)
		global->t_textures->east = texture_map(is_space(line) + 2);
	if (ft_strncmp(is_space(line), "F", 1) == 0)
		global->t_textures->floor = texture_map(is_space(line) + 1);
	if (ft_strncmp(is_space(line), "C", 1) == 0)
		global->t_textures->ceiling = texture_map(is_space(line) + 1);
}

void	read_map(t_global *global, char *map_content)
{
	int		fd;
	char	*line;

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
	printf("NORTH :%s", global->t_textures->north);
	printf("SOUTH : %s", global->t_textures->south);
	printf("FLOOR: %s", global->t_textures->floor);
	printf("CEILI : %s", global->t_textures->ceiling);
	printf("WEAST : %s", global->t_textures->west);
	printf("EAST : %s", global->t_textures->east);
}

int	error_gestion(int ac, char **av)
{
	if (ac != 2)
		return (printf("Bad argument"), 1);
	if (map_cub(av[1]) == 1)
		return (printf("Bad map"), 1);
	return (0);
}

void	free_all(t_global *global)
{
	free(global->t_textures->ceiling);
	free(global->t_textures->east);
	free(global->t_textures->floor);
	free(global->t_textures->north);
	free(global->t_textures->south);
	free(global->t_textures->west);
	free(global->t_textures);
	free(global);
}

int	main(int ac, char **av)
{
	t_global	*global;

	if (error_gestion(ac, av) == 1)
		return (1);
	global = malloc(sizeof(t_global));
	global->t_textures = malloc(sizeof(t_textures));
	read_map(global, av[1]);
	free_all(global);
	return (0);
}
