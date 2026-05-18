/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 17:57:49 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/18 17:11:33 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	map_width_height(t_global *global, char *map_content)
{
	global->map.height = get_height_map(map_content);
	if (global->map.height < 0)
		return (error_exit(global));
	global->map.height -= global->textures->start;
	global->map.width = get_width_map(global->map.mapou);
}

bool	start_map(t_global *global, char *map_content)
{
	int	map_len;

	map_len = map_start(global, map_content);
	if (map_len == 0)
		return (printf("Error\nMap doesnt exist\n"), error_exit(global), true);
	global->map.mapou = malloc(sizeof(char *) * (map_len + 1));
	if (!global->map.mapou)
		return (true);
	map_index(global, map_content);
	if (!global->map.mapou)
		return (ft_printf(2, "Error\nMap\n"), error_exit(global), true);
	if (error_check(global->map.mapou, global) == 1)
		return (printf("Error\nInvalid map\n"), error_exit(global), true);
	if (check_mapline(global->map.mapou) == 1)
		return (ft_printf(2, "Error\nMap\n"), error_exit(global), true);
	map_width_height(global, map_content);
	if (build_fake_map(global))
		return (error_exit(global), true);
	if (build_true_map(global))
		return (error_exit(global), true);
	if (map_flood(global) == 1)
		return (ft_printf(2, "Error\nMap is open\n"), true);
	return (false);
}
