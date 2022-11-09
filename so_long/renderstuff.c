/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderstuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:22:59 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/09 14:29:42 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_hook(int key, t_map *map)
{
	control_player(key, map);
	if (key == 65307)
	{
		free_grid(map->grid);
		mlx_destroy_window(map->win.mlx, map->win.win);
		exit(0);
	}
	return (0);
}

int	new_pos(int next_y, int next_x, t_map *map)
{
	if (map->grid[next_y][next_x] == '1')
		return (0);
	if (map->grid[next_y][next_x] == 'E')
	{
		ft_printf("You moved %d times.\n", ++map->move_count);
		evaluate(map);
	}
	if (map->grid[next_y][next_x] == 'C')
		map->collect_act++;
	map->grid[map->player.y][map->player.x] = '0';
	map->player.x = next_x;
	map->player.y = next_y;
	map->grid[map->player.y][map->player.x] = 'P';
	ft_printf("You moved %d times.\n", ++map->move_count);
	return (1);
}

void	control_player(int key, t_map *map)
{
	if (key == 65361 || key == 65362 || key == 65363 || key == 65364)
	{
		if (key == 65361)
			new_pos(map->player.y, map->player.x - 1, map);
		if (key == 65363)
			new_pos(map->player.y, map->player.x + 1, map);
		if (key == 65362)
			new_pos(map->player.y - 1, map->player.x, map);
		if (key == 65364)
			new_pos(map->player.y + 1, map->player.x, map);
		put_map(map);
		return ;
	}
}

void	open_window(t_map *map)
{
	map->win.mlx = mlx_init();
	map->win.win = mlx_new_window(WINDO);
	map->move_count = 0;
}

void	render_graphics(t_map *map)
{
	int	h;
	int	w;

	map->graphics.wall = mlx_xpm_file_to_image(map->win.mlx, WALL, &h, &w);
	map->graphics.path = mlx_xpm_file_to_image(map->win.mlx, PATH, &h, &w);
	map->graphics.start = mlx_xpm_file_to_image(map->win.mlx, START, &h, &w);
	map->graphics.player = mlx_xpm_file_to_image(map->win.mlx, PLAYER, &h, &w);
	map->graphics.exit = mlx_xpm_file_to_image(map->win.mlx, END, &h, &w);
	map->graphics.collec = mlx_xpm_file_to_image(map->win.mlx, COLLECT, &h, &w);
}

void	*check_graphic(t_map *map, int x, int y)
{
	void	*graph;

	if (map->grid[y][x] == '1')
		graph = map->graphics.wall;
	if (map->grid[y][x] == '0')
		graph = map->graphics.path;
	if (map->grid[y][x] == 'C')
		graph = map->graphics.collec;
	if (map->grid[y][x] == 'P')
		graph = map->graphics.start;
	if (map->grid[y][x] == 'E')
		graph = map->graphics.exit;
	return (graph);
}

void	put_map(t_map *map)
{
	int		i;
	int		j;
	int		x;
	int		y;
	void	*p;

	i = 0;
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			y = i * OFFSET;
			x = j * OFFSET;
			p = check_graphic(map, j, i);
			mlx_put_image_to_window(map->win.mlx, map->win.win, p, x, y);
			j++;
		}
		i++;
	}
}
