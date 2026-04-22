/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:25:31 by mickzhan          #+#    #+#             */
/*   Updated: 2026/04/22 17:34:46 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../cub3d.h"

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
}						t_textures;

typedef struct s_map
{
	char				**map;
	int					width;
	int					height;
}						t_map;

int	map_cub(char *str);
char	*is_space(char *str);
char	*copy_enter(char *str);
char	*texture_map(char *str);
char	*rgb_map(char *str);
bool	nothing_slash(char *line);
bool	stock_checker(struct s_global *global);
void	convert_line3(struct s_global *global, char *line);
void	convert_line2(struct s_global *global, char *line);
void	convert_line(struct s_global *global, char *line);
void	read_map(struct s_global *global, char *map_content);
int	error_gestion(int ac, char **av);
void	free_all(struct s_global *global);


#endif