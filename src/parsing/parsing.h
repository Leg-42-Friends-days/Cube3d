/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:25:31 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/11 16:50:52 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../cub3d.h"
# include <stdbool.h>

typedef struct s_global	t_global;

typedef struct s_textures
{
	char				*north;
	char				*south;
	char				*west;
	char				*east;
	char				*floor;
	char				*ceiling;
	char				*door;
	int					stock[9];
	int					bonus[3];
	int					start;
	int					end;
}						t_textures;

typedef struct s_map
{
	char				**mapou;
	char				**fake_map;
	int					width;
	int					height;
	int					wopen;
	int					limite;

}						t_map;

int						map_cub(char *str);
char					*is_space(char *str);
char					*copy_enter(char *str);
char					*texture_map(char *str);
char					*rgb_map(char *str);
bool					nothing_slash(char *line);
int						error_gestion(int ac, char **av);
bool					stock_checker(t_global *global);
bool					char_check(char ch, t_global *global);
bool					direction_check(char ch);
bool					error_check(char **str, t_global *global);
bool					map_check(t_global *global);
int						get_height_map(char *map);
int						get_width_map(char **mapou);
bool					check_mapline(char **map);
char					*reformat_line(char *line, int width);
void					free_fake_map(t_map *map);
bool					build_fake_map(t_global *global);
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
bool					line_check(char *str, t_global *global);
bool					check_if_alpha(char *str);
bool					rgb_checker(char *str);
bool					check_rgb(char *str);
void					free_map(t_global *global);
int						added_name(char *line, char *str);
bool					solo_reader(t_global *global, char *map_content,
							char *str);
void					add_bonus_map(t_global *global, char *str);
bool					bonus_reader(t_global *global, char *map_content,
							char *str);
bool					read_unique(t_global *global, char *map_content);
void					map_index2(t_global *global, int *fd);

#endif