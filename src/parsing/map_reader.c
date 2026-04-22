/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 17:57:49 by mickzhan          #+#    #+#             */
/*   Updated: 2026/04/21 17:58:10 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	map_cub(char *str)
{
	int		i;
	int		j;
	char	*cub;

	i = 0;
	j = 0;
	cub = ".cub";
	while (str[i])
		i++;
	i -= 4;
	while (str[i] == cub[j])
	{
		i++;
		j++;
	}
	if (j == 5)
	{
		j = open(str, O_RDONLY);
		close(j);
		if (j < 0)
			return (ft_putendl_fd("Error\nMauvais fichier", 2), 1);
	}
	else
		return (ft_putendl_fd("Error\nMauvais fichier", 2), 1);
	return (0);
}

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

char	*copy_enter(char *str)
{
	int		i;
	char	*cpy;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		i++;
	}
	cpy = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*texture_map(char *str)
{
	int		i;
	int		fd;
	char	*cpy;

	i = 0;
	while (str[i] == ' ')
		i++;
	cpy = copy_enter(str + i);
	if (!cpy)
		return (NULL);
	fd = open(cpy, O_RDONLY);
	if (fd == -1)
		return (free(cpy), printf("Error\nFichier n'existe pas"), exit(1), NULL);
	close(fd);
	return (cpy);
}

char	*rgb_map(char *str)
{
	int		i;
	char	*cpy;

	i = 0;
	while (str[i] == ' ')
		i++;
	cpy = copy_enter(str + i);
	if (!cpy)
		return (NULL);
	return (cpy);
}

bool	nothing_slash(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\n')
			i++;
		else
			return (true);
	}
	return (false);
}

bool	stock_checker(t_global *global)
{
	int	i;

	i = 0;
	while (global->textures->stock[i])
	{
		if (global->textures->stock[i] != 1)
			return (true);
		i++;
	}
	return (false);
}

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
		if (nothing_slash(line) == 1)
			printf("Error\nMap not valid"), exit(1);
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
	if (stock_checker(global) == 1)
		return ;
	if (ft_strncmp(is_space(line), "NO", 2) == 0)
	{
		if (global->textures->stock[0] == 1)
			return (printf("Error\nTo much NO"), exit(1));
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

void	read_map(t_global *global, char *map_content)
{
	int		fd;
	char	*line;

	global->textures->start = 0;
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
	printf("CEILING :%s\n", global->textures->ceiling);
	printf("FLOOR : %s\n", global->textures->floor);
	printf("START POINT : %d\n", global->textures->start);
	printf("NORTH : %s\n", global->textures->north);
	printf("SOUTH : %s\n", global->textures->south);
	printf("EAST : %s\n", global->textures->east);
	printf("WEST : %s\n", global->textures->west);
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
	free(global->textures->ceiling);
	free(global->textures->floor);
	free(global->textures->north);
	free(global->textures->south);
	free(global->textures->west);
	free(global->textures->east);
	free(global->textures);
	free(global);
}
