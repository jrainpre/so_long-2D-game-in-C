/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:00:59 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/08 15:29:05 by jrainpre         ###   ########.fr       */
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
typedef struct s_window
{
	void	*mlx;
	void	*win;
}t_win;

typedef struct s_positions
{
	int	x;
	int	y;
}t_pos;

typedef struct s_graphics
{
	void	*wall;
	void	*path;
	void	*start;
	void	*exit;
	void	*collec;
	void	*player;
}t_graphics;

typedef struct s_map
{
	char	**grid;
	int		dim_x;
	int		dim_y;
	int		collect_count;
	int		collect_act;
	int		move_count;
	t_pos	player;
	t_win	window; 
	t_graphics graphics;
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




#include "minilibx-linux/mlx.h"
#include "minilibx-linux/mlx_int.h"

#define WALL "wall.xpm"
#define PATH "path.xpm"
#define START "player.xpm"
#define END "exit.xpm"
#define COLLECTS "collect.xpm"
#define PLAYER "player.xpm"
#define OFFSET 50

void	open_window(t_map *map);
void	render_graphics(t_map *map);
void	*check_graphic(t_map *map, int x, int y);
void	put_map(t_map *map);
int		key_hook(int key, t_map *map);
void 	control_player(int key, t_map *map);
int 	new_pos(int next_y, int next_x, t_map *map);
void	free_exit(t_map *map);
void	evaluate(t_map *map);


#endif