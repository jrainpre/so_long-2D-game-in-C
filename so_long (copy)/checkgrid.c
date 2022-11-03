/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkgrid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:22:59 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/03 11:18:58 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_check_set(char c, const char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_find_start(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] && ft_check_set(s1[i], set))
		i++;
	return (i);
}

static int	ft_find_end(char const *s1, char const *set)
{
	int	i;
	int	len;

	len = ft_strlen(s1) - 1;
	i = len;
	while (s1[i] && i >= 0 && ft_check_set(s1[i], set))
		i--;
	return (i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*p;

	if (!s1)
		return (NULL);
	start = ft_find_start(s1, set);
	end = ft_find_end(s1, set);
	if (start >= end)
	{
		p = malloc(1);
		if (p == NULL)
			return (NULL);
		p[0] = '\0';
		return (p);
	}
	p = malloc(end - start + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (start < end)
		p[i++] = s1[start++];
	p[i] = '\0';
	return (p);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	j = -1;
	while (s1[++j])
		p[i++] = s1[j];
	j = -1;
	while (s2[++j])
		p[i++] = s2[j];
	p[i] = '\0';
	return (&p[0]);
}

int	include_newline(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (&dest[0]);
}

char	*ft_strdup(const char *s)
{
	char	*p;

	if (!s)
	{
		p = malloc(1);
		p[0] = '\0';
		return (p);
	}
	p = malloc(ft_strlen(s) + 1);
	if (p == NULL)
		return (0);
	return (ft_strcpy(p, s));
}

void	ft_free(char **s1, char **s2, char **s3)
{
	if (s1 && *s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (s2 && *s2)
	{
		free(*s2);
		*s2 = NULL;
	}
	if (s3 && *s3)
	{
		free(*s3);
		*s3 = NULL;
	}
}

char	*after_line_beak(char *buf)
{
	int		i;
	int		j;
	char	*after;

	j = 0;
	while (buf[j])
		j++;
	i = 0;
	while (buf[i] && !(buf[i] == '\n' || buf[i] == '\0'))
		i++;
	if (buf[i] == '\n')
		i++;
	after = malloc(sizeof(char) * (j - i + 1));
	if (after == NULL)
		return (NULL);
	j = 0;
	while (buf[i])
	{
		after[j] = buf[i];
		i++;
		j++;
	}
	after[j] = '\0';
	return (after);
}

char	*before_line_break(char *buf)
{
	int		i;
	char	*before;

	i = 0;
	while (buf[i] && !(buf[i] == '\n' || buf[i] == '\0'))
		i++;
	if (buf[i] == '\n')
		i++;
	before = malloc(sizeof(char) * (i + 1));
	if (before == NULL)
		return (NULL);
	i = 0;
	while (buf[i] && !(buf[i] == '\n' || buf[i] == '\0'))
	{
		before[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
	{
		before[i] = buf[i];
		i++;
	}
	before[i] = '\0';
	return (before);
}

void	readline(int fd, char **save)
{
	char	*temp;
	char	*buffer;
	ssize_t	r;

	buffer = malloc(sizeof(char) * 5 + 1);
	if (buffer == NULL)
		return ;
	r = 1;
	while (r > 0)
	{
		r = read(fd, buffer, 5);
		if (r == -1)
		{
			ft_free(save, &buffer, 0);
			return ;
		}
		temp = ft_strdup(*save);
		ft_free(save, 0, 0);
		buffer[r] = '\0';
		*save = ft_strjoin(temp, buffer);
		ft_free(&temp, 0, 0);
		if (include_newline(*save))
			break ;
	}
	ft_free(&buffer, 0, 0);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;
	char		*temp;

	if (fd < 0 || 5 <= 0)
		return (NULL);
	line = NULL;
	readline(fd, &save);
	if (save != NULL && *save != '\0')
	{
		temp = ft_strdup(save);
		ft_free(&save, 0, 0);
		save = after_line_beak(temp);
		line = before_line_break(temp);
		ft_free(&temp, 0, 0);
	}
	if (!line || *line == '\0')
	{
		ft_free(&save, &line, 0);
		return (NULL);
	}
	return (line);
}

//-------------------------------------------------------------------

int			get_grid(t_map *map, char *filename);

int	get_linecount(char *filename)
{
	size_t	i;
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		return (-1);
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
		return (-1);
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
	free(grid);
}

int	checkgrid_dimensions(t_map *map)
{
	size_t	i;
	size_t	l;
	size_t	j;

	i = 0;
	while (map->grid[i])
	{
		i++;
	}
	if (i < 3)
		return (-1);
	l = ft_strlen(map->grid[0]);
	if (l < 3)
		return (-1);
	i = 0;
	while (map->grid[i])
	{
		if (l != ft_strlen(map->grid[i]))
			return (-1);
		i++;
	}
	map->dim_y = i;
	map->dim_x = l;
	return (1);
}

int	checkgrid_wall_colls(t_map *map)
{
	size_t i;
	size_t j;
	
	i = 0;
	while (map->grid[i])
		i++;
	 while (map->grid[0][j])
		{
			if (map->grid[0][j] != '1')
			return (-1);
			j++;
		}
	j = 0;
	while (map->grid[i - 1][j])
	{
		if (map->grid[i - 1][j] != '1')
			return (-1);
		j++;
	}
	return (1);
}

int	checkgrid_wall_rows(t_map *map)
{
	size_t i;
	size_t j;

	j = 0;
	while (map->grid[0][j])
		j++;
	i = 0;
	while (map->grid[i])
	{
		if (map->grid[i][0] != '1')
			return (-1);
		i++;
	}
	i = 0;
	while (map->grid[i])
	{
		if (map->grid[i][j - 1] != '1')
			return (-1);
		i++;
	}
	return (1);
}
	
int checkgrid_start(t_map *map)
	{
		int count;
		int x;
		int y;

		count == 0;
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
		return (-1);
	}

	int checkgrid_exit(t_map * map)
	{
		int count;
		int x;
		int y;

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
		return (-1);
	}

	int checkgrid_collects(t_map * map)
	{
		int count;
		int x;
		int y;

		count == 0;
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
		return (-1);
	}

	char **copygrid(t_map *map)
	{
		char **gridcpy;
		int		i;

		gridcpy = (char **)malloc(map->dim_y * sizeof(char*));
		if (!gridcpy)
			return (NULL);
		i = 0;
		while (i < map->dim_y)
		{
			gridcpy[i] = ft_strdup(map->grid[i]);
			i++;
		}
		gridcpy[i] = NULL;
		return(gridcpy);
	}

int search(int x, int y, char **grid)
{
	if (grid[y][x] == 'E') 
		return (1);
	if (grid[y][x] == '0' || grid[y][x] == 'C' || grid[y][x] == 'P')
	{
		grid[y][x] = 'x';
		if (search(x - 1, y, grid))
		{	
			grid[y][x] = 'x';
			return (1);
		}
		if (search(x, y + 1, grid))
		{	
			grid[y][x] = 'x';
			return (1);
		}
		if (search(x + 1, y, grid))
		{	
			grid[y][x] = 'x';
			return (1);
		}	
		if (search(x, y - 1, grid))
		{	
			grid[y][x] = 'x';
			return (1);
		}
	}
	return (0);
}

	int dfs(t_map *map)
	{
		char **gridcpy;
		int result;

		result = 0;
		gridcpy = copygrid(map);
		result = search(map->start_pos.x, map->start_pos.y, gridcpy);
		/*print_grid(gridcpy);*/
		free_grid(gridcpy);
		if (result == 1)
			return (1);
		return(-1);
	}

	int checkgrid(t_map *map)
	{
		int checksum;
		
		checksum = 0;
		checksum += checkgrid_dimensions(map);
		checksum += checkgrid_wall_rows(map);
		checksum +=checkgrid_wall_colls(map);
		checksum += checkgrid_start(map);
		checksum += checkgrid_exit(map);
		checksum += checkgrid_collects(map);
		checksum += dfs(map);
		if (checksum == 7)
			return (1);
		return (0);
		
	}

	int main()
	{
		t_map map;
		get_grid(&map, "testgrid.txt");
		print_grid(map.grid);
		checkgrid(&map);

		free_grid(map.grid);
	}