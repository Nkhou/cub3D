/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:54:31 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/19 15:00:30 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


int rgb_to_int(int r, int g, int b,int a)
{
    return (r << 24 | g << 16 | b << 8  | a);
}


int pixels_color_rgb(mlx_texture_t *p,u_int32_t x,u_int32_t y)
{
    int color;
    int i;
    if(x >= 0 && x < p->width && y >= 0 && y < p->height)
    {
        i = (y * p->width + x) * p->bytes_per_pixel;
        color = rgb_to_int(p->pixels[i],p->pixels[i + 1],p->pixels[i + 2],p->pixels[i + 3]);
    }
    else
        color = rgb_to_int(0,0,0,255);
    return(color);
}
