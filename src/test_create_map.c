/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_create_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 15:42:00 by ibrouin-          #+#    #+#             */
/*   Updated: 2026/04/22 15:45:32 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void    create_map(t_global *global, char *str)
{
    int     fd;
    char    *line;


    fd = open(str, O_RONLY);
    line = get_next_line(fd);
    if (!line)
        return ;
    malloc(global->map->map[i])
    global->map->map[i]

}
