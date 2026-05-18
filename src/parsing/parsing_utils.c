/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:09:37 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/18 17:14:01 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		return (ft_printf(2, "Error\nIncorrect map"), error_exit(global));
	while (len < global->textures->start)
	{
		line = get_next_line(fd);
		free(line);
		len++;
	}
	map_index2(global, &fd);
	close(fd);
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
