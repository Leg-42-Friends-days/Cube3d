/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 17:57:15 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/20 17:57:33 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	refresh_image(t_global *global)
{
	go_though_all_rays(&(global->raycast_data), &(global->map), global);
	dessin(global);
	if (global->textures->beer > 0)
	{
		animation(global, global->sprite, get_time());
		sprite_2(global);
	}
	drunk_or_not_drunk(global, get_time());
	mlx_put_image_to_window(global->mlx, global->win, global->img.img, 0, 0);
}

void	refresh_drunk_image(t_global *global)
{
	deform_rays(&(global->raycast_data), &(global->map), global);
	dessin(global);
	if (global->textures->beer > 0)
	{
		animation(global, global->sprite, get_time());
		sprite_2(global);
	}
	drunk_or_not_drunk(global, get_time());
	mlx_put_image_to_window(global->mlx, global->win, global->img.img, 0, 0);
}
