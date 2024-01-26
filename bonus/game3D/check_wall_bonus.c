/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:40:52 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/26 15:42:22 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	map_wall(double x, double y, t_map *map)
{
	double	mapgridindexx;
	double	mapgridindexy;

	if (x < 0 || x > map->width * TILE_SIZE
		|| y < 0 || y > map->height * TILE_SIZE)
		return (1);
	mapgridindexx = (int)floor((double)x / (double)TILE_SIZE);
	mapgridindexy = (int)floor((double)y / (double)TILE_SIZE);
	if (!map->map1[(int)mapgridindexy]
		|| map->map1[(int)mapgridindexy][(int)mapgridindexx] == '1'
		|| map->map1[(int)mapgridindexy][(int)mapgridindexx] == 'D')
		return (1);
	return (0);
}
