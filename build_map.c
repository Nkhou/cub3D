/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:01:04 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/22 19:23:23 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
// void build(void *mlx)
// {
//     t_map *map;
//     map = mlx;

//     map->map3d.color = malloc(sizeof(int *) * (int)HEIGHT * (int)WIDTH);
//     if (!map->map3d)
//         ft_error("malloc failed");
//     int i = 0;
//     int j = 0;
//     while (i < WIDTH)
//     {
//         j = 0;
//         while (j < HEIGHT)
//         {
//             map->map3d[WIDTH * j + x] = 0xFF00000;
//             j++;
//         }
//         i++;
//     }
// }