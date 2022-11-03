/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:00:59 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/02 17:34:11 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>


typedef struct s_positions
{
	int	x;
	int	y;
}t_pos;


typedef struct s_map
{
	char	**grid;
	int		dim_x;
	int		dim_y;
	int		collect_count;
	t_pos	start_pos;
 }t_map;

// # ifndef BUFFER_SIZE
// #  define BUFFER_SIZE BUFSIZ
// # endif

/* get_next_line.c */
char	*get_next_line(int fd);
void	readline(int fd, char **save);
char	*before_line_break(char *buf);
char	*after_line_beak(char *buf);
char	*ft_strdup(const char *s);
char	*ft_strcpy(char *dest, const char *src);
int		include_newline(char *s);
void	ft_free(char **s1, char **s2, char **s3);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);

#endif