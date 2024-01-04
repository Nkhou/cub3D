/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:54:31 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/04 15:45:11 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int ft_texture(t_map *map)
{
   init_map(map);
   while(map->map[map->i])
   { 
      map->texture = mlx_load_png(map->South);
      map->texture = mlx_load_png(map->West);
      map->texture = mlx_load_png(map->East);
      map->texture = mlx_load_png(map->North);
      map->texture = mlx_load_png(map->Floor);
      map->texture = mlx_load_png(map->Ceiling);
      map->i++;
    }
    return(0);
}  

// int put_pixel_by_pixel(t_map *map)
// {
//     init_map(map);
//     printf("map->map[map->i] = %s\n",map->map[map->i]);
//     exit(0);
//     while(map->map[map->i])
//     {
//         map->j = 0;
//         while(map->map[map->i][map->j])
//         {
//             if(map->map[map->i][map->j] == '1')
//             {
//                 map->x = map->j * map->tile_size;
//                 map->y = map->i * map->tile_size;
//                 map->texture = mlx_load_png(map->South);
//                 mlx_image_to_window(map->mlx, map->img, map->i, map->j);
//             }
//             map->j++;
//         }
//         map->i++;
//     }
// }