/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:19:37 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/15 15:20:53 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
