/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderstuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:22:59 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/08 13:46:25 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// 65361 links
// 65363 rechts
// 65362 oben 
// 65364 unten

#include "so_long.h"

int key_hook(int key, t_map *map)
{
    ft_printf("%d\n", key);
	control_player(key, map);
    if (key == 65307)
    {
        mlx_destroy_window(map->window.mlx, map->window.win);
        exit(0);
    }
    return 0;
}

int new_pos(int next_y, int next_x, t_map *map)
{
	if (map->grid[next_y][next_x] == '1')
		return (0);
	if (map->grid[next_y][next_x] == 'C')
			map->collect_act++;
	map->grid[map->player.y][map->player.x] = '0';
	map->player.x = next_x;
	map->player.y = next_y;
	map->grid[map->player.y][map->player.x] = 'P';
	return(1);
}

void control_player(int key, t_map *map)
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
		map->window.mlx = mlx_init();
		map->window.win = mlx_new_window(map->window.mlx, map->dim_x * OFFSET, map->dim_y * OFFSET, "so_long");
}

void	render_graphics(t_map *map)
{
	int	hight;
	int width;
	
	map->graphics.wall= mlx_xpm_file_to_image(map->window.mlx, WALL, &hight, &width);
	map->graphics.path= mlx_xpm_file_to_image(map->window.mlx, PATH, &hight, &width);
	map->graphics.start= mlx_xpm_file_to_image(map->window.mlx, START, &hight, &width);
	map->graphics.player= mlx_xpm_file_to_image(map->window.mlx, PLAYER, &hight, &width);
	map->graphics.exit= mlx_xpm_file_to_image(map->window.mlx, END, &hight, &width);
	map->graphics.collec= mlx_xpm_file_to_image(map->window.mlx, COLLECTS, &hight, &width);
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
	return(graph);
}

void	put_map(t_map *map)
{
	int	i;
	int	j;
	int	offset_x;
	int offset_y;

	i = 0;
	while (map->grid[i])
	{
		j = 0;
		while(map->grid[i][j])
		{
			offset_y = i * OFFSET;
			offset_x = j * OFFSET;
			mlx_put_image_to_window(map->window.mlx, map->window.win, check_graphic(map, j, i), offset_x, offset_y);
			j++;
		}
		i++;
	}
}