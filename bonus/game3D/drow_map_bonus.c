/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drow_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:07:16 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/26 16:01:00 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	draw_3d_line(t_map *map, int i)
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

void	draw_c_f(t_map *map, int i)
{
	int	j;

	j = 0;
	while (j < HEIGHT / 2)
	{
		mlx_put_pixel(map->img, i, j, \
		rgb_to_int(map->ceil->r, map->ceil->g, map->ceil->b, 255));
		j++;
	}
	j = HEIGHT / 2;
	while (j < HEIGHT)
	{
		mlx_put_pixel(map->img, i, j, \
		rgb_to_int(map->floor->r, map->floor->g, map->floor->b, 255));
		j++;
	}
}

double	callculate_texture_x(t_map *map, int i, int text)
{
	double	xo;
	double	tex_x;

	xo = 0;
	if (text == NORTH || text == SOUTH || (text == DOOR && !map->player.rays[i].isv))
        xo = (int)fmodf(map->player.rays[i].wallHX, TILE_SIZE);
    else if ((text == DOOR && map->player.rays[i].isv))
        xo = (int)fmodf(map->player.rays[i].wallHY, TILE_SIZE);
    else if (text == EAST || text == WEST)
        xo = (int)fmodf(map->player.rays[i].wallHY, TILE_SIZE);
	tex_x = xo * (map->texture[text]->width / TILE_SIZE);
	if (tex_x < 0)
		tex_x = 0;
	return (tex_x);
}

void	pp(t_map *map, int i, t_projection p)
{
	int			text;
	double		factor;
	uint32_t	*arr;
	double		tex_x;
	double		yo;

	text = draw_3d_line(map, i);
	if (text == -1)
		return ;
	factor = (double)map->texture[text]->height / p.wallstripheight;
	arr = (u_int32_t *)map->texture[text]->pixels;
	tex_x = callculate_texture_x(map, i, text);
	yo = (p.walltoppixel - (HEIGHT / 2) + (p.wallstripheight / 2)) * factor;
	if (yo < 0)
		yo = 0;
	while (p.walltoppixel < p.wallbottompixel)
	{
		if (yo >= map->texture[text]->height)
			yo = map->texture[text]->height - 1;
		mlx_put_pixel(map->img, i, p.walltoppixel, \
		arr[(int)yo * map->texture[text]->width + (int)tex_x]);
		yo += factor;
		p.walltoppixel++;
	}
}

void	generate_3d_projection(t_map *map)
{
	int				i;
	t_projection	p;

	i = 0;
	while (i < WIDTH)
	{
		if (map->player.rays[i].distance == 0)
			map->player.rays[i].distance = 1;
		p.perpDistance = map->player.rays[i].distance
			* cos(map->player.rays[i].rayA - map->player.rA);
		p.distanceprojplane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
		p.projwallheight = (TILE_SIZE / p.perpDistance) * p.distanceprojplane;
		p.wallstripheight = p.projwallheight;
		p.walltoppixel = (HEIGHT / 2) - (p.wallstripheight / 2);
		p.wallbottompixel = (HEIGHT / 2) + (p.wallstripheight / 2);
		if (p.walltoppixel < 0)
			p.walltoppixel = 0;
		if (p.wallbottompixel > HEIGHT)
			p.wallbottompixel = HEIGHT;
		draw_c_f(map, i);
		pp(map, i, p);
		i++;
	}
}
