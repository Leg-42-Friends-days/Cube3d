/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 14:23:06 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/22 17:20:21 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_if_error(t_global *global)
{
	mlx_destroy_display(global->mlx);
	free(global->mlx);
	free_all(global);
	exit(1);
}

int	load_texture(t_global *global, t_xpm *tex, char *path)
{
	tex->img_ptr = mlx_xpm_file_to_image(global->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img_ptr)
	{
		perror("Error\nTexture ");
		return (1);
	}
	tex->data = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len,
			&tex->endian);
	return (0);
}

void	load_all_textures(t_global *global)
{
	if (load_texture(global, &(global->raycast_data.north),
			global->textures->north))
		free_if_error(global);
	if (load_texture(global, &(global->raycast_data.east),
			global->textures->east))
	{
		mlx_destroy_image(global->mlx, global->raycast_data.north.img_ptr);
		free_if_error(global);
	}
	if (load_texture(global, &(global->raycast_data.west),
			global->textures->west))
	{
		mlx_destroy_image(global->mlx, global->raycast_data.north.img_ptr);
		mlx_destroy_image(global->mlx, global->raycast_data.east.img_ptr);
		free_if_error(global);
	}
	if (load_texture(global, &(global->raycast_data.south),
			global->textures->south))
	{
		mlx_destroy_image(global->mlx, global->raycast_data.north.img_ptr);
		mlx_destroy_image(global->mlx, global->raycast_data.east.img_ptr);
		mlx_destroy_image(global->mlx, global->raycast_data.west.img_ptr);
		free_if_error(global);
	}
}
