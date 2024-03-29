/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:00:59 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/10 11:52:14 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_window
{
	void		*mlx;
	void		*win;
}				t_win;

typedef struct s_positions
{
	int			x;
	int			y;
}				t_pos;

typedef struct s_graphics
{
	void		*wall;
	void		*path;
	void		*start;
	void		*exit;
	void		*collec;
	void		*player;
}				t_graphics;

typedef struct s_map
{
	char		**grid;
	int			dim_x;
	int			dim_y;
	int			collect_count;
	int			collect_act;
	int			move_count;
	t_pos		player;
	t_win		win;
	t_graphics	graphics;
}				t_map;

# define ERR_MAP "The provided map is invalid!"
# define ERR_FILE "Filename not correct. Please check filename."
# define ERR_DIM "Dimensions are not ok. Please check map"
# define ERR_WALL "Map is not surrounded by walls. Please check the map."
# define ERR_START "The map has more then one or no start position."
# define ERR_COLL "There is no collectable on the map. Please check the map."
# define ERR_SOL "The input map is not sloveable. Please check the map."
# define ERR_EXIT "There is no or more then one exit. Please check the map."
# define ERR_CHAR "There are undefined characters on the map."
# define WALL "images/wall.xpm"
# define PATH "images/path.xpm"
# define START "images/player.xpm"
# define END "images/exit.xpm"
# define COLLECT "images/collect.xpm"
# define PLAYER "images/player.xpm"
# define OFFSET 50

int				get_linecount(char *filename);
int				fillgrid(t_map *map, char *filename);
int				get_grid(t_map *map, char *filename);
void			print_grid(char **grid);
void			free_grid(char **grid);
int				checkgrid_filename(char *filename);
int				checkgrid_dimensions(t_map *map);
int				checkgrid_wall_colls(t_map *map);
int				checkgrid_wall_rows(t_map *map);
int				checkgrid_start(t_map *map);
int				checkgrid_exit(t_map *map);
int				checkgrid_collects(t_map *map);
int				checkgrid_chars(t_map *map);
char			**copygrid(t_map *map);
int				search(int x, int y, char **grid);
int				checkgrid_soluitions(t_map *map);
int				error_msg_map(char *msg, t_map *map);
void			evaluate(t_map *map);
int				free_exit(t_map *map);
void			checkgrid(t_map *map, char *filename);
int				key_hook(int key, t_map *map);
int				new_pos(int next_y, int next_x, t_map *map);
void			control_player(int key, t_map *map);
void			open_window(t_map *map);
void			render_graphics(t_map *map);
void			*check_graphic(t_map *map, int x, int y);
void			put_map(t_map *map);
int				error_only(char *msg);

#endif