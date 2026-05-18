/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_fonction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:06:04 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/18 18:04:12 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	rgb_checker(char *str)
{
	int	i;
	int	max;
	int	vir;

	vir = 0;
	i = 0;
	max = ft_atoi(str);
	while (str[i] == ' ')
		i++;
	while (ft_isdigit(str[i]) || str[i] == ',')
	{
		if (max < 0 || max > 255)
			return (true);
		if (str[i] == ',')
		{
			vir++;
			max = ft_atoi(str + i + 1);
		}
		i++;
	}
	if (str[i] && str[i] != '\n')
		return (true);
	if (vir != 2)
		return (true);
	return (check_if_alpha(str));
}

bool	check_rgb(char *str)
{
	if (rgb_checker(str) == 1)
		return (true);
	return (false);
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
	if (check_rgb(str) == 1)
		return (free(cpy), NULL);
	return (cpy);
}
