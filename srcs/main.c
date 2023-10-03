/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrainpre <jrainpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:34:31 by jrainpre          #+#    #+#             */
/*   Updated: 2022/11/10 11:56:58 by jrainpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		error_only("argumnt is not valid");
	get_grid(&map, argv[1]);
	checkgrid(&map, argv[1]);
	open_window(&map);
	render_graphics(&map);
	put_map(&map);
	mlx_key_hook(map.win.win, key_hook, &map);
	mlx_hook(map.win.win, 17, 0, free_exit, &map);
	mlx_loop(map.win.mlx);
	free_grid(map.grid);
}
