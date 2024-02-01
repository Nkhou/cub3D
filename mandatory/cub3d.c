/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:19:04 by saboulal          #+#    #+#             */
/*   Updated: 2024/02/01 11:10:33 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"
void ft_exit()
{
	system("leaks cub3D");
}
void check_input(void)
{
	if (TILE_SIZE != 64 || WIDTH != 1900
		|| HEIGHT != 1200 || NORTH != 0
		|| SOUTH != 1 || WEST != 2
		|| EAST != 3 || DOOR != 4)
		ft_error();
}
int	main(int argc, char **argv)
{
	t_map	map;

	atexit(ft_exit);
	ini_map(&map, argc);
	ft_extention(argv);
	init_infos(&map, argv);
	init_part_map(&map);  
	init_parse(&map);
	get_space_wall(map);
	map_draw(map);
	free_programme(&map);
	return (0);
}
