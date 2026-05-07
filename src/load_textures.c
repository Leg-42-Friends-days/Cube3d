/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 14:23:06 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/05 14:35:45 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void    load_texture(t_global *global, t_xpm *tex, char *path)
{
    tex->img_ptr = mlx_xpm_file_to_image(global->mlx, path, &tex->width, &tex->height);
    if (!tex->img_ptr)
    {
        perror("Error texture ");
        free_all(global);
        exit (1);
    }
    tex->data = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len, &tex->endian);

}

void    load_all_textures(t_global *global)
{
    load_texture(global, &(global->raycast_data.north), global->textures->north);
    load_texture(global, &(global->raycast_data.east), global->textures->east);
    load_texture(global, &(global->raycast_data.west), global->textures->west);
    load_texture(global, &(global->raycast_data.south), global->textures->south);
}