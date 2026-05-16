/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 13:48:19 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/16 19:08:46 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	left_rotation(t_raycast_data *data)
{
	double	old_dir_x;
	double	rot_speed;
	double	old_plane_x;

	rot_speed = 0.05;
	old_dir_x = data->dir.x;
	old_plane_x = data->plane.x;
	data->dir.x = data->dir.x * cos(-rot_speed) - data->dir.y * sin(-rot_speed);
	data->dir.y = old_dir_x * sin(-rot_speed) + data->dir.y * cos(-rot_speed);
	data->plane.x = data->plane.x * cos(-rot_speed) - data->plane.y
		* sin(-rot_speed);
	data->plane.y = old_plane_x * sin(-rot_speed) + data->plane.y
		* cos(-rot_speed);
}

void	right_rotation(t_raycast_data *data)
{
	double	old_dir_x;
	double	rot_speed;
	double	old_plane_x;

	rot_speed = 0.05;
	old_dir_x = data->dir.x;
	old_plane_x = data->plane.x;
	data->dir.x = data->dir.x * cos(rot_speed) - data->dir.y * sin(rot_speed);
	data->dir.y = old_dir_x * sin(rot_speed) + data->dir.y * cos(rot_speed);
	data->plane.x = data->plane.x * cos(rot_speed) - data->plane.y
		* sin(rot_speed);
	data->plane.y = old_plane_x * sin(rot_speed) + data->plane.y
		* cos(rot_speed);
}

int	rotate(int keycode, t_global *global)
{
	if (keycode == LEFT)
		left_rotation(&(global->raycast_data));
	if (keycode == RIGHT)
		right_rotation(&(global->raycast_data));
	refresh_image(global);
	return (0);
}

int	crab_walk(int keycode, t_global *global)
{
	double			move_speed;
	t_raycast_data	*data;

	data = &(global->raycast_data);
	move_speed = 0.1;
	if (keycode == D)
	{
		if (collision_detection(&(global->raycast_data), &(global->map), 3))
			return (1);
		data->player.x += -data->dir.y * move_speed;
		data->player.y += data->dir.x * move_speed;
	}
	if (keycode == A)
	{
		if (collision_detection(&(global->raycast_data), &(global->map), 4))
			return (1);
		data->player.x += data->dir.y * move_speed;
		data->player.y += -data->dir.x * move_speed;
	}
	refresh_image(global);
	return (0);
}

int	walk(int keycode, t_global *global)
{
	double			move_speed;
	t_raycast_data	*data;

	data = &(global->raycast_data);
	move_speed = 0.1;
	if (keycode == W)
	{
		if (collision_detection(&(global->raycast_data), &(global->map), 1))
			return (1);
		data->player.x += data->dir.x * move_speed;
		data->player.y += data->dir.y * move_speed;
	}
	if (keycode == S)
	{
		if (collision_detection(&(global->raycast_data), &(global->map), 2))
			return (1);
		data->player.x -= data->dir.x * move_speed;
		data->player.y -= data->dir.y * move_speed;
	}
	refresh_image(global);
	return (0);
}
