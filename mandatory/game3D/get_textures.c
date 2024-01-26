/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:54:31 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/26 14:09:11 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	rgb_to_int(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a << 0);
}

int	pixels_color_rgb(mlx_texture_t *p, u_int32_t x, u_int32_t y)
{
	int	color;
	int	i;

	if (x >= 0 && x < p->width && y >= 0 && y < p->height)
	{
		i = (y * p->width + x) * p->bytes_per_pixel;
		color = rgb_to_int(p->pixels[i], p->pixels[i + 1], \
		p->pixels[i + 2], p->pixels[i + 3]);
	}
	else
		color = rgb_to_int(0, 0, 0, 255);
	return (color);
}

void	inttocheck(t_horz *h, t_direction direction, int i)
{
	if (i)
	{
		if (direction.up)
			h->ytocheck = floor(h->nexty - 1);
		else
			h->ytocheck = floor(h->nexty);
		h->xtocheck = floor(h->nextx);
		return ;
	}
	if (direction.left)
		h->xtocheck = floor(h->nextx - 1);
	else
		h->xtocheck = floor(h->nextx);
	h->ytocheck = floor(h->nexty);
}

t_hv	stor_ray(t_map *map, t_hv horz, t_horz h, t_direction direction)
{
	while (h.nextx >= 0 && h.nextx <= map->width * TILE_SIZE
		&& h.nexty >= 0 && h.nexty <= map->height * TILE_SIZE)
	{
		inttocheck(&h, direction, 1);
		h.xtocheck = floor(h.nextx);
		if (h.xtocheck < 0 || h.xtocheck > map->width * TILE_SIZE
			|| h.ytocheck < 0 || h.ytocheck > map->height * TILE_SIZE)
			break ;
		if (map_wall(h.xtocheck, h.ytocheck, map))
		{
			horz.fhwh = 1;
			horz.wallhitx = h.nextx;
			horz.wallhity = h.nexty;
			horz.content = map->map1[(int)floor(h.ytocheck / TILE_SIZE)] \
			[(int)floor(h.xtocheck / TILE_SIZE)];
			break ;
		}
		else
		{
			h.nextx += h.xstep;
			h.nexty += h.ystep;
		}
	}
	return (horz);
}
