/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:01:29 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/25 21:18:00 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void comm_distance(t_map *map, int i, t_hv horz, t_hv vert)
{
    double horzhitdistance;
    double verthitdistance;

    horzhitdistance = LONG_MAX;
    verthitdistance = LONG_MAX;
    if (horz.fhwh)
        horzhitdistance = distance_between_points(map->player.x, map->player.y, horz.wallhitx, horz.wallhity);
    if (vert.fhwv)
        verthitdistance = distance_between_points(map->player.x, map->player.y, vert.wallhitx, vert.wallhity);
    if (vert.fhwv && verthitdistance < horzhitdistance)
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