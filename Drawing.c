/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:57:44 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/10 13:33:03 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void get_draw(t_map *map,int tex)
{
  double  y;
   
    y = 0;
    while(y < map->height)
    {
       if(tex == NORTH || tex == SOUTH)
        mlx_pixel_put(map->mlx, map->win, map->x, y, map->color);
        y++;
    }
    
}
