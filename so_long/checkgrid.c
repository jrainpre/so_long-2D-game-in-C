/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkgrid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:22:59 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/07 15:39:09 by jrainpre         ###   ########.fr       */
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
		return (0);
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

int checkgrid_filename(char *filename)
{
    size_t length_xend;

    length_xend = ft_strlen(filename) - 4;
    if(ft_strncmp(&filename[length_xend], ".ber", 4) != 0)
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
				map->start_pos.x = x;
				map->start_pos.y = y;
			}
			x++;
		}
		y++;
	}
	if (count == 1)
		return (1);
	return (0);
}

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

int	search(int x, int y, char **grid)
{
	if (grid[y][x] == 'E')
		return (1);
	if (grid[y][x] == '0' || grid[y][x] == 'C' || grid[y][x] == 'P')
	{
		grid[y][x] = 'x';
		if (search(x - 1, y, grid) || search(x, y + 1, grid) ||
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
	result = search(map->start_pos.x, map->start_pos.y, gridcpy);
	print_grid(gridcpy);
	free_grid(gridcpy);
	if (result == 1)
		return (1);
	return (0);
}

int	error_msg_map(char *msg, t_map *map)
{
	free_grid(map->grid);
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(msg, 2);
	exit(0);
	return (0);
}

void	checkgrid(t_map *map, char *filename)
{
	if(!checkgrid_filename(filename))
		error_msg_map("Filename not correct. Please check filename.", map);
	if(!checkgrid_dimensions(map))
		error_msg_map("Dimensions are not ok. Please check map", map);
	if(!checkgrid_wall_rows(map))
		error_msg_map("Map is not surrounded by walls. Please check the map.", map);
	if(!checkgrid_wall_colls(map))
			error_msg_map("Map is not surrounded by walls. Please check the map.", map);
	if(!checkgrid_start(map))
			error_msg_map("The map has more then one or no start position. Please check the map.", map);
	if(!checkgrid_exit(map))
			error_msg_map("There is no or more then one exit. Please check the map.", map);
	if(!checkgrid_collects(map))
		error_msg_map("Map is not surrounded by walls. Please check the map.", map);
	if(!checkgrid_soluitions(map))
		error_msg_map("The input map is not sloveable. Please check the map.", map);
}

int	main(void)
{
	t_map	map;

	ft_strlen("sadfgasdf");
	get_grid(&map, "map.ber");
	print_grid(map.grid);
	checkgrid(&map, "map.ber");

	open_window(&map);
	render_graphics(&map);
	put_map(&map);
	
	free_grid(map.grid);
}
