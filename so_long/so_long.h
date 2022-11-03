/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:00:59 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/03 17:09:44 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define ERR_MSG "The provided map is invalid!"

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

int	get_linecount(char *filename);
int	fillgrid(t_map *map, char *filename);
int	get_grid(t_map *map, char *filename);
void	print_grid(char **grid);
void	free_grid(char **grid);
int	checkgrid_dimensions(t_map *map);
int	checkgrid_wall_colls(t_map *map);
int	checkgrid_wall_rows(t_map *map);
int checkgrid_start(t_map *map);
int checkgrid_exit(t_map *map);
int checkgrid_collects(t_map *map);
char **copygrid(t_map *map);
int search(int x, int y, char **grid);
void	checkgrid(t_map *map, char *filename);
int	checkgrid_solutions(t_map *map);



#endif