/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:50:04 by mickzhan          #+#    #+#             */
/*   Updated: 2026/04/20 16:48:41 by mickzhan         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	if (error_gestion(ac, av) == 1)
		return (1);
	return (0);
}
