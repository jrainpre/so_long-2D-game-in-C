/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:43:58 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/03 09:39:27 by jrainpre         ###   ########.fr       */
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
	char		*temp;
	char		*buffer;
	ssize_t		r;

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

int	checkgrid_dimensions(char **grid)
{
	size_t i;
	size_t	l;
	size_t	j;
	
	i = 0;
	while (grid[i])
	{
		i++;
	}
	if (i < 3)
		return (0);
	l = ft_strlen(grid[i]);
	if (i < 3)
		return (0);
	i = 0;
	while (grid[i])
	{
		if (l != ft_strlen(grid[i]))
			return (0);
		i++;
	}
	return (1);
}

int	checkgrid_wall_rows(char **grid)
{
	size_t	i;
	size_t	l;
	size_t	j;
	
	i = 0;
	while (grid[i])
		i++;
	j = 0;
	while (grid[0][j])
	{
		if (grid[0][j] != '1')
			return (0);
		j++;
	}
	j = 0;
	while (grid[i][j])
	{
		if (grid[i][j] != '1')
			return (0);
		j++;
	}
	return(1);
}

int	checkgrid_wall_colls(char **grid)
{
	size_t	i;
	size_t	k;
	size_t	j;

	j = 0;
	while (grid[0][j])
		j++;
	i = 0;
	while (grid[i])
	{
		if (grid[i][0] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (grid[i])
	{
		if (grid[i][j] != '1')
			return (0);
		i++;
	}
	return (1);
}


int	main(void)
{
	int		fd;
	char	*line;
	int		i;
	int		y;
	int		x;
	int		x_start;
	int		y_start;
	char	**grid;
	char buf[2000];

	ssize_t		r	i = 0;
	while (grid[i])
	{
		if (grid[i][0] != '1')
			return (0);
		i++;
	};
	int	count_lines;

	fd = open("testgrid.txt", O_RDONLY);
	r = read(fd, buf, 100);
	i = 0;
	count_lines = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			count_lines++;
		i++;
	}
	close(fd);
	grid = (char **)malloc((count_lines + 1) * sizeof(char *));
	open("testgrid.txt", O_RDONLY);
	line = get_next_line(fd);
	y = 0;
	while (line)
	{
		grid[y] = ft_strtrim((const char *)line, "\n");
		free(line);
		line = get_next_line(fd);
		y++;
	}
	y = 0;
	while(grid[y])
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
	

		y = 0;
	while(grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == 'P')
			{
				x_start = x;
				y_start = y;
			}
				x++;
		}
			y++;
	}
	i = search(x_start, y_start, grid);
		write(1, "\n", 1);
 	y = 0;
	while(grid[y])
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