/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:17:51 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/28 15:36:53 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	solo_reader(t_global *global, char *map_content, char *str)
{
	int		fd;
	int		n;
	char	*line;

	(void)global;
	n = 0;
	fd = open(map_content, O_RDONLY);
	if (fd == -1)
		return (ft_printf(2, "Error\nOpen\n"), error_exit(global), true);
	line = get_next_line(fd);
	if (!line)
		return (ft_printf(2, "Error\nEmpty file\n"), close(fd),
			error_exit(global), true);
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
	if (bonus_reader(global, map_content, "R") == 1)
		return (ft_printf(2, "Error\nInvalid map (R)\n"), true);
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
		return (ft_printf(2, "Error\nOpen\n"), error_exit(global));
	line = get_next_line(fd);
	if (!line)
		return (ft_printf(2, "Error\nDossier vide\n"), close(fd),
			error_exit(global));
	while (line)
	{
		convert_line(global, line, fd);
		free(line);
		line = get_next_line(fd);
	}
	if (global->textures->bonus[1] || global->textures->bonus[2])
		if (!global->textures->bonus[1] || !global->textures->bonus[2])
			return (ft_printf(2, "Error\nBonus sprite\n"), close(fd),
				error_exit(global));
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
