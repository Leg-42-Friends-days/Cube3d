/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:13:37 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/15 15:14:31 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
