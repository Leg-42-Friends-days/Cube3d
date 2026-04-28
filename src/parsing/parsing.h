/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:25:31 by mickzhan          #+#    #+#             */
/*   Updated: 2026/04/24 15:24:50 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../cub3d.h"

typedef struct s_global	t_global;

typedef struct s_textures
{
	char				*north;
	char				*south;
	char				*west;
	char				*east;
	char				*floor;
	char				*ceiling;
	int					stock[6];
	int					start;
	int					end;
}						t_textures;

typedef struct s_map
{
	char				**mapy;
	char				**true_map;
	int					width;
	int					height;
}						t_map;

int						map_cub(char *str);
char					*is_space(char *str);
char					*copy_enter(char *str);
char					*texture_map(char *str);
char					*rgb_map(char *str);
bool					nothing_slash(char *line);
int						error_gestion(int ac, char **av);
bool				stock_checker(t_global *global);
void				convert_line3(t_global *global, char *line, int fd);
void				convert_line2(t_global *global, char *line, int fd);
void				convert_line(t_global *global, char *line, int fd);
void				initiate_stock(t_global *global);
void				read_map(t_global *global, char *map_content);
void				free_all(t_global *global);
void			error_exit(t_global *global);
bool				line_check(char *str);

#endif