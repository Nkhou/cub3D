/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:01:29 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/27 20:58:22 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	put_in_ray(t_map *map, t_hv hv, int i)
{
	map->player.rays[i].wallhx = hv.wallhitx;
	map->player.rays[i].wallhy = hv.wallhity;
	map->player.rays[i].content = hv.content;
}

void	comm_distance(t_map *map, int i, t_hv horz, t_hv vert)
{
	double	horzhitdistance;
	double	verthitdistance;

	horzhitdistance = LONG_MAX;
	verthitdistance = LONG_MAX;
	if (horz.fhwh)
		horzhitdistance = distance_between_points \
		(map->player.x, map->player.y, horz.wallhitx, horz.wallhity);
	if (vert.fhwv)
		verthitdistance = distance_between_points \
		(map->player.x, map->player.y, vert.wallhitx, vert.wallhity);
	if (vert.fhwv && verthitdistance < horzhitdistance)
	{
		put_in_ray(map, vert, i);
		map->player.rays[i].distance = verthitdistance;
		map->player.rays[i].isv = 1;
	}
	else
	{
		put_in_ray(map, horz, i);
		map->player.rays[i].distance = horzhitdistance;
		map->player.rays[i].isv = 0;
	}
}

double	fix_angle(double ra)
{
	ra = remainder(ra, M_PI * 2);
	if (ra < 0)
		ra = M_PI * 2 + ra;
	return (ra);
}

void	castr(t_map *map, double ra, int i)
{
	t_direction	direction;
	t_hv		horz;
	t_hv		vert;

	ra = fix_angle(ra);
	direction.up = israyfacingup(ra);
	direction.down = !direction.up;
	direction.right = israyfacingright(ra);
	direction.left = !direction.right;
	horz = horz_(map, ra, direction);
	vert = vert_(map, ra, direction);
	comm_distance(map, i, horz, vert);
	map->player.rays[i].raya = ra;
	map->player.rays[i].isu = direction.up;
	map->player.rays[i].isd = direction.down;
	map->player.rays[i].isl = direction.left;
	map->player.rays[i].isr = direction.right;
}

void	castrays(t_map *map)
{
	int		i;
	double	ra;

	i = 0;
	if (!map)
		return ;
	ra = map->player.ra - (map->fav / 2);
	while (i < NB_RAYS)
	{
		castr(map, ra, i);
		ra += map->fav / NB_RAYS;
		i++;
	}
}
