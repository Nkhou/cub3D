/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:19:04 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/26 13:05:36 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"
// void ft_exit(void)
// {
//    system("leaks cub3D");
// }
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
	free_programme(map.str, map);
	return (0);
}
