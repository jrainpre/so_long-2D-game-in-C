/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:22:59 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/09 15:39:58 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
