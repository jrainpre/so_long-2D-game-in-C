/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderstuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:22:59 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/07 16:01:52 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
void	open_window(t_map *map)
{
		map->window.mlx = mlx_init();
		map->window.win = mlx_new_window(map->window.mlx, 1920, 1080, "so_long");

}

void	render_graphics(t_map *map)
{
	int	hight;
	int width;
	
	map->graphics.wall= mlx_xpm_file_to_image(map->window.mlx, WALL, &hight, &width);
	map->graphics.path= mlx_xpm_file_to_image(map->window.mlx, PATH, &hight, &width);
	map->graphics.start= mlx_xpm_file_to_image(map->window.mlx, START, &hight, &width);
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
		graph = map->graphics.path;
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
			mlx_loop(map->window.mlx);
}