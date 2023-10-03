/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:22:59 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/10 11:52:49 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_linecount(char *filename)
{
	size_t	i;
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		error_only("File name is not valid.");
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	if (line)
		free(line);
	close(fd);
	return (i);
}

int	fillgrid(t_map *map, char *filename)
{
	size_t	i;
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		return (0);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		map->grid[i] = ft_strtrim((const char *)line, "\n");
		free(line);
		line = get_next_line(fd);
		i++;
	}
	map->grid[i] = NULL;
	if (line)
		free(line);
	close(fd);
	return (i);
}

int	get_grid(t_map *map, char *filename)
{
	int	linecount;

	linecount = get_linecount(filename);
	if (linecount < 0)
		return (-1);
	map->grid = (char **)malloc((linecount + 1) * sizeof(char *));
	if (fillgrid(map, filename) == -1)
		return (-1);
	return (1);
}

void	print_grid(char **grid)
{
	int	x;
	int	y;

	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			write(1, &grid[y][x], 1);
			x++;
		}
		y++;
		write(1, "\n", 1);
	}
}
