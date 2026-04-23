/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_create_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 15:42:00 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/23 11:54:03 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void    create_map(t_map *map, char *str)
{
	int     fd;
	char    *line;
	int     i;

	i = 0;
	fd = open(str, O_RDONLY);
	map->mapy = malloc(sizeof(char *) * 14);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map->mapy[i] = line;
		i++;
	}
	i = 0;
	map->height = 14;
	map->width = 33;
	/* while (i < 14)
	{
		printf("%s\n", map.mapy[i]);
		i ++;
	} */
}
