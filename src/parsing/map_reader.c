/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 17:57:49 by mickzhan          #+#    #+#             */
/*   Updated: 2026/04/24 15:23:45 by mickzhan         ###   ########.fr       */
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
		return (free(cpy), printf("Error\nFichier n'existe pas\n"), exit(1), NULL);
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

bool	line_check(char *str)
{
	int i;

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

void	free_all(t_global *global)
{
	int i;
	i = 0;
	
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
	if (global->textures)
		free(global->textures);
	while (global->map.mapy[i])
	{
		free(global->map.mapy[i]);
		i++;
	}
	free(global->map.mapy);
	free(global);
}
