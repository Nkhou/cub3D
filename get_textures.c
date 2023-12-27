/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:54:31 by saboulal          #+#    #+#             */
/*   Updated: 2023/12/27 17:00:47 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int ft_texture(t_map *map,int x,int y)
{
    init_map(map);
    map->img = mlx_png_file_to_image(map->mlx,map->North,&map->width,&map->height);
    return(0);
}