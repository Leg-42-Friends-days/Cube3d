/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:56:24 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/14 14:52:08 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sprite_what_to_draw(t_sprite *sprite)
{
	sprite->draw_start.y = -sprite->sprite_height / 2 + SCREEN_HEIGHT / 2;
	if (sprite->draw_start.y < 0)
		sprite->draw_start.y = 0;
	sprite->draw_end.y = sprite->sprite_height / 2 + SCREEN_HEIGHT / 2;
	if (sprite->draw_end.y >= SCREEN_HEIGHT)
		sprite->draw_end.y = SCREEN_HEIGHT - 1;
	sprite->draw_start.x = -sprite->sprite_width / 2 + sprite->sprite_screen_x;
	if (sprite->draw_start.x < 0)
		sprite->draw_start.x = 0;
	sprite->draw_end.x = sprite->sprite_width / 2 + sprite->sprite_screen_x;
	if (sprite->draw_end.x >= SCREEN_WIDTH)
		sprite->draw_end.x = SCREEN_WIDTH - 1;
}

void	sprite_in_persp(t_sprite *sprite)
{
	sprite->sprite_screen_x = (SCREEN_WIDTH / 2) * (1 + sprite->camera.x / sprite->camera.y);
	sprite->sprite_height = abs((int)(SCREEN_HEIGHT / sprite->camera.y));
	sprite->sprite_width = abs((int)(SCREEN_HEIGHT / sprite->camera.y));
}

int	sprite_camera_position(t_sprite *sprite, t_raycast_data *data)
{
	double	inv_det;

	sprite->relative_sprite.x = sprite->sprite.x - data->player.x;
	sprite->relative_sprite.y = sprite->sprite.y - data->player.y;
	inv_det = 1.0 / (data->plane.x * data->dir.y - data->dir.x * data->plane.y);
	sprite->camera.x = inv_det * (data->dir.y * sprite->relative_sprite.x
			- data->dir.x * sprite->relative_sprite.y);
	sprite->camera.y = inv_det * (-data->plane.y * sprite->relative_sprite.x
			+ data->plane.x * sprite->relative_sprite.y);
	if (sprite->camera.y <= 0)
		return (1);
	return (0);
}

void	draw_y(t_sprite *sprite, t_global *global, int x)
{
	int		current;
	int		color;
	double	tex_pos_y;

	current = sprite->draw_start.y;
	while (current < sprite->draw_end.y)
	{
		tex_pos_y = (double)(current - sprite->draw_start.y) / sprite->sprite_height;
		sprite->tex_y = (int)(tex_pos_y * sprite->texture.height);
		color = *(int *)sprite->texture.data + (sprite->tex_y * sprite->texture.line_len
				+ sprite->tex_x * (sprite->texture.bpp / 8));
		if ((color & 0x00FFFFFF) != 0)
			put_pixel(global, x, current, color);
		current ++;
	}
}

void	draw_sprite(t_global *global, t_sprite *sprite, t_raycast_data *data)
{
	int		current;
	double	tex_pos_x;

	current = sprite->draw_start.x;
	while (current < sprite->draw_end.x)
	{
		if (current >= 0 && current < SCREEN_WIDTH && sprite->camera.y < data->perp_wall_buffer[current])
		{
			tex_pos_x = (double)(current - sprite->draw_start.x) / sprite->sprite_width;
			sprite->tex_x = (int)(tex_pos_x * sprite->texture.width);
			draw_y(sprite, global, current);
		}
		current ++;
	}
}

void	sprite(t_global *global)
{
	init_sprite(global);
	if (sprite_camera_position(&(global->sprite), &(global->raycast_data)))
		return ;
	sprite_in_persp(&(global->sprite));
	sprite_what_to_draw(&(global->sprite));
	draw_sprite(global, &(global->sprite), &(global->raycast_data));
}






/* void	draw_sprite(t_global *global)
{
	t_sprite	*s;
	int			stripe;
	int			y;
	int			tex_x;
	int			tex_y;
	int			color;
	double		tex_pos_x;
	double		tex_pos_y;

	s = &global->sprite;
	stripe = s->draw_start.x;
	while (stripe < s->draw_end.x)
	{
		tex_pos_x = (double)(stripe - s->draw_start.x)
			/ s->sprite_width;
		tex_x = (int)(tex_pos_x * s->texture.width);
		if (s->camera.y > 0
			&& stripe >= 0
			&& stripe < SCREEN_WIDTH
			&& s->camera.y < global->zbuffer[stripe])
		{
			y = s->draw_start.y;
			while (y < s->draw_end.y)
			{
				tex_pos_y = (double)(y - s->draw_start.y)
					/ s->sprite_height;
				tex_y = (int)(tex_pos_y * s->texture.height);
				color = get_pixel_color(
						&s->texture,
						tex_x,
						tex_y);
				if ((color & 0x00FFFFFF) != 0)
				{
					my_mlx_pixel_put(
						&global->img,
						stripe,
						y,
						color);
				}
				y++;
			}
		}
		stripe++;
	}
} */
/* 
int	get_pixel_color(t_texture *texture, int x, int y)
{
	char	*dst;

	if (!texture || !texture->addr)
		return (0);
	if (x < 0 || x >= texture->width
		|| y < 0 || y >= texture->height)
		return (0);
	dst = texture->addr
		+ (y * texture->line_length
		+ x * (texture->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
} */
 