/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:02:31 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/02/01 13:21:07 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	map_wall(double x, double y, t_map *map)
{
	double	mapgridindexx;
	double	mapgridindexy;

	if (x < 0 || x > map->width * TILE_SIZE
		|| y < 0 || y > map->height * TILE_SIZE)
		return (1);
	mapgridindexx = (int)floor((double)x / (double)TILE_SIZE);
	mapgridindexy = (int)floor((double)y / (double)TILE_SIZE);
	if (!map->map1[(int)mapgridindexy]
		|| map->map1[(int)mapgridindexy][(int)mapgridindexx] == '1'
		|| map->map1[(int)mapgridindexy][(int)mapgridindexx] == 'D')
		return (1);
	return (0);
}

void	initial_data(t_map *map)
{
	if (!map)
		error_in_draw();
	if (map->map1[(int)map->player.y / TILE_SIZE][(int)map->player.x \
		/ TILE_SIZE] == 'N')
		map->player.ra = 1.5 * M_PI;
	else if (map->map1[(int)map->player.y / TILE_SIZE][(int)map->player.x \
		/ TILE_SIZE] == 'S')
		map->player.ra = 0.5 * M_PI;
	else if (map->map1[(int)map->player.y / TILE_SIZE][(int)map->player.x \
		/ TILE_SIZE] == 'E')
		map->player.ra = M_PI;
	else if (map->map1[(int)map->player.y / TILE_SIZE][(int)map->player.x \
		/ TILE_SIZE] == 'W')
		map->player.ra = 0;
	map->player.td = 0;
	map->player.wd = 0;
	map->player.wlr = 0;
	map->player.ws = 8;
	map->player.ts = 3 * (M_PI / 180);
	map->player.d = 0;
	map->prev = -1;
	map->fav = 60 * (M_PI / 180);
}

void	key_release(mlx_key_data_t keydata, t_map *map)
{
	if ((keydata.key == MLX_KEY_W) && (keydata.action == MLX_RELEASE))
		map->player.wd = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		map->player.wd = 0;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		map->player.wlr = 0;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		map->player.wlr = 0;
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_RELEASE))
		map->player.td = 0;
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_RELEASE))
		map->player.td = 0;
}

void	key_press(mlx_key_data_t keydata, void *mlx)
{
	t_map	*map;

	map = mlx;
	if ((keydata.key == MLX_KEY_S) && (keydata.action == MLX_PRESS))
		map->player.wd = -1;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS))
		map->player.wd = 1;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		map->player.wlr = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		map->player.wlr = 1;
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS))
		map->player.td = -1;
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS))
		map->player.td = 1;
	else if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS))
	{
		exit(0);
	}
	key_release(keydata, map);
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
