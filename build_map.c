/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:01:04 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/15 15:06:31 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
// void build(void *mlx)
// {
//     t_map *map;
//     map = mlx;

//     map->map3d.color = malloc(sizeof(int *) * (int)map->height * (int)map->width);
//     if (!map->map3d)
//         ft_error("malloc failed");
//     int i = 0;
//     int j = 0;
//     while (i < map->width)
//     {
//         j = 0;
//         while (j < map->height)
//         {
//             map->map3d[map->width * j + x] = 0xFF00000;
//             j++;
//         }
//         i++;
//     }
// }