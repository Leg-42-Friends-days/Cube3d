/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:59:42 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/19 17:22:54 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_all(t_global *global)
{
	if (!global)
		return ;
	free_texture(global);
	free_map(global);
	if (global->img.tile)
		free(global->img.tile);
	free(global);
}

void	error_exit(t_global *global)
{
	get_next_line(-1);
	free_all(global);
	exit(1);
}

void	free_texture(t_global *global)
{
	if (!global)
		return ;
	if (global->textures)
	{
		if (global->textures->ceiling)
			free(global->textures->ceiling);
		if (global->textures->floor)
			free(global->textures->floor);
		if (global->textures->north)
			free(global->textures->north);
		if (global->textures->south)
			free(global->textures->south);
		if (global->textures->west)
			free(global->textures->west);
		if (global->textures->east)
			free(global->textures->east);
		if (global->textures->door)
			free(global->textures->door);
		if (global->textures->sprite)
			free(global->textures->sprite);
		if (global->textures->sprite2)
			free(global->textures->sprite2);
		free(global->textures);
	}
}
