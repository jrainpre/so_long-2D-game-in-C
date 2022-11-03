/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:00:59 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/01 14:52:06 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

/*
int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open("41_no_nl", O_RDONLY);
	while (i <2)
	{
		line = get_next_line(fd);
		printf("%s", line);
		i++;
		ft_free(&line, 0, 0);
	}
}
*/