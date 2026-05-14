/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:35:44 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/14 14:51:08 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_sprite(t_global *global)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	map = global->map.mapou;
	while (i < global->map.height)
	{
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'B')
			{
				global->sprite.sprite.y = i;
				global->sprite.sprite.x = j;
				return ;
			}
			j++;
		}
		j = 0;
		i++;
	}
}
