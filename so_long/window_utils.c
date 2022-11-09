/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:22:59 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/09 18:01:32 by jrainpre         ###   ########.fr       */
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

void	open_window(t_map *map)
{
	int	x;
	int	y;

	x = map->dim_x * OFFSET;
	y = map->dim_y * OFFSET;
	map->win.mlx = mlx_init();
	map->win.win = mlx_new_window(map->win.mlx, x, y, "so_long");
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
