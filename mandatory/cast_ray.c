/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:01:29 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/24 21:11:28 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"
t_hv horz_(t_map *map, double ra, t_direction direction)
{
    t_hv horz;
    t_horz h;

    h.horzwallhity = 0;
    h.foundhorzwallhit = 0;
    h.yintercept = floor(map->player.y / TILE_SIZE) * TILE_SIZE;
    if (direction.down) // looking down
        h.yintercept += TILE_SIZE;
    h.xintercept = map->player.x + (h.yintercept - map->player.y) / tan(ra);
    h.ystep = TILE_SIZE;
    if (direction.up) // looking up
        h.ystep *= -1;
    h.xstep = TILE_SIZE / tan(ra);
    if (direction.left && h.xstep > 0) // looking left
        h.xstep *= -1;
    if (direction.right && h.xstep < 0) // looking right
        h.xstep *= -1;
    h.nextx = h.xintercept;
    h.nexty = h.yintercept;
    while (h.nextx >= 0 && h.nextx <= map->width * TILE_SIZE && h.nexty >= 0 && h.nexty <= map->height * TILE_SIZE)
    {
        h.xtocheck = floor(h.nextx);
        if (direction.up)
            h.ytocheck = floor(h.nexty - 1);
        else
            h.ytocheck = floor(h.nexty);
        if (h.xtocheck < 0 || h.xtocheck > map->width * TILE_SIZE || h.ytocheck < 0 || h.ytocheck > map->height * TILE_SIZE)
            break;
        if (map_wall(h.xtocheck, h.ytocheck, map))
        {
            h.foundhorzwallhit = 1;
            h.horzwallhitx = h.nextx;
            h.horzwallhity = h.nexty;
            horz.content = map->map1[(int)floor(h.ytocheck / TILE_SIZE)][(int)floor(h.xtocheck / TILE_SIZE)];
            break;
        }
        else
        {
            h.nextx += h.xstep;
            h.nexty += h.ystep;
        }
    }
    horz.wallhitx = h.horzwallhitx;
    horz.wallhity = h.horzwallhity;
    horz.fhwh = h.foundhorzwallhit;
    return (horz);
}

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
    while (nextvertTouchX >= 0 && nextvertTouchX <= map->width * TILE_SIZE && nextvertTouchY >= 0 && nextvertTouchY <= map->height * TILE_SIZE)
    {
        xtocheck = floor(nextvertTouchX + (direction.left ? -1 : 0));
        ytocheck = floor(nextvertTouchY);
        if (xtocheck < 0 || xtocheck > map->width * TILE_SIZE || ytocheck < 0 || ytocheck > map->height * TILE_SIZE)
            break;
        if (map_wall(xtocheck, ytocheck, map))
        {
            vert.fhwv = 1;
            vert.wallhitx = nextvertTouchX;
            vert.wallhity = nextvertTouchY;
            vert.content = map->map1[(int)floor(ytocheck / TILE_SIZE)][(int)floor(xtocheck / TILE_SIZE)];
            break;
        }
        else
        {
            nextvertTouchX += step.xstep;
            nextvertTouchY += step.ystep;
        }
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
void comm_distance(t_map *map, int i, t_hv horz, t_hv vert)
{
    double horzhitdistance;
    double verthitdistance;

    horzhitdistance = (horz.fhwh) ? distance_between_points(map->player.x, map->player.y, horz.wallhitx, horz.wallhity) : LONG_MAX;
    verthitdistance = (vert.fhwv) ? distance_between_points(map->player.x, map->player.y, vert.wallhitx, vert.wallhity) : LONG_MAX;
    if (verthitdistance < horzhitdistance)
    {
        map->player.rays[i].distance = verthitdistance;
        map->player.rays[i].wallHX = vert.wallhitx;
        map->player.rays[i].wallHY = vert.wallhity;
        map->player.rays[i].content = vert.content;
        map->player.rays[i].isv = 1;
    }
    else
    {
        map->player.rays[i].distance = horzhitdistance;
        map->player.rays[i].wallHX = horz.wallhitx;
        map->player.rays[i].wallHY = horz.wallhity;
        map->player.rays[i].content = horz.content;
        map->player.rays[i].isv = 0;
    }
}

double fix_angle(double ra)
{
    ra = remainder(ra, TWO_PI);
    if (ra < 0)
        ra = TWO_PI + ra;
    return (ra);
}

void castr(t_map *map, double ra, int i)
{
    t_direction direction;
    t_hv horz;
    t_hv vert;

    ra = fix_angle(ra);
    direction.up = israyfacingup(ra);
    direction.down = !direction.up;
    direction.right = israyfacingright(ra);
    direction.left = !direction.right;
    horz = horz_(map, ra, direction);
    vert = vert_(map, ra, direction);
    comm_distance(map, i, horz, vert);
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