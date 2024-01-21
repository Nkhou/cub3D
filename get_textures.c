/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:54:31 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/21 15:05:52 by saboulal         ###   ########.fr       */
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
double get_line_height(t_map *map,t_rend *rend)
{
    double line_height;
    // double distanceprojplane;
  
    // printf("rend->perpDistance = %f",rend->perpDistance);
    // exit(0);
    // distanceprojplane = (map->width / 2) / tan(FOV_ANGLE / 2);
    // perpDistance = map->player.rays[rend->i].distance * cos(map->player.rays[rend->i].rayA - map->player.rotationAngle);
    line_height = (map->size / rend->perpDistance) * rend->distanceprojplane;
    return(line_height);
}
void draw_line(t_map *map,t_rend *rend,int tex)
{
    double height;
    ray_t *ray;

    ray = NULL;
    height = get_line_height(map,rend);
    
    my_mlx_put_image_to_image(map,rend,ray,tex);
}
void draw_3d_line(t_map *map, t_rend *rend, ray_t *ray)
{
    (void)ray;
    if (map->player.rays->isv && map->player.rays->isr)
		draw_line(map, rend, EAST);
	else if (map->player.rays->isv && map->player.rays->isl)
		draw_line(map, rend, WEST);
	else if (!map->player.rays->isv && map->player.rays->isu)
		draw_line(map, rend, NORTH);
	else if (!map->player.rays->isv && map->player.rays->isd)
		draw_line(map, rend, SOUTH);
}

void  drawing_pix(t_map *map, t_rend *rend,ray_t *ray,double height,int tex)
{
    double	tile_x;
	double	tex_x;
	double	tex_y;
	double	y_start;
	double	y;
    (void)ray;
    y_start = rend->walltoppixel ;
    if (tex == NORTH || tex == SOUTH)
        tile_x = fmod(map->player.rays->wallHX, map->size);
    else 
        tile_x = fmod(map->player.rays->wallHY, map->size);
    tex_x = tile_x * (map->texture[tex]->width / map->size);
    y = y_start;
    while(rend->wallbottompixel)
    {
        if(rend->i >= 0 && rend->i < map->width && y >= 0 && y < map->height)
        {
            tex_y = (y - y_start) * (map->texture[tex]->height / height);
            mlx_put_pixel(map->img,rend->i,y,pixels_color_rgb(map->texture[tex],tex_x,tex_y));
        }
        y++;
    }
    
}