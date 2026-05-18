/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:53:27 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/18 17:03:58 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	convert_line5(t_global *global, char *line, int fd)
{
	if (ft_strncmp(is_space(line), "R", 1) == 0)
	{
		global->textures->stock[8] = 1;
		global->textures->bonus[2] = 1;
		global->textures->sprite2 = texture_map(is_space(line) + 1);
		if (!global->textures->sprite2)
			return (ft_printf(2, "Error\nTexture (R)\n"), free(line), close(fd),
				error_exit(global));
		global->textures->start++;
	}
	else
	{
		if (line_check(line, global))
			return (ft_printf(2, "Error\nMap invalid\n"), free(line), close(fd),
				error_exit(global));
		if (nothing_slash(line) == 1)
			global->textures->end++;
		else
			global->textures->start++;
	}
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
		global->textures->sprite = texture_map(is_space(line) + 1);
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
