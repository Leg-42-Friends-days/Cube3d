/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickzhan <mickzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 15:23:04 by mickzhan          #+#    #+#             */
/*   Updated: 2026/05/18 14:58:53 by mickzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

typedef struct s_global	t_global;

int						image_initiator_1(t_global *global, int x_map,
							int y_map);
int						image_initiator_p(t_global *global, int x_map,
							int y_map);
int						image_initiator_0(t_global *global, int x_map,
							int y_map);
int						show_1(t_global *global);
int						show_0(t_global *global);
int						dessin(t_global *global);
void					add_tile(t_global *global);
int						show_d(t_global *global);
int						image_initiator_d(t_global *global, int x_map,
							int y_map);

#endif