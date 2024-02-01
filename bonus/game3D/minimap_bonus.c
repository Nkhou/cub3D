/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:33:04 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/02/01 13:21:44 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	find_player(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	if (!map)
		return ;
	while (map->map1[i])
	{
		j = 0;
		while (map->map1[i][j])
		{
			if (map->map1[i][j] && (map->map1[i][j] == 'N'
			|| map->map1[i][j] == 'S'
			|| map->map1[i][j] == 'W' || map->map1[i][j] == 'E'))
			{
				map->player.y = (i) * TILE_SIZE + TILE_SIZE / 2;
				map->player.x = j * TILE_SIZE + TILE_SIZE / 2;
				map->dr = map->map1[i][j];
				map->map1[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

void	draw_player(t_map *map)
{
	int	px;
	int	py;

	py = 140;
	while (py < 160)
	{
		px = 140;
		while (px < 160)
		{
			if (distance_between_points(px, py, 150, 150) <= 5)
				mlx_put_pixel(map->img, px, py, 0xF8E559);
			px++;
		}
		py++;
	}
}

void	draw_minmap(t_map *map, t_min *min)
{
	if (map->map1[(int)(min->y / TILE_SIZE)]
		&& map->map1[(int)(min->y / TILE_SIZE)] \
		[(int)(min->x / TILE_SIZE)] == '1')
		mlx_put_pixel(map->img, min->j, min->i, 0xFFFFFFFF);
	else if (map->map1[(int)(min->y / TILE_SIZE)]
	&& map->map1[(int)(min->y / TILE_SIZE)] \
	[(int)(min->x / TILE_SIZE)] == '0')
		mlx_put_pixel(map->img, min->j, min->i, 0x00000000);
	else if (map->map1[(int)(min->y / TILE_SIZE)]
	&& map->map1[(int)(min->y / TILE_SIZE)] \
	[(int)(min->x / TILE_SIZE)] == 'D')
		mlx_put_pixel(map->img, min->j, min->i, 0xFFFFFF);
	else
		mlx_put_pixel(map->img, min->j, min->i, 0x00000000);
	min->j++;
	min->x++;
}

void	minimap(t_map *map)
{
	t_min	min;

	min.y = map->player.y - 150;
	min.i = 0;
	while (min.i < 300)
	{
		min.j = 0;
		min.x = map->player.x - 150;
		while (min.j < 300)
		{
			if ((int)(min.x / TILE_SIZE) < 0
				|| (int)(min.x / TILE_SIZE) > map->width
				|| (int)(min.y / TILE_SIZE) < 0
				|| (int)(min.y / TILE_SIZE) > map->height)
			{
				min.j++;
				min.x++;
				continue ;
			}
			draw_minmap(map, &min);
		}
		min.i++;
		min.y++;
	}
	draw_player(map);
}

void	intial_mlx(t_map *map)
{
	map->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!map->mlx)
	{
		error_in_draw();
		return ;
	}
	map->img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	if (!map->img)
	{
		mlx_close_window(map->mlx);
		error_in_draw();
	}
	if (mlx_image_to_window(map->mlx, map->img, 0, 0) == -1)
	{
		mlx_close_window(map->mlx);
		error_in_draw();
	}
}
