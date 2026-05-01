/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 10:45:04 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/01 11:35:17 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void    print_wall(t_raycast_data *data, t_global *global, int x)
{
	int line_height;
	int	draw_start;
	int	draw_end;

	(void)global;
	(void)x;
	line_height = SCREEN_HEIGHT / data->perp_wall_dist;
	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	print_line(global, draw_start, draw_end, x);
}

void    print_line(t_global *global, int draw_start, int draw_end, int x)
{
	int current;

	current = draw_start;
	while(current < draw_end)
	{
		put_pixel(global, x, current, 0xFF9900);
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
