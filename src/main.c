/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibrouin- <ibrouin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 16:50:04 by mickzhan          #+#    #+#             */
/*   Updated: 2026/04/29 17:14:14 by ibrouin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* char	*is_space(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
			return (str + i);
	}
	return (str);
}

char	*copy_enter(char *str)
{
	int		i;
	char	*cpy;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		i++;
	}
	cpy = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*texture_map(char *str)
{
	int		i;
	int		fd;
	char	*cpy;

	i = 0;
	while (str[i] == ' ')
		i++;
	cpy = copy_enter(str + i);
	if (!cpy)
		return (NULL);
	printf("%s\n", cpy);
	fd = open(cpy, O_RDONLY);
	printf("%d\n", fd);
	if (fd == -1)
		return (free(cpy), printf("Error\nFD"), exit(1), NULL);
	close(fd);
	return (cpy);
}

bool	nothing_slash(char *line)
{

}

void	convert_line2(t_global *global, char *line)
{
	if (ft_strncmp(is_space(line), "SO", 2) == 0)
	{
		if (global->textures->stock[2] == 1)
			return (printf("Error\nTo much SO"), exit(1));
		global->textures->stock[2] = 1;
		global->textures->south = texture_map(is_space(line) + 2);
	}
	else if (ft_strncmp(is_space(line), "EA", 2) == 0)
	{
		if (global->textures->stock[3] == 1)
			return (printf("Error\nTo much EA"), exit(1));
		global->textures->east = texture_map(is_space(line) + 2);
		global->textures->stock[3] = 1;
	}
	else
	{
		if (nothing_slash(line) == 1)
		
	}
}

void	convert_line(t_global *global, char *line)
{
	if (ft_strncmp(is_space(line), "NO", 2) == 0)
	{
		if (global->textures->stock[0] == 1)
			return (printf("Error\nTo much NO"), exit(1));
		global->textures->stock[0] = 1;
		global->textures->north = texture_map(is_space(line) + 2);
	}
	else if (ft_strncmp(is_space(line), "WE", 2) == 0)
	{
		if (global->textures->stock[1] == 1)
			return (printf("Error\nTo much WE"), exit(1));
		global->textures->stock[1] = 1;
		global->textures->west = texture_map(is_space(line) + 2);
	}
	else
		convert_line2(global, line);
}

void	read_map(t_global *global, char *map_content)
{
	int		fd;
	char	*line;

	fd = open(map_content, O_RDONLY);
	if (!fd)
		return (printf("Error\n"), exit(1));
	line = get_next_line(fd);
	while (line)
	{
		convert_line(global, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	printf("NORTH :%s\n", global->textures->north);
	printf("SOUTH : %s\n", global->textures->south);
	printf("WEST : %s\n", global->textures->west);
	printf("EAST : %s\n", global->textures->east);
	// printf("FLOOR: %s\n", global->textures->floor);
	// printf("CEILI : %s\n", global->textures->ceiling);
}

int	error_gestion(int ac, char **av)
{
	if (ac != 2)
		return (printf("Bad argument"), 1);
	if (map_cub(av[1]) == 1)
		return (printf("Bad map"), 1);
	return (0);
}

void	free_all(t_global *global)
{
	// free(global->t_textures->ceiling);
	// free(global->t_textures->floor);
	free(global->textures->north);
	free(global->textures->south);
	free(global->textures->west);
	free(global->textures->east);
	free(global->textures);
	free(global);
} */

int	main(int ac, char **av)
{
	t_global	*global;
	
	(void)ac;
	//if (error_gestion(ac, av) == 1)
	//	return (1);
	global = malloc(sizeof(t_global));
	//global->t_textures = malloc(sizeof(t_textures));
	create_map(&(global->map), av[1]);
	raycasting(global);
	global->mlx = mlx_init();
	if (!global->mlx)
		exit(1);
	global->win = mlx_new_window(global->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "42");
	global->img.img = mlx_new_image(global->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	global->img.addr = mlx_get_data_addr(global->img.img, &global->img.bits_per_pixel,
			&global->img.line_length, &global->img.endian);
	mlx_put_image_to_window(global->mlx, global->win, global->img.img, 0, 0);
	mlx_loop(global->mlx);
	//read_map(global, av[1]);
	//free_all(global);
	return (0);
}
