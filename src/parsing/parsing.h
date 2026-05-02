/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:25:31 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/02 15:24:07 by ibrouin-         ###   ########.fr       */
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
	char				**mapou;
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
bool					stock_checker(t_global *global);
bool					char_check(char ch);
bool					direction_check(char ch);
bool					error_check(char **str);
bool					map_check(t_global *global);
int						get_height_map(char *map);
int						get_width_map(char **mapou);
bool					check_mapline(char **map);
void					flood_fill(t_global *global, int x, int y);
int						map_flood(t_global *global);
bool					start_map(t_global *global, char *map_content);
t_global				*init_malloc(void);
void					free_texture(t_global *global);
void					add_map(t_global *global, char *line, int index);
void					map_index(t_global *global, char *map_content);
int						map_start(t_global *global, char *map_content);
void					convert_line3(t_global *global, char *line, int fd);
void					convert_line2(t_global *global, char *line, int fd);
void					convert_line(t_global *global, char *line, int fd);
void					convert_line4(t_global *global, char *line, int fd);
void					initiate_stock(t_global *global);
void					read_map(t_global *global, char *map_content);
void					free_all(t_global *global);
void					error_exit(t_global *global);
bool					line_check(char *str);

#endif