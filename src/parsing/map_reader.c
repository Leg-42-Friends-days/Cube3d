/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 17:57:49 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/15 14:22:00 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	check_if_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a'
				&& str[i] <= 'b'))
			return (true);
		i++;
	}
	return (false);
}

bool	rgb_checker(char *str)
{
	int	i;
	int	max;
	int	vir;

	vir = 0;
	i = 0;
	max = ft_atoi(str);
	while (str[i] == ' ')
		i++;
	while (ft_isdigit(str[i]) || str[i] == ',')
	{
		if (max < 0 || max > 255)
			return (true);
		if (str[i] == ',')
		{
			vir++;
			max = ft_atoi(str + i + 1);
		}
		i++;
	}
	if (vir != 2)
		return (true);
	return (check_if_alpha(str));
}

bool	check_rgb(char *str)
{
	if (rgb_checker(str) == 1)
		return (true);
	return (false);
}

int	map_cub(char *str)
{
	int		len;
	int		fd;
	char	*cub;

	cub = ".cub";
	if (!str)
		return (1);
	len = ft_strlen(str);
	if (len < 4 || ft_strncmp(str + (len - 4), cub, 4) != 0)
		return (1);
	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (1);
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
		return (free(cpy), NULL);
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
	if (check_rgb(str) == 1)
		return (free(cpy), NULL);
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
	while (i < 8)
	{
		if (global->textures->stock[i] != 1)
			return (true);
		i++;
	}
	return (false);
}

