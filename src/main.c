/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:50:04 by mickzhan          #+#    #+#             */
/*   Updated: 2026/04/24 15:11:15 by mickzhan         ###   ########.fr       */
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
			// printf("HAHA NO MAP\n");
			// exit(1);
			return (true);
		}
		i++;
	}
	return (false);
}

void	start_map(t_global *global, char *map_content)
{
	int	map_len;

	map_len = map_start(global, map_content);
	global->map.mapy = malloc(sizeof(char *) * (map_len + 1));
	map_index(global, map_content);
	map_check(global);
	// map_cpy(global);
}

int	main(int ac, char **av)
{
	t_global	*global;
	// int			i;

	if (error_gestion(ac, av) == 1)
		return (1);
	global = malloc(sizeof(t_global));
	global->textures = malloc(sizeof(t_textures));
	read_map(global, av[1]);
	start_map(global, av[1]);
	// i = 0;
	// while (global->map.mapy[i])
	// {
	// 	printf("Map : %s", global->map.mapy[i]);
	// 	i++;
	// }
	free_all(global);
	return (0);
}
