/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:54:31 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/08 11:13:36 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int ft_texture(t_map *map)
{
   init_map(map);
   while(map->map[map->i])
   { 
      map->texture = mlx_load_png(map->South);
      if(map->texture == NULL)
        ft_error();
      map->texture = mlx_load_png(map->West);
      if(map->texture == NULL)
        ft_error();
      map->texture = mlx_load_png(map->East);
      if(map->texture == NULL)
        ft_error();
      map->texture = mlx_load_png(map->North);
      if(map->texture == NULL)
        ft_error();
      map->i++;
    }
    free(map->texture);
    return(0);
}  
void display(t_map *map)
{
    init_map(map);
    while(map->map[map->i])
    {
         if(map->map[map->i][map->j] == '1')
        {
         map->img = mlx_texture_to_image(map->mlx, map->texture);
        }
        map->i++;
    }
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

int rgb_to_int(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

// int mlx_image_to_window(t_mlx *mlx, t_img *img, int x, int y)
// {
//     int i;
//     int j;
//     int color;

//     i = 0;
//     while (i < img->height)
//     {
//         j = 0;
//         while (j < img->width)
//         {
//             color = mlx_get_pixel(img, j, i);
//             mlx_pixel_put(mlx->mlx, mlx->win, x + j, y + i, color);
//             j++;
//         }
//         i++;
//     }
//     return (0);
// }