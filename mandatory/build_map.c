/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:01:04 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/25 14:12:25 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"
// t_hv stor_ray(t_map *map, t_hv horz, t_horz h, t_direction direction)
// {
//     while (h.nextx >= 0 && h.nextx <= map->width * TILE_SIZE && h.nexty >= 0 && h.nexty <= map->height * TILE_SIZE)
//     {
//         h.xtocheck = floor(h.nextx);
//         if (direction.up)
//             h.ytocheck = floor(h.nexty - 1);
//         else
//             h.ytocheck = floor(h.nexty);
//         if (h.xtocheck < 0 || h.xtocheck > map->width * TILE_SIZE || h.ytocheck < 0 || h.ytocheck > map->height * TILE_SIZE)
//             break;
//         if (map_wall(h.xtocheck, h.ytocheck, map))
//         {
//             horz.fhwh = 1;
//             horz.wallhitx = h.nextx;
//             horz.wallhity = h.nexty;
//             horz.content = map->map1[(int)floor(h.ytocheck / TILE_SIZE)][(int)floor(h.xtocheck / TILE_SIZE)];
//             break;
//         }
//         else
//         {
//             h.nextx += h.xstep;
//             h.nexty += h.ystep;
//         }
//     }
//     return (horz);
// }
// t_hv horz_(t_map *map, double ra, t_direction direction)
// {
//     t_hv horz;
//     t_horz h;

//     horz.fhwh = 0;
//     horz.wallhitx = 0;
//     horz.wallhity = 0;
//     h.yintercept = floor(map->player.y / TILE_SIZE) * TILE_SIZE;
//     if (direction.down) // looking down
//         h.yintercept += TILE_SIZE;
//     h.xintercept = map->player.x + (h.yintercept - map->player.y) / tan(ra);
//     h.ystep = TILE_SIZE;
//     if (direction.up) // looking up
//         h.ystep *= -1;
//     h.xstep = TILE_SIZE / tan(ra);
//     if (direction.left && h.xstep > 0) // looking left
//         h.xstep *= -1;
//     if (direction.right && h.xstep < 0) // looking right
//         h.xstep *= -1;
//     h.nextx = h.xintercept;
//     h.nexty = h.yintercept;
//     horz = stor_ray(map, horz, h, direction);
//     return (horz);
// }
// t_hv stor_vert_ray(t_map *map, t_hv vert, t_horz v, t_direction direction)
// {
//      while (v.nextx >= 0 && v.nextx <= map->width * TILE_SIZE && v.nexty >= 0 && v.nexty <= map->height * TILE_SIZE)
//     {
//         if (direction.left) // looking left
//             v.xtocheck = floor(v.nextx - 1);
//         else // looking right (right is positive
//             v.xtocheck = floor(v.nextx);
//         v.ytocheck = floor(v.nexty);
//         if (v.xtocheck < 0 || v.xtocheck > map->width * TILE_SIZE || v.ytocheck < 0 || v.ytocheck > map->height * TILE_SIZE)
//             break;
//         if (map_wall(v.xtocheck, v.ytocheck, map))
//         {
//             vert.fhwv = 1;
//             vert.wallhitx = v.nextx;
//             vert.wallhity = v.nexty;
//             vert.content = map->map1[(int)floor(v.ytocheck / TILE_SIZE)][(int)floor(v.xtocheck / TILE_SIZE)];
//             break;
//         }
//         else
//         {
//             v.nextx += v.xstep;
//             v.nexty += v.ystep;
//         }
//     }
//     return (vert);
// }
// t_hv incrver(double x, double y, t_map *map, t_direction direction, double ra)
// {
//     t_hv vert;
//     t_horz v;

//     vert.fhwv= 0;
//     vert.wallhitx = 0;
//     vert.wallhity = 0;
//     vert.content = 0;
//     v.xstep = TILE_SIZE;
//     if (direction.left) 
//         v.xstep *= -1;
//     v.ystep = TILE_SIZE * tan(ra);
//     if (direction.up && v.ystep > 0)
//         v.ystep *= -1;
//     if (direction.down && v.ystep < 0)
//         v.ystep *= -1;
//     v.nextx = x;
//     v.nexty = y;
//     vert = stor_vert_ray(map, vert, v, direction);
//     return (vert);
// }
// t_hv vert_(t_map *map, double ra, t_direction direction)
// {
//     double xintercept;
//     double yintercept;
//     t_hv vert;

//     xintercept = floor(map->player.x / TILE_SIZE) * TILE_SIZE;
//     if (direction.right)
//         xintercept += TILE_SIZE;
//     yintercept = map->player.y + (xintercept - map->player.x) * tan(ra);
//     vert = incrver(xintercept, yintercept, map, direction, ra);
//     return (vert);
// }
// // void comm_distance(t_map *map, int i, t_hv horz, t_hv vert)
// // {
// //     double horzhitdistance;
// //     double verthitdistance;

// //     if (horz.fhwh)
// //         horzhitdistance = distance_between_points(map->player.x, map->player.y, horz.wallhitx, horz.wallhity);
// //     else
// //         horzhitdistance = LONG_MAX;
// //     if (vert.fhwv)
// //         verthitdistance = distance_between_points(map->player.x, map->player.y, vert.wallhitx, vert.wallhity);
// //     else
// //         verthitdistance = LONG_MAX;
// //     if (verthitdistance < horzhitdistance)
// //     {
// //         map->player.rays[i].distance = verthitdistance;
// //         map->player.rays[i].wallHX = vert.wallhitx;
// //         map->player.rays[i].wallHY = vert.wallhity;
// //         map->player.rays[i].content = vert.content;
// //         map->player.rays[i].isv = 1;
// //     }
// //     else
// //     {
// //         map->player.rays[i].distance = horzhitdistance;
// //         map->player.rays[i].wallHX = horz.wallhitx;
// //         map->player.rays[i].wallHY = horz.wallhity;
// //         map->player.rays[i].content = horz.content;
// //         map->player.rays[i].isv = 0;
// //     }
// // }
