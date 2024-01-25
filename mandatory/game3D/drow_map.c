// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   dr_map.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/12/13 15:10:35 by nkhoudro          #+#    #+#             */
// /*   Updated: 2024/01/02 16:35:51 by nkhoudro         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../include/cub.h"


int draw_3d_line(t_map *map, int i)
{
    if (map->player.rays[i].content == 'D')
        return (DOOR);
    else if (map->player.rays[i].isv && map->player.rays[i].isr)
        return (EAST);
    else if (map->player.rays[i].isv && map->player.rays[i].isl)
        return (WEST);
    else if (!map->player.rays[i].isv && map->player.rays[i].isu)
        return (NORTH);
    else if (!map->player.rays[i].isv && map->player.rays[i].isd)
        return (SOUTH);
    return (-1);
}

void draw_c_f(t_map *map, int i)
{
    int j = 0;
    while (j < HEIGHT / 2)
    {
        mlx_put_pixel(map->img, i, j, rgb_to_int(map->ceil->r, map->ceil->g, map->ceil->b, 255));
        j++;
    }
    j = HEIGHT / 2;
    while (j < HEIGHT)
    {
        mlx_put_pixel(map->img, i, j, rgb_to_int(map->floor->r, map->floor->g, map->floor->b, 255));
        j++;
    }
}


void pp(t_map *map, int walltoppixel, int wallbottompixel, int i, double height)
{
    int text = draw_3d_line(map,i);

    if (text == -1)
        return ;
    double factor = (double)map->texture[text]->height / height;
    uint32_t	*arr = (u_int32_t *)map->texture[text]->pixels;
    double			xo = 0;

    if (text == NORTH || text == SOUTH)
        xo = (int)fmodf(map->player.rays[i].wallHX, TILE_SIZE);
    else
        xo = (int)fmodf(map->player.rays[i].wallHY, TILE_SIZE);
 
    double tex_x = xo * (map->texture[text]->width / TILE_SIZE);
    
    if (tex_x < 0)
        tex_x = 0;
	double			yo = (walltoppixel - (HEIGHT/2) + (height/2)) * factor;

    if (yo < 0)
        yo = 0;
    while (walltoppixel < wallbottompixel)
    {
        if (yo >= map->texture[text]->height)
            yo = map->texture[text]->height - 1;
        mlx_put_pixel(map->img, i, walltoppixel, arr[(int)yo * map->texture[text]->width + (int)tex_x]);
        yo += factor;
        walltoppixel++;
    }
    
}
void generate_3d_projection(t_map *map)
{
    int i;
    double wallstripheight;
    double distanceprojplane;
    double projwallheight;
    int walltoppixel;
    int wallbottompixel;
    double perpDistance;
    i = 0;
    while (i < WIDTH)
    {
        if (map->player.rays[i].distance == 0)
            map->player.rays[i].distance = 1;
        perpDistance = map->player.rays[i].distance 
        * cos(map->player.rays[i].rayA - map->player.rotationAngle);
        distanceprojplane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
        projwallheight = (TILE_SIZE / perpDistance) * distanceprojplane;
        wallstripheight = projwallheight;
        walltoppixel = (HEIGHT / 2) - (wallstripheight / 2);
        wallbottompixel = (HEIGHT / 2) + (wallstripheight / 2);
        if (walltoppixel < 0)
            walltoppixel = 0;
        if (wallbottompixel > HEIGHT)
            wallbottompixel = HEIGHT;
        draw_c_f(map, i);
        pp(map, walltoppixel, wallbottompixel, i, wallstripheight);
        i++;
    }
}
