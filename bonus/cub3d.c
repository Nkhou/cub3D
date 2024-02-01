/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:47:55 by saboulal          #+#    #+#             */
/*   Updated: 2024/02/01 12:48:07 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	check_input(void)
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
