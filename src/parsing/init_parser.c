/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:11:48 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/18 16:53:47 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initiate_stock(t_global *global)
{
	global->textures->stock[0] = 0;
	global->textures->stock[1] = 0;
	global->textures->stock[2] = 0;
	global->textures->stock[3] = 0;
	global->textures->stock[4] = 0;
	global->textures->stock[5] = 0;
	global->textures->stock[6] = 1;
	global->textures->stock[7] = 1;
	global->textures->stock[8] = 1;
	global->textures->bonus[0] = 0;
	global->textures->bonus[1] = 0;
	global->textures->bonus[2] = 0;
}

t_global	*init_malloc(void)
{
	t_global	*global;

	global = malloc(sizeof(t_global));
	if (!global)
		return (exit(1), NULL);
	ft_bzero(global, sizeof(t_global));
	global->textures = malloc(sizeof(t_textures));
	if (!global->textures)
		return (free(global), exit(1), NULL);
	ft_bzero(global->textures, sizeof(t_textures));
	global->map.fake_map = NULL;
	global->map.mapou = NULL;
	global->map.wopen = 0;
	global->textures->start = 0;
	global->textures->end = 0;
	global->textures->beer = 0;
	return (global);
}
