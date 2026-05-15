/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:55:56 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/15 15:12:51 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int	error_gestion(int ac, char **av)
{
	if (ac != 2)
		return (ft_printf(2, "Error\nPlease use a map after [./Cub3d]\n"), 1);
	if (map_cub(av[1]) == 1)
		return (ft_printf(2, "Error\nThe map doesnt exist! or not a .cub!\n"),
			1);
	return (0);
}
