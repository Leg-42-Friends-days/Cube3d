/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 10:45:04 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/07 11:06:58 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

int	color_in_hexa(char *color)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(color);
	while(*color != ',')
		color ++;
	color ++;
	g = ft_atoi(color);
	while(*color != ',')
		color ++;
	color ++;
	b = ft_atoi(color);
	return (r << 16) | (g << 8) | b;
}

t_xpm	which_wall(t_raycast_data *data)
{
	if (data->side == 0)
	{
		if (data->ray_dir.x > 0)
			return (data->east);
        else
			return (data->west);
	}
    if (data->side == 1)
	{
		if (data->ray_dir.y < 0)
			return (data->south);
		else
			return (data->north);
	}
	return (data->north);
}

void	calcul_image_sens(t_raycast_data *data, double *wall_x)
{
	if (data->side == 0)
	{
		*wall_x = data->player.y + data->perp_wall_dist * data->ray_dir.y;
		if (data->ray_dir.x > 0)
			*wall_x = 1 - (*wall_x - floor(*wall_x));
        else
			*wall_x -= floor(*wall_x);
	}
    if (data->side == 1)
	{
		*wall_x = data->player.x + data->perp_wall_dist * data->ray_dir.x;
		if (data->ray_dir.y < 0)
			*wall_x = 1 - (*wall_x - floor(*wall_x));
		else
			*wall_x -= floor(*wall_x);
	}
}

void    print_wall(t_raycast_data *data, t_global *global, int x)
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
	print_line(global, data, x);
}

void    print_line(t_global *global, t_raycast_data *data, int x)
{
    int     current;
    int     color;
	t_xpm	wall;

	wall = which_wall(data);
    data->print.step = (double)wall.height / data->print.line_height;
    data->print.tex_pos = (data->print.draw_start - SCREEN_HEIGHT / 2 + data->print.line_height / 2) * data->print.step;
    current = 0;
	while (current < data->print.draw_start)
	{
		put_pixel(global, x, current, color_in_hexa(global->textures->ceiling));
		current ++;
	}
	while (current < data->print.draw_end)
    {
        data->print.tex_y = (int)data->print.tex_pos % wall.height;
        data->print.tex_pos += data->print.step;
        color = *(int *)(wall.data
                + data->print.tex_y * wall.line_len
                + data->print.tex_x * (wall.bpp / 8));
        put_pixel(global, x, current, color);
        current++;
    }
	while (current < SCREEN_HEIGHT)
	{
		put_pixel(global, x, current, color_in_hexa(global->textures->floor));
		current ++;
	}
}

void	put_pixel(t_global *global, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return ;
	dst = global->img.addr + (y * global->img.line_length
			+ x *(global->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
