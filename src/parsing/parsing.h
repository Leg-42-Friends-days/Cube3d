/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:25:31 by mickzhan          #+#    #+#             */
/*   Updated: 2026/04/21 11:51:38 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../cub3d.h"

typedef struct s_textures
{
	char				*target;
	char				*path;
	struct s_textures	*next;
	struct s_textures	*prev;
}						t_textures;

typedef struct s_colors
{
	char				*target;
	int					color;
	struct s_colors		*next;
	struct s_colors		*prev;
}						t_colors;

typedef struct s_map
{
	char				**map;
	int					width;
	int					height;
}						t_map;

#endif