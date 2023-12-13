/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drow_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:10:35 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/12/13 18:17:50 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
void trace_carre(t_map map, int x, int y, int color)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < 32)
    {
        while (j < 32)
        {
            mlx_pixel_put(map.mlx, map.win, x + i, y + j, color);
            j++;
        }
        j = 0;
        i++;
    }
}
void inisti_window(t_map map)
{
    int i;
    int j;
    int k;

    i = map.start;
    j = 0;
    k = 0;
    map.mlx = mlx_init();
    map.win = mlx_new_window(map.mlx, map.width, map.height, "cub3D");
    while (map.map[i])
    {
        while(map.map[i][j])
        {
            if(map.map[i][j] == '1')
            {
                trace_carre(map, j * 32, k * 32, 0xFFFFFF);
            }
            else if (map.map[i][j] == '0') 
            {
                trace_carre(map, j * 32, k * 32, 0x000000);
            }
            j++;
        }
        k++;
        j = 0;
        i++;
    }
    mlx_loop(map.mlx);
}
void map_draw(t_map map)
{
    inisti_window(map);
    // mlx_hook(map.win, 2, 1L<<0, key_press, &map);
    // mlx_hook(map.win, 3, 1L<<1, key_release, &map);
}