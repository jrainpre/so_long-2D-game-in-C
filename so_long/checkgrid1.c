/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkgrid1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:22:59 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/09 14:59:31 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	checkgrid_filename(char *filename)
{
	size_t	length_xend;

	length_xend = ft_strlen(filename) - 4;
	if (ft_strncmp(&filename[length_xend], ".ber", 4) != 0)
		return (0);
	return (1);
}

int	checkgrid_dimensions(t_map *map)
{
	size_t	i;
	size_t	l;

	i = 0;
	while (map->grid[i])
	{
		i++;
	}
	if (i < 3)
		return (0);
	l = ft_strlen(map->grid[0]);
	if (l < 3)
		return (0);
	i = 0;
	while (map->grid[i])
	{
		if (l != ft_strlen(map->grid[i]))
			return (0);
		i++;
	}
	map->dim_y = i;
	map->dim_x = l;
	return (1);
}

int	checkgrid_wall_colls(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (map->grid[i])
		i++;
	while (map->grid[0][j])
	{
		if (map->grid[0][j] != '1')
			return (0);
		j++;
	}
	j = 0;
	while (map->grid[i - 1][j])
	{
		if (map->grid[i - 1][j] != '1')
			return (0);
		j++;
	}
	return (1);
}

int	checkgrid_wall_rows(t_map *map)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (map->grid[0][j])
		j++;
	i = 0;
	while (map->grid[i])
	{
		if (map->grid[i][0] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (map->grid[i])
	{
		if (map->grid[i][j - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	checkgrid_start(t_map *map)
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
			if (map->grid[y][x] == 'P')
			{
				count++;
				map->player.x = x;
				map->player.y = y;
			}
			x++;
		}
		y++;
	}
	if (count == 1)
		return (1);
	return (0);
}
