/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 17:37:32 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/05/22 17:12:20 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sprite_what_to_draw(t_sprite *sprite)
{
	int	v_move;
	int	v_move_screen;

	v_move = 470;
	v_move_screen = (int)(v_move / sprite->camera.y);
	sprite->draw_start.y = -sprite->sprite_height / 2 + SCREEN_HEIGHT / 2
		+ v_move_screen;
	if (sprite->draw_start.y < 0)
		sprite->draw_start.y = 0;
	sprite->draw_end.y = sprite->draw_start.y + sprite->sprite_height;
	if (sprite->draw_end.y >= SCREEN_HEIGHT)
		sprite->draw_end.y = SCREEN_HEIGHT - 1;
	sprite->draw_start.x = -sprite->sprite_width / 2 + sprite->sprite_screen_x;
	sprite->draw_end.x = sprite->sprite_width / 2 + sprite->sprite_screen_x;
	if (sprite->draw_end.x >= SCREEN_WIDTH)
		sprite->draw_end.x = SCREEN_WIDTH - 1;
}

void	sprite_in_persp(t_sprite *sprite)
{
	sprite->sprite_screen_x = (SCREEN_WIDTH / 2) * (1 + sprite->camera.x
			/ sprite->camera.y);
	sprite->sprite_height = abs((int)(SCREEN_HEIGHT / sprite->camera.y / 2));
	sprite->sprite_width = abs((int)(SCREEN_HEIGHT / sprite->camera.y / 3));
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
	char	*dst;

	current = sprite->draw_start.y;
	while (current < sprite->draw_end.y)
	{
		tex_pos_y = (double)(current - sprite->draw_start.y)
			/ sprite->sprite_height;
		sprite->tex_y = (int)(tex_pos_y
				* sprite->anim.frame[sprite->anim.current_frame].height);
		dst = sprite->anim.frame[sprite->anim.current_frame].data
			+ (sprite->tex_y
				* sprite->anim.frame[sprite->anim.current_frame].line_len
				+ sprite->tex_x
				* (sprite->anim.frame[sprite->anim.current_frame].bpp / 8));
		color = *(unsigned int *)dst;
		if ((color & 0x00FFFFFF) != 0)
			put_pixel(global, x, current, color);
		current++;
	}
}

void	draw_sprite(t_global *global, t_sprite *sprite, t_raycast_data *data)
{
	int		current;
	double	tex_pos_x;

	(void)data;
	current = sprite->draw_start.x;
	while (current < sprite->draw_end.x)
	{
		if (current >= 0 && current < SCREEN_WIDTH && sprite->camera.y
			< data->perp_wall_buffer[current])
		{
			tex_pos_x = (double)(current - sprite->draw_start.x)
				/ sprite->sprite_width;
			sprite->tex_x = (int)(tex_pos_x
					* sprite->anim.frame[sprite->anim.current_frame].width);
			draw_y(sprite, global, current);
		}
		current ++;
	}
}
