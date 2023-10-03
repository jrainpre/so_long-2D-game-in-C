/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkgrid2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:22:59 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/09 18:01:59 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	checkgrid_exit(t_map *map)
{
	int	count;
	int	x;
	int	y;

	count = 0;
	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == 'E')
				count++;
			x++;
		}
		y++;
	}
	if (count == 1)
		return (1);
	return (0);
}

int	checkgrid_collects(t_map *map)
{
	int	x;
	int	y;

	map->collect_count = 0;
	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == 'C')
				map->collect_count++;
			x++;
		}
		y++;
	}
	if (map->collect_count > 0)
		return (1);
	return (0);
}

int	checkgrid_chars(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (!(map->grid[y][x] == '1' || \
					map->grid[y][x] == '0' || \
					map->grid[y][x] == 'P' || \
					map->grid[y][x] == 'E' || \
					map->grid[y][x] == 'C' || \
					map->grid[y][x] == 'S'))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

void	checkgrid(t_map *map, char *filename)
{
	if (!checkgrid_filename(filename))
		error_msg_map(ERR_FILE, map);
	if (!checkgrid_dimensions(map))
		error_msg_map(ERR_DIM, map);
	if (!checkgrid_wall_rows(map))
		error_msg_map(ERR_WALL, map);
	if (!checkgrid_wall_colls(map))
		error_msg_map(ERR_WALL, map);
	if (!checkgrid_start(map))
		error_msg_map(ERR_START, map);
	if (!checkgrid_exit(map))
		error_msg_map(ERR_EXIT, map);
	if (!checkgrid_collects(map))
		error_msg_map(ERR_COLL, map);
	if (!checkgrid_soluitions(map))
		error_msg_map(ERR_SOL, map);
	if (!checkgrid_chars(map))
		error_msg_map(ERR_CHAR, map);
}
