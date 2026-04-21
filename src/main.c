/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:50:04 by mickzhan          #+#    #+#             */
/*   Updated: 2026/04/21 16:18:11 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	error_gestion(int ac, char **av)
{
	if (ac != 2)
		return (printf("Bad argument"), 1);
	if (map_cub(av[1]) == 1)
		return (printf("Bad map"), 1);
	return (0);
}

int	map_len(char *map_content)
{
	int		fd;
	int		len;
	char	*line;

	len = 0;
	fd = open(map_content, O_RDONLY);
	if (fd == -1)
		return (printf("Error fd"), exit(1), 1);
	line = get_next_line(fd);
	if (!line)
		return (printf("Error\n Map"), exit(1), 1);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		len++;
	}
	close(fd);
	return (len);
}

char	**read_map(char *map_content)
{
	int		fd;
	int		len;
	char	*line;
	char	**content;
	int		i;

	i = 0;
	len = map_len(map_content);
	content = malloc(sizeof(char *) * (len + 1));
	if (!content)
		return (printf("Error\nMalloc"), exit(1), NULL);
	fd = open(map_content, O_RDONLY);
	if (!fd)
		return (printf("Error\n"), exit(1), NULL);
	line = get_next_line(fd);
	while (line)
	{
		content[i] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		printf("%s", content[i]);
		i++;
	}
	content[i] = NULL;
	return (content);
}

int	main(int ac, char **av)
{
	t_map	*map;

	if (error_gestion(ac, av) == 1)
		return (1);
	map = malloc(sizeof(t_map));
	map->map = read_map(av[1]);
	return (0);
}
