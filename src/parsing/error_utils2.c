/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:15:11 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/15 15:15:32 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	check_if_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a'
				&& str[i] <= 'b'))
			return (true);
		i++;
	}
	return (false);
}

int	map_cub(char *str)
{
	int		len;
	int		fd;
	char	*cub;

	cub = ".cub";
	if (!str)
		return (1);
	len = ft_strlen(str);
	if (len < 4 || ft_strncmp(str + (len - 4), cub, 4) != 0)
		return (1);
	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}
