/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_solutions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:22:59 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/09 15:58:00 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	search(int x, int y, char **grid)
{
	if (grid[y][x] == 'E')
		return (1);
	if (grid[y][x] == '0' || grid[y][x] == 'C' || grid[y][x] == 'P')
	{
		grid[y][x] = 'x';
		if (search(x - 1, y, grid) || search(x, y + 1, grid) || \
			search(x + 1, y, grid) || search(x, y - 1, grid))
		{
			grid[y][x] = 'x';
			return (1);
		}
	}
	return (0);
}

int	checkgrid_soluitions(t_map *map)
{
	char	**gridcpy;
	int		result;

	result = 0;
	gridcpy = copygrid(map);
	result = search(map->player.x, map->player.y, gridcpy);
	free_grid(gridcpy);
	if (result == 1)
		return (1);
	return (0);
}