bool	line_check(char *str, t_global *global)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (char_check(str[i], global) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	error_gestion(int ac, char **av)
{
	if (ac != 2)
		return (ft_printf(2, "Error\nPlease use a map after [./Cub3d]\n"), 1);
	if (map_cub(av[1]) == 1)
		return (ft_printf(2, "Error\nThe map doesnt exist! or not a .cub!\n"),
			1);
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
		if (global->textures->door)
			free(global->textures->door);
		if (global->textures->sprite)
			free(global->textures->sprite);
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
	if (global->img.tile)
		free(global->img.tile);
	free(global);
}

void	error_exit(t_global *global)
{
	get_next_line(-1);
	free_all(global);
	exit(1);
}

void	convert_line5(t_global *global, char *line, int fd)
{
	if (line_check(line, global))
		return (ft_printf(2, "Error\nMap invalid\n"), free(line), close(fd),
			error_exit(global));
	if (nothing_slash(line) == 1)
		global->textures->end++;
	else
		global->textures->start++;
}

void	convert_line4(t_global *global, char *line, int fd)
{
	if (ft_strncmp(is_space(line), "WE", 2) == 0)
	{
		global->textures->stock[1] = 1;
		global->textures->west = texture_map(is_space(line) + 2);
		if (!global->textures->west)
			return (ft_printf(2, "Error\nTexture (WE)\n"), free(line),
				close(fd), error_exit(global));
		global->textures->start++;
	}
	else if (ft_strncmp(is_space(line), "B", 1) == 0)
	{
		global->textures->stock[7] = 1;
		global->textures->bonus[1] = 1;
		global->textures->sprite = texture_map(is_space(line) + 2);
		if (!global->textures->sprite)
			return (ft_printf(2, "Error\nTexture (B)\n"), free(line), close(fd),
				error_exit(global));
		global->textures->start++;
	}
	else
		convert_line5(global, line, fd);
}

void	convert_line3(t_global *global, char *line, int fd)
{
	if (ft_strncmp(is_space(line), "F", 1) == 0)
	{
		global->textures->stock[4] = 1;
		global->textures->floor = rgb_map(is_space(line) + 1);
		if (!global->textures->floor)
			return (ft_printf(2, "Error\nBad arguments (F)\n"), free(line),
				close(fd), error_exit(global));
		global->textures->start++;
	}
	else if (ft_strncmp(is_space(line), "C", 1) == 0)
	{
		global->textures->ceiling = rgb_map(is_space(line) + 1);
		if (!global->textures->ceiling)
			return (ft_printf(2, "Error\nBad arguments (C)\n"), free(line),
				close(fd), error_exit(global));
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
		global->textures->stock[2] = 1;
		global->textures->south = texture_map(is_space(line) + 2);
		if (!global->textures->south)
			return (ft_printf(2, "Error\nTexture (SO)\n"), free(line),
				close(fd), error_exit(global));
		global->textures->start++;
	}
	else if (ft_strncmp(is_space(line), "EA", 2) == 0)
	{
		global->textures->stock[3] = 1;
		global->textures->east = texture_map(is_space(line) + 2);
		if (!global->textures->east)
			return (ft_printf(2, "Error\nTexture (EA)\n"), free(line),
				close(fd), error_exit(global));
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
		global->textures->stock[0] = 1;
		global->textures->north = texture_map(is_space(line) + 2);
		if (!global->textures->north)
			return (ft_printf(2, "Error\nTexture (NO)\n"), free(line),
				close(fd), error_exit(global));
		global->textures->start++;
	}
	else if (ft_strncmp(is_space(line), "D", 1) == 0)
	{
		global->textures->stock[6] = 1;
		global->textures->bonus[0] = 1;
		global->textures->door = texture_map(is_space(line) + 1);
		if (!global->textures->door)
			return (ft_printf(2, "Error\nTexture (D)\n"), free(line), close(fd),
				error_exit(global));
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
	global->textures->stock[6] = 1;
	global->textures->stock[7] = 1;
	global->textures->bonus[0] = 0;
	global->textures->bonus[1] = 0;
}

int	added_name(char *line, char *str)
{
	int	i;
	int	stock;

	stock = 0;
	i = ft_strlen(str);
	if (ft_strncmp(is_space(line), str, i) == 0)
		stock++;
	return (stock);
}

bool	solo_reader(t_global *global, char *map_content, char *str)
{
	int		fd;
	int		n;
	char	*line;

	(void)global;
	n = 0;
	fd = open(map_content, O_RDONLY);
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
	if (n != 1)
		return (true);
	return (false);
}

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
}

bool	bonus_reader(t_global *global, char *map_content, char *str)
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

bool	read_unique(t_global *global, char *map_content)
{
	if (solo_reader(global, map_content, "NO") == 1)
		return (ft_printf(2, "Error\nInvalid map (NO)\n"), true);
	if (solo_reader(global, map_content, "WE") == 1)
		return (ft_printf(2, "Error\nInvalid map (WE)\n"), true);
	if (solo_reader(global, map_content, "EA") == 1)
		return (ft_printf(2, "Error\nInvalid map (EA)\n"), true);
	if (solo_reader(global, map_content, "SO") == 1)
		return (ft_printf(2, "Error\nInvalid map (SO)\n"), true);
	if (solo_reader(global, map_content, "F") == 1)
		return (ft_printf(2, "Error\nInvalid map (F)\n"), true);
	if (solo_reader(global, map_content, "C") == 1)
		return (ft_printf(2, "Error\nInvalid map (C)\n"), true);
	if (bonus_reader(global, map_content, "D") == 1)
		return (ft_printf(2, "Error\nInvalid map (D)\n"), true);
	if (bonus_reader(global, map_content, "B") == 1)
		return (ft_printf(2, "Error\nInvalid map (B)\n"), true);
	return (false);
}

void	read_map(t_global *global, char *map_content)
{
	int		fd;
	char	*line;

	initiate_stock(global);
	if (read_unique(global, map_content))
		return (error_exit(global));
	fd = open(map_content, O_RDONLY);
	if (fd == -1)
		return (ft_printf(2, "Error\n"), error_exit(global));
	line = get_next_line(fd);
	if (!line)
		return (ft_printf(2, "Error\nDossier vide"), close(fd),
			error_exit(global));
	while (line)
	{
		convert_line(global, line, fd);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
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
		return (ft_printf(2, "Error\nThere is no map\n"), close(*fd),
			error_exit(global));
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
		return (printf("Error\nIncorrect map"), error_exit(global));
	while (len < global->textures->start)
	{
		line = get_next_line(fd);
		free(line);
		len++;
	}
	map_index2(global, &fd);
	close(fd);
}

bool	char_check(char ch, t_global *global)
{
	if (ch == ' ' || ch == '\n' || ch == '1' || ch == '0' || ch == 'N'
		|| ch == 'S' || ch == 'E' || ch == 'W')
		return (true);
	else if (global->textures->bonus[0] == 1 && ch == 'D')
		return (true);
	else if (global->textures->bonus[1] == 1 && ch == 'B')
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

bool	error_check(char **str, t_global *global)
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
			if (str[i][j] == 'B')
				global->textures->beer++;
			if (direction_check(str[i][j]))
				cpt++;
			if (char_check(str[i][j], global))
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
	if (error_check(global->map.mapou, global) == 1)
		return (true);
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

bool	start_map(t_global *global, char *map_content)
{
	int	map_len;

	map_len = map_start(global, map_content);
	if (map_len == 0)
		return (printf("Error\nMap doesnt exist\n"), error_exit(global), true);
	global->map.mapou = malloc(sizeof(char *) * (map_len + 1));
	if (!global->map.mapou)
		return (true);
	map_index(global, map_content);
	if (!global->map.mapou)
		return (ft_printf(2, "Error\nMap\n"), error_exit(global), true);
	if (map_check(global) == 1)
		return (printf("Error\nInvalid map\n"), error_exit(global), true);
	if (check_mapline(global->map.mapou) == 1)
		return (ft_printf(2, "Error\nMap\n"), error_exit(global), true);
	global->map.height = get_height_map(map_content);
	if (global->map.height < 0)
		return (error_exit(global), true);
	global->map.height -= global->textures->start;
	global->map.width = get_width_map(global->map.mapou);
	if (build_fake_map(global))
		return (error_exit(global), true);
	if (map_flood(global) == 1)
		return (ft_printf(2, "Error\nMap incorrect\n"), true);
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
	global->map.mapou = NULL;
	global->map.wopen = 0;
	global->textures->start = 0;
	global->textures->end = 0;
	global->textures->beer = 0;
	return (global);
}
