/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:50:04 by mickzhan          #+#    #+#             */
/*   Updated: 2026/04/29 11:08:47 by mickzhan         ###   ########.fr       */
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
	if (fd == -1)
		return (error_exit(global), 0);
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
	if (fd == -1)
		return (error_exit(global));
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
		if (!global->map.mapy[i])
			return (free(line), close(fd), error_exit(global));
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}

bool	char_check(char ch)
{
	if (ch == ' ' || ch == '\n' || ch == '1' || ch == '0' || ch == 'N'
		|| ch == 'S' || ch == 'E' || ch == 'W')
		return (true);
	else
		return (false);
}

bool	direction_check(char ch)
{
	if (ch == 'W' || ch == 'S' || ch == 'E' || ch == 'N')
		return (true);
	else
		return (false);
}

bool	error_check(char **str)
{
	int	i;
	int	j;
	int	cpt;

	cpt = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (direction_check(str[i][j]))
				cpt++;
			if (char_check(str[i][j]))
				j++;
			else
				return (true);
		}
		i++;
	}
	if (cpt != 1)
		return (true);
	return (false);
}

bool	map_check(t_global *global)
{
	int	i;

	i = 0;
	while (global->map.mapy[i])
	{
		if (error_check(global->map.mapy) == 1)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

int	get_height_map(char *map)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (ft_putendl_fd("Error\nMauvais fichier", 2), -1);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}

int	get_width_map(char **mapy)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	max = 0;
	while (mapy[i])
	{
		j = 0;
		while (mapy[i][j] && mapy[i][j] != '\n')
		{
			j++;
			if (max < j)
				max = j;
		}
		i++;
	}
	return (max);
}

bool	check_mapline(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == '\n')
			return (true);
		i++;
	}
	return (false);
}

void	flood_fill(t_global *global, int x, int y)
{
	if (x < 0 || y < 0 || x >= global->map.width || y >= global->map.height)
		return ;
	if (global->map.mapy[y][x] == 'x' || global->map.mapy[y][x] == '1')
		return ;
	global->map.mapy[y][x] = 'x';
	flood_fill(global, x - 1, y);
	flood_fill(global, x + 1, y);
	flood_fill(global, x, y - 1);
	flood_fill(global, x, y + 1);
	flood_fill(global, x + 1, y + 1);
	flood_fill(global, x - 1, y - 1);
	flood_fill(global, x - 1, y + 1);
	flood_fill(global, x + 1, y - 1);
}

int	map_flood(t_global *global)
{
	int	row;
	int	col;
	int	x;
	int	y;

	y = 0;
	row = global->map.width;
	col = global->map.height;
	while (y < col)
	{
		x = 0;
		while (x < row)
		{
			if (global->map.mapy[y][x] == 'N')
			{
				flood_fill(global, x, y);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (0);
}

bool	start_map(t_global *global, char *map_content)
{
	int	map_len;

	map_len = map_start(global, map_content);
	global->map.mapy = malloc(sizeof(char *) * (map_len + 1));
	if (!global->map.mapy)
		return (true);
	map_index(global, map_content);
	if (!global->map.mapy)
		return (printf("MAPY N'EXISTE PAS\n"), error_exit(global), true);
	if (map_check(global) == 1)
		return (error_exit(global), true);
	if (check_mapline(global->map.mapy) == 1)
		return (printf("Error\nMap to much line\n"), error_exit(global), true);
	// if (map_flood(global) == 1)
	// return (printf("Error\nMap incorrect"));
	global->map.height = get_height_map(map_content);
	if (global->map.height < 0)
		return (error_exit(global), true);
	global->map.height -= global->textures->start;
	global->map.width = get_width_map(global->map.mapy);
	return (false);
}

t_global	*init_malloc(void)
{
	t_global	*global;

	global = malloc(sizeof(t_global));
	if (!global)
		return (exit(1), NULL);
	ft_bzero(global, sizeof(t_global));
	global->textures = malloc(sizeof(t_textures));
	if (!global->textures)
		return (free(global), exit(1), NULL);
	ft_bzero(global->textures, sizeof(t_textures));
	return (global);
}

int	main(int ac, char **av)
{
	t_global	*global;
	int			i;

	if (error_gestion(ac, av) == 1)
		return (1);
	global = init_malloc();
	read_map(global, av[1]);
	if (start_map(global, av[1]) == 1)
		return (free_all(global), 1);
	i = 0;
	while (global->map.mapy[i])
	{
		printf("Map : %s", global->map.mapy[i]);
		i++;
	}
	printf("\n");
	printf("height : %d\n", global->map.height);
	printf("width : %d\n", global->map.width);
	free_all(global);
	return (0);
}
