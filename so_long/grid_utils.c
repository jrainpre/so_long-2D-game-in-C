/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:22:59 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/09 18:02:10 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**copygrid(t_map *map)
{
	char	**gridcpy;
	int		i;

	gridcpy = (char **)malloc((map->dim_y + 1) * sizeof(char *));
	if (!gridcpy)
		return (NULL);
	i = 0;
	while (i < map->dim_y)
	{
		gridcpy[i] = ft_strdup(map->grid[i]);
		i++;
	}
	gridcpy[i] = NULL;
	return (gridcpy);
}

int	free_exit(t_map *map)
{
	mlx_destroy_window(map->win.mlx, map->win.win);
	free_grid(map->grid);
	exit(0);
	return (0);
}

void	evaluate(t_map *map)
{
	if (map->collect_act == map->collect_count)
		ft_printf("You won!");
	else
		ft_printf("You lost!");
	free_exit(map);
}

int	error_msg_map(char *msg, t_map *map)
{
	free_grid(map->grid);
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(msg, 2);
	exit(0);
	return (0);
}

void	free_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	if (grid)
		free(grid);
}
