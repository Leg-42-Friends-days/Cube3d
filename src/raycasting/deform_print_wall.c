/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deform_print_wall.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 10:45:04 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/20 17:53:40 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	filtre_color_in_hexa(char *color, t_global *global)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(color);
	while (*color != ',')
		color ++;
	color ++;
	g = ft_atoi(color);
	while (*color != ',')
		color ++;
	color ++;
	b = ft_atoi(color) + global->drunk.filter;
	return ((r << 16) | (g << 8) | b);
}

void	deform_print_wall(t_raycast_data *data, t_global *global, int x)
{
	data->print.line_height = (SCREEN_HEIGHT * 1.5) / data->perp_wall_dist;
	data->print.draw_start = -data->print.line_height / 2 + SCREEN_HEIGHT / 2;
	if (data->print.draw_start < 0)
		data->print.draw_start = 0;
	data->print.draw_end = data->print.line_height / 2 + SCREEN_HEIGHT / 2;
	if (data->print.draw_end >= SCREEN_HEIGHT)
		data->print.draw_end = SCREEN_HEIGHT - 1;
	calcul_image_sens(data, &data->print.wall_x);
	data->print.tex_x = (int)(data->print.wall_x * data->north.width);
	deform_print_line(global, data, x);
}

void	deform_print_floor(t_global *global, int x, int current)
{
	while (current < SCREEN_HEIGHT)
	{
		put_pixel(global, x, current,
			filtre_color_in_hexa(global->textures->floor, global));
		current ++;
	}
}

void	deform_print_ceiling(t_global *global, int x, int *current)
{
	while (*current < global->raycast_data.print.draw_start)
	{
		put_pixel(global, x, *current,
			filtre_color_in_hexa(global->textures->ceiling, global));
		*current = *current + 1;
	}
}

void	deform_print_line(t_global *global, t_raycast_data *data, int x)
{
	int		current;
	int		color;
	t_xpm	wall;

	wall = which_wall(data, global);
	data->print.step = (double)wall.height / data->print.line_height;
	data->print.tex_pos = (data->print.draw_start - SCREEN_HEIGHT / 2
			+ data->print.line_height / 2) * data->print.step;
	current = 0;
	deform_print_ceiling(global, x, &current);
	while (current < data->print.draw_end)
	{
		data->print.tex_y = (int)data->print.tex_pos % wall.height;
		data->print.tex_pos += data->print.step;
		color = *(int *)(wall.data
				+ data->print.tex_y * wall.line_len
				+ data->print.tex_x * (wall.bpp / 8)) + global->drunk.filter;
		current = current + global->drunk.double_vision;
		put_pixel(global, x, current, color);
		current++;
	}
	deform_print_floor(global, x, current);
}
