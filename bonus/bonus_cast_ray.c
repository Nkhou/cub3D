/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cast_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:01:29 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/24 14:28:59 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"
t_hv horz_(t_map *map, double ra, t_direction direction)
{
    double xintercept; // x and y intercept of the wall
    double yintercept;
    double xstep;
    double ystep;
    int foundhorzwallhit;
    double horzwallhitx;
    double horzwallhity;
    double horzWllcontent;
    double nextHorzTouchX;
    double nextHorzTouchY;
    double xtocheck;
    double ytocheck;
    t_hv horz;
 //need to check if ray is up or down*****
    // ra = fix_angle(ra);
    direction.up = israyfacingup(ra);
    direction.down = !direction.up;
    direction.right = israyfacingright(ra);
    direction.left = !direction.right;
    horzwallhitx = 0;
    horzwallhity = 0;
    foundhorzwallhit = 0;
    horzWllcontent = 0;
    yintercept = floor(map->player.y / TILE_SIZE) * TILE_SIZE;
    if (direction.down) // looking down
    {
        yintercept += TILE_SIZE;
    }
    xintercept = map->player.x + (yintercept - map->player.y) / tan(ra);
    ystep = TILE_SIZE;
    if (direction.up) // looking up
        ystep *= -1;
    xstep = TILE_SIZE / tan(ra);
    if (direction.left && xstep > 0) // looking left
        xstep *= -1;
    if (direction.right && xstep < 0) // looking right
        xstep *= -1;
    nextHorzTouchX = xintercept;
    nextHorzTouchY = yintercept;
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= map->width * TILE_SIZE && nextHorzTouchY >= 0 && nextHorzTouchY <= map->height * TILE_SIZE)
    {
        xtocheck = floor(nextHorzTouchX);
        if (direction.up)
            ytocheck = floor(nextHorzTouchY - 1);
        else
            ytocheck = floor(nextHorzTouchY + 1);
        // ytocheck = floor(nextHorzTouchY + (direction.up ? -1 : 0));
        if (xtocheck < 0 || xtocheck > map->width * TILE_SIZE || ytocheck < 0 || ytocheck > map->height * TILE_SIZE)
            break;
        if (map_wall(xtocheck, ytocheck, map))
        {
            foundhorzwallhit = 1;
            horzwallhitx = nextHorzTouchX;
            horzwallhity = nextHorzTouchY;
            // horzWllcontent = (int)map->map[(int)floor(ytocheck /TILE_SIZE + map->start)][(int)floor(xtocheck /TILE_SIZE)];
            break;
        }
        else
        {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }
    // printf("%d\n", map->player.y < horzwallhity ? 1 : 0);
    horz.wallhitx = horzwallhitx;
    horz.wallhity = horzwallhity;
    horz.content = horzWllcontent;
    horz.fhwh = foundhorzwallhit;
    return (horz);
}
// t_hv findwallv(double nextvertTouchX, double nextvertTouchY, t_map *map, t_direction direction, t_step step)
// {
//     double xtocheck;
//     double ytocheck;
//     t_hv vert;

