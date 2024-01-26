/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:01:04 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/26 14:08:14 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

// void	inttocheck(t_horz *h, t_direction direction, int i)
// {
// 	if (i)
// 	{
// 		if (direction.up)
// 			h->ytocheck = floor(h->nexty - 1);
// 		else
// 			h->ytocheck = floor(h->nexty);
// 		h->xtocheck = floor(h->nextx);
// 		return ;
// 	}
// 	if (direction.left)
// 		h->xtocheck = floor(h->nextx - 1);
// 	else
// 		h->xtocheck = floor(h->nextx);
// 	h->ytocheck = floor(h->nexty);
// }

// t_hv	stor_ray(t_map *map, t_hv horz, t_horz h, t_direction direction)
// {
// 	while (h.nextx >= 0 && h.nextx <= map->width * TILE_SIZE
// 		&& h.nexty >= 0 && h.nexty <= map->height * TILE_SIZE)
// 	{
// 		inttocheck(&h, direction, 1);
// 		h.xtocheck = floor(h.nextx);
// 		if (h.xtocheck < 0 || h.xtocheck > map->width * TILE_SIZE
// 			|| h.ytocheck < 0 || h.ytocheck > map->height * TILE_SIZE)
// 			break ;
// 		if (map_wall(h.xtocheck, h.ytocheck, map))
// 		{
// 			horz.fhwh = 1;
// 			horz.wallhitx = h.nextx;
// 			horz.wallhity = h.nexty;
// 			horz.content = map->map1[(int)floor(h.ytocheck / TILE_SIZE)] \
// 			[(int)floor(h.xtocheck / TILE_SIZE)];
// 			break ;
// 		}
// 		else
// 		{
// 			h.nextx += h.xstep;
// 			h.nexty += h.ystep;
// 		}
// 	}
// 	return (horz);
// }

t_hv	horz_(t_map *map, double ra, t_direction direction)
{
	t_hv	horz;
	t_horz	h;

	horz.fhwh = 0;
	horz.wallhitx = 0;
	horz.wallhity = 0;
	h.yintercept = floor(map->player.y / TILE_SIZE) * TILE_SIZE;
	if (direction.down)
		h.yintercept += TILE_SIZE;
	h.xintercept = map->player.x + (h.yintercept - map->player.y) / tan(ra);
	h.ystep = TILE_SIZE;
	if (direction.up)
		h.ystep *= -1;
	h.xstep = TILE_SIZE / tan(ra);
	if (direction.left && h.xstep > 0)
		h.xstep *= -1;
	if (direction.right && h.xstep < 0)
		h.xstep *= -1;
	h.nextx = h.xintercept;
	h.nexty = h.yintercept;
	horz = stor_ray(map, horz, h, direction);
	return (horz);
}

t_hv	stor_vert_ray(t_map *map, t_hv vert, t_horz v, t_direction direction)
{
	while (v.nextx >= 0 && v.nextx <= map->width * TILE_SIZE
		&& v.nexty >= 0 && v.nexty <= map->height * TILE_SIZE)
	{
		inttocheck(&v, direction, 0);
		if (v.xtocheck < 0 || v.xtocheck > map->width * TILE_SIZE
			|| v.ytocheck < 0 || v.ytocheck > map->height * TILE_SIZE)
			break ;
		if (map_wall(v.xtocheck, v.ytocheck, map))
		{
			vert.fhwv = 1;
			vert.wallhitx = v.nextx;
			vert.wallhity = v.nexty;
			vert.content = map->map1[(int)floor(v.ytocheck / TILE_SIZE)] \
			[(int)floor(v.xtocheck / TILE_SIZE)];
			break ;
		}
		else
		{
			v.nextx += v.xstep;
			v.nexty += v.ystep;
		}
	}
	return (vert);
}

t_hv	incrver(t_horz	v, t_map *map, t_direction direction, double ra)
{
	t_hv	vert;

	vert.fhwv = 0;
	vert.wallhitx = 0;
	vert.wallhity = 0;
	vert.content = 0;
	v.xstep = TILE_SIZE;
	if (direction.left)
		v.xstep *= -1;
	v.ystep = TILE_SIZE * tan(ra);
	if (direction.up && v.ystep > 0)
		v.ystep *= -1;
	if (direction.down && v.ystep < 0)
		v.ystep *= -1;
	v.nextx = v.xintercept;
	v.nexty = v.yintercept;
	vert = stor_vert_ray(map, vert, v, direction);
	return (vert);
}

t_hv	vert_(t_map *map, double ra, t_direction direction)
{
	t_hv	vert;
	t_horz	v;

	v.xintercept = floor(map->player.x / TILE_SIZE) * TILE_SIZE;
	if (direction.right)
		v.xintercept += TILE_SIZE;
	v.yintercept = map->player.y + (v.xintercept - map->player.x) * tan(ra);
	vert = incrver(v, map, direction, ra);
	return (vert);
}