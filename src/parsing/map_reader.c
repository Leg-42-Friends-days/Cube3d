/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 17:57:49 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/04 17:39:53 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	map_cub(char *str)
{
	int		len;
	int		fd;
	char	*cub;

	cub = ".cub";
	if (!str)
		return (ft_putendl_fd("Error\nMauvais fichier", 2), 1);
	len = ft_strlen(str);
	if (len < 4 || ft_strncmp(str + (len - 4), cub, 4) != 0)
		return (ft_putendl_fd("Error\nMauvais fichier", 2), 1);
	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (ft_putendl_fd("Error\nMauvais fichier", 2), 1);
	close(fd);
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
	if (!cpy)
		return (NULL);
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
		return (free(cpy), printf("Error\nFichier n'existe pas\n"), NULL);
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
	while (i < 6)
	{
		if (global->textures->stock[i] != 1)
			return (true);
		i++;
	}
	return (false);
}

bool	line_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (char_check(str[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	error_gestion(int ac, char **av)
{
	if (ac != 2)
		return (printf("Bad argument"), 1);
	if (map_cub(av[1]) == 1)
		return (printf("Bad map\n"), 1);
	return (0);
}

void	free_texture(t_global *global)
{
	if (!global)
		return ;
	if (global->textures)
	{
		if (global->textures->ceiling)
			free(global->textures->ceiling);
		if (global->textures->floor)
			free(global->textures->floor);
		if (global->textures->north)
			free(global->textures->north);
		if (global->textures->south)
			free(global->textures->south);
		if (global->textures->west)
			free(global->textures->west);
		if (global->textures->east)
			free(global->textures->east);
		free(global->textures);
	}
}

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

void	free_all(t_global *global)
{
	if (!global)
		return ;
	free_texture(global);
	free_map(global);
	free(global);
}

void	error_exit(t_global *global)
{
	get_next_line(-1);
	free_all(global);
	exit(1);
}

void	convert_line4(t_global *global, char *line, int fd)
{
	if (ft_strncmp(is_space(line), "WE", 2) == 0)
	{
		if (global->textures->stock[1] == 1)
			return (printf("Error\nTo much WE"), free(line), close(fd),
				error_exit(global));
		global->textures->stock[1] = 1;
		global->textures->west = texture_map(is_space(line) + 2);
		if (!global->textures->west)
			return (free(line), close(fd), error_exit(global));
		global->textures->start++;
	}
	else
	{
		if (line_check(line))
			return (printf("Error\nMap invalid\n"), free(line), close(fd),
				error_exit(global));
		if (nothing_slash(line) == 1)
			global->textures->end++;
		else
			global->textures->start++;
	}
}

void	convert_line3(t_global *global, char *line, int fd)
{
	if (ft_strncmp(is_space(line), "F", 1) == 0)
	{
		if (global->textures->stock[4] == 1)
			return (printf("Error\nTo much F"), free(line), close(fd),
				error_exit(global));
		global->textures->stock[4] = 1;
		global->textures->floor = rgb_map(is_space(line) + 1);
		if (!global->textures->floor)
			return (free(line), close(fd), error_exit(global));
		global->textures->start++;
	}
	else if (ft_strncmp(is_space(line), "C", 1) == 0)
	{
		if (global->textures->stock[5] == 1)
			return (printf("Error\nTo much C"), free(line), close(fd),
				error_exit(global));
		global->textures->ceiling = rgb_map(is_space(line) + 1);
		if (!global->textures->ceiling)
			return (free(line), close(fd), error_exit(global));
		global->textures->stock[5] = 1;
		global->textures->start++;
	}
	else
		convert_line4(global, line, fd);
}

void	convert_line2(t_global *global, char *line, int fd)
{
	if (ft_strncmp(is_space(line), "SO", 2) == 0)
	{
		if (global->textures->stock[2] == 1)
			return (printf("Error\nTo much SO"), free(line), close(fd),
				error_exit(global));
		global->textures->stock[2] = 1;
		global->textures->south = texture_map(is_space(line) + 2);
		if (!global->textures->south)
			return (free(line), close(fd), error_exit(global));
		global->textures->start++;
	}
	else if (ft_strncmp(is_space(line), "EA", 2) == 0)
	{
		if (global->textures->stock[3] == 1)
			return (printf("Error\nTo much EA"), free(line), close(fd),
				error_exit(global));
		global->textures->east = texture_map(is_space(line) + 2);
		if (!global->textures->east)
			return (free(line), close(fd), error_exit(global));
		global->textures->stock[3] = 1;
		global->textures->start++;
	}
	else
		convert_line3(global, line, fd);
}

void	convert_line(t_global *global, char *line, int fd)
{
	if (stock_checker(global) == 1 && global->textures->end == 1)
		return ;
	if (ft_strncmp(is_space(line), "NO", 2) == 0)
	{
		if (global->textures->stock[0] == 1)
			return (printf("Error\nTo much NO\n"), free(line), close(fd),
				error_exit(global));
		global->textures->stock[0] = 1;
		global->textures->north = texture_map(is_space(line) + 2);
		if (!global->textures->north)
			return (free(line), close(fd), error_exit(global));
		global->textures->start++;
	}
	else
		convert_line2(global, line, fd);
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
	if (fd == -1)
		return (printf("Error\n"), error_exit(global));
	line = get_next_line(fd);
	if (!line)
		return (printf("Error\nDossier vide"), close(fd), error_exit(global));
	while (line)
	{
		convert_line(global, line, fd);
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
	global->map.mapou[index] = ft_strdup(line);
	global->map.mapou[index + 1] = NULL;
}

void	map_index2(t_global *global, int *fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(*fd);
	if (line == NULL)
		return (printf("Error\nNO MAP\n"), error_exit(global));
	while (line)
	{
		add_map(global, line, i);
		if (!global->map.mapou[i])
			return (free(line), close(*fd), error_exit(global));
		free(line);
		line = get_next_line(*fd);
		i++;
	}
}

void	map_index(t_global *global, char *map_content)
{
	int		len;
	int		fd;
	char	*line;

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
	map_index2(global, &fd);
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
	while (global->map.mapou[i])
	{
		if (error_check(global->map.mapou) == 1)
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

int	get_width_map(char **mapou)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	max = 0;
	while (mapou[i])
	{
		j = 0;
		while (mapou[i][j] && mapou[i][j] != '\n')
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

// void	affichage_map(t_global *global)
// {
// 	int	i;

// 	i = 0;
// 	while (global->map.fake_map[i])
// 	{
// 		printf("%s\n", global->map.fake_map[i]);
// 		i++;
// 	}
// }

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
				// affichage_map(global);
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

bool	rgb_checker(char *str)
{
	int	i;
	int	max;
	int	vir;

	vir = 0;
	i = 0;
	max = ft_atoi(str);
	printf("max : %d\n", max);
	while (ft_isdigit(str[i]) || str[i] == ' ' || str[i] == ',')
	{
		if (max < 0 || max > 255)
			return (true);
		if (str[i] == ',')
		{
			vir++;
			i++;
			max = ft_atoi(str + i);
			printf("new : max : %d\n", max);
		}
		i++;
	}
	if (vir != 2)
		return (true);
	return (false);
}

bool	check_rgb(t_global *global)
{
	printf("RGB F : %s\n", global->textures->floor);
	printf("RGB C : %s\n", global->textures->ceiling);
	if (rgb_checker(global->textures->floor) == 1)
	{
		printf("HERE\n");
		return (true);
	}
	if (rgb_checker(global->textures->ceiling))
	{
		printf("C HERE\n");
		return (true);
	}
	return (false);
}

bool	start_map(t_global *global, char *map_content)
{
	int	map_len;

	map_len = map_start(global, map_content);
	global->map.mapou = malloc(sizeof(char *) * (map_len + 1));
	if (!global->map.mapou)
		return (true);
	map_index(global, map_content);
	if (!global->map.mapou)
		return (printf("Error\nMap\n"), error_exit(global), true);
	if (check_rgb(global) == 1)
		return (printf("Error\nRGB\n"), 1);
	if (map_check(global) == 1)
		return (error_exit(global), true);
	if (check_mapline(global->map.mapou) == 1)
		return (printf("Error\nMap\n"), error_exit(global), true);
	global->map.height = get_height_map(map_content);
	if (global->map.height < 0)
		return (error_exit(global), true);
	global->map.height -= global->textures->start;
	global->map.width = get_width_map(global->map.mapou);
	if (build_fake_map(global))
		return (error_exit(global), true);
	if (map_flood(global) == 1)
		return (printf("Error\nMap incorrect"));
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
	global->map.fake_map = NULL;
	global->map.wopen = 0;
	return (global);
}