//     while (nextvertTouchX >= 0 && nextvertTouchX <= map->width && nextvertTouchY >= 0 && nextvertTouchY <= map->height)
//     {
//         xtocheck = nextvertTouchX + (direction.left ? -1 : 0);
//         ytocheck = nextvertTouchY;
//         if (map_wall(xtocheck, ytocheck, map))
//         {
//             vert.fhwv = 1;
//             vert.wallhitx = nextvertTouchX;
//             vert.wallhity = nextvertTouchY;
//             vert.content = (int)map->map[(int)((ytocheck /TILE_SIZE) + map->start)][(int)(xtocheck /TILE_SIZE)];
//             break;
//         }
//         else
//         {
//             nextvertTouchX += step.xstep;
//             nextvertTouchY += step.ystep;
//         }
//     }
//     return (vert);
// }
t_hv incrver(double x, double y, t_map *map, t_direction direction, double ra)
{
    double nextvertTouchX;
    double nextvertTouchY;
    double xtocheck;
    double ytocheck;
    t_step step;
    t_hv vert;

    vert.fhwv= 0;
    vert.wallhitx = 0;
    vert.wallhity = 0;
    vert.content = 0;
    step.xstep = TILE_SIZE;
    if (direction.left) 
        step.xstep *= -1;
    step.ystep = TILE_SIZE * tan(ra);
    if (direction.up && step.ystep > 0)
        step.ystep *= -1;
    if (direction.down && step.ystep < 0)
        step.ystep *= -1;
    nextvertTouchX = x;
    nextvertTouchY = y;
    // findwallv(x, y, map, direction, step);
    while (nextvertTouchX >= 0 && nextvertTouchX <= map->width * TILE_SIZE && nextvertTouchY >= 0 && nextvertTouchY <= map->height * TILE_SIZE)
    {
        // xtocheck = floor(nextvertTouchX + (direction.left ? -1 : 0));
        if (direction.left)
            xtocheck = floor(nextvertTouchX - 1);
        else
            xtocheck = floor(nextvertTouchX + 1);
        ytocheck = floor(nextvertTouchY);
        if (xtocheck < 0 || xtocheck > map->width * TILE_SIZE || ytocheck < 0 || ytocheck > map->height * TILE_SIZE)
            break;
        if (map_wall(xtocheck, ytocheck, map))
        {
            vert.fhwv = 1;
            vert.wallhitx = nextvertTouchX;
            vert.wallhity = nextvertTouchY;
            // vert.content = (int)map->map[(int)((ytocheck /TILE_SIZE) + map->start)][(int)(xtocheck /TILE_SIZE)];
            break;
        }
        else if (direction.left && map_wall(xtocheck + 1, ytocheck, map))
        {
            vert.fhwv = 1;
            vert.wallhitx = nextvertTouchX;
            vert.wallhity = nextvertTouchY;
            // vert.content = (int)map->map[(int)((ytocheck /TILE_SIZE) + map->start)][(int)(xtocheck /TILE_SIZE)];
            break;
        }
        else
        {
            nextvertTouchX += step.xstep;
            nextvertTouchY += step.ystep;
        }
        // else
        // {
        //     nextvertTouchX += step.xstep;
        //     nextvertTouchY += step.ystep;
        // }
    }
    return (vert);
}
t_hv vert_(t_map *map, double ra, t_direction direction)
{
    double xintercept; // x and y intercept of the wall
    double yintercept;
    t_hv vert;

    xintercept = floor(map->player.x / TILE_SIZE) * TILE_SIZE;
    if (direction.right) // looking right
        xintercept += TILE_SIZE;
    yintercept = map->player.y + (xintercept - map->player.x) * tan(ra);
    vert = incrver(xintercept, yintercept, map, direction, ra);
    return (vert);
}
void castr(t_map *map, double ra, int i)
{
    t_direction direction;
    t_hv horz;
    double horzhitdistance;
    double verthitdistance;
    t_hv vert;
    ra = fix_angle(ra);
    direction.up = israyfacingup(ra);
    direction.down = !direction.up;
    direction.right = israyfacingright(ra);
    direction.left = !direction.right;
    horz = horz_(map, ra, direction);
    vert = vert_(map, ra, direction);
    horzhitdistance = (horz.fhwh) ? distance_between_points(map->player.x, map->player.y, horz.wallhitx, horz.wallhity) : LONG_MAX;
    verthitdistance = (vert.fhwv) ? distance_between_points(map->player.x, map->player.y, vert.wallhitx, vert.wallhity) : LONG_MAX;
    if (verthitdistance < horzhitdistance )
    {
        map->player.rays[i].distance = verthitdistance;
        map->player.rays[i].wallHX = vert.wallhitx;
        map->player.rays[i].wallHY = vert.wallhity;
        // map->player.rays[i].wallHitContent = vert.content;
        map->player.rays[i].isv = 1;
    }
    else
    {
        map->player.rays[i].distance = horzhitdistance;
        map->player.rays[i].wallHX = horz.wallhitx;
        map->player.rays[i].wallHY = horz.wallhity;
        // map->player.rays[i].wallHitContent = horz.content;
        map->player.rays[i].isv = 0;
    }
    map->player.rays[i].rayA = ra;
    map->player.rays[i].isu = direction.up;
    map->player.rays[i].isd = direction.down;
    map->player.rays[i].isl = direction.left;
    map->player.rays[i].isr = direction.right;
    
}
void castRays(t_map *map)
{
    int i;
    double ra;

    i = 0;
    if (!map)
        return ;
    ra = map->player.rotationAngle - (FOV_ANGLE / 2);
    while (i < NB_RAYS)
    {
        castr(map, ra, i);
        ra += FOV_ANGLE / NB_RAYS;
        i++;
    }
}
// void mouse_press(double x, double y, void *mlx)
// {
//     t_map *map;

//     map = mlx;
//     if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
//     {
//         if (map->prev != -1)
//         {
//             map->player.rotationAngle += (x - map->prev) * 0.00008;
//         }
//         else
//             map->prev = x;
//     }
//     else
//         map->prev = -1;
// }