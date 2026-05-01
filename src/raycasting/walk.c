/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 13:48:19 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/01 15:44:55 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void    right_rotation(t_raycast_data *data)
{
	double  old_dir_x;
	double	rot_speed;
	double	old_plane_x;
	
	rot_speed = 0.2;
	old_dir_x = data->dir.x;
	old_plane_x = data->plane.x;
	data->dir.x = data->dir.x * cos(-rot_speed) - data->dir.y * sin(-rot_speed);
	data->dir.y = old_dir_x * sin(-rot_speed) + data->dir.y * cos(-rot_speed);
	data->plane.x = data->plane.x * cos(-rot_speed) - data->plane.y * sin(-rot_speed);
	data->plane.y = old_plane_x * sin(-rot_speed) + data->plane.y * cos(-rot_speed);
}

void    left_rotation(t_raycast_data *data)
{
	double  old_dir_x;
	double	rot_speed;
	double	old_plane_x;
	
	rot_speed = 0.2;
	old_dir_x = data->dir.x;
	old_plane_x = data->plane.x;
	data->dir.x = data->dir.x * cos(rot_speed) - data->dir.y * sin(rot_speed);
	data->dir.y = old_dir_x * sin(rot_speed) + data->dir.y * cos(rot_speed);
	data->plane.x = data->plane.x * cos(rot_speed) - data->plane.y * sin(rot_speed);
	data->plane.y = old_plane_x * sin(rot_speed) + data->plane.y * cos(rot_speed);
}

int	rotate(int keycode, t_global *global)
{
	if (keycode == LEFT)
		left_rotation(&(global->raycast_data));
	if (keycode == RIGHT)
		right_rotation(&(global->raycast_data));
	mlx_destroy_image(global->mlx, global->img.img);
	global->img.img = mlx_new_image(global->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	global->img.addr = mlx_get_data_addr(global->img.img, &global->img.bits_per_pixel,
			&global->img.line_length, &global->img.endian);
	go_though_all_rays(&(global->raycast_data), &(global->map), global);
	mlx_put_image_to_window(global->mlx, global->win, global->img.img, 0, 0);
	return (0);
}

int	walk(int keycode, t_global *global)
{
	double			move_speed;
	t_raycast_data	*data;

	data = &(global->raycast_data);
	move_speed = 0.5;
	if (keycode == UP)
	{
		data->player.x += data->dir.x * move_speed;
		data->player.y += data->dir.y * move_speed;
	}
	if (keycode == DOWN)
	{
		data->player.x -= data->dir.x * move_speed;
		data->player.y -= data->dir.y * move_speed;
	}
	mlx_destroy_image(global->mlx, global->img.img);
	global->img.img = mlx_new_image(global->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	global->img.addr = mlx_get_data_addr(global->img.img, &global->img.bits_per_pixel,
			&global->img.line_length, &global->img.endian);
	go_though_all_rays(&(global->raycast_data), &(global->map), global);
	mlx_put_image_to_window(global->mlx, global->win, global->img.img, 0, 0);
	return (0);
}
