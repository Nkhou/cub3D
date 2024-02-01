/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:02:31 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/02/01 13:21:35 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	initial_data(t_map *map)
{
	if (!map)
		error_in_draw();
	if (map->dr == 'N')
		map->player.ra = 1.5 * M_PI;
	else if (map->dr == 'S')
		map->player.ra = 0.5 * M_PI;
	else if (map->dr == 'E')
		map->player.ra = M_PI;
	else if (map->dr == 'W')
		map->player.ra = 0;
	map->player.td = 0;
	map->player.wd = 0;
	map->player.wlr = 0;
	map->player.ws = 8;
	map->player.ts = 3 * (M_PI / 180);
	map->player.direction = 0;
	map->player.d = 0;
	map->player.height = 8;
	map->player.width = 8;
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

void	open_dor(t_map *map)
{
	int	x;
	int	y;

	x = floor(map->player.x / TILE_SIZE);
	y = floor(map->player.y / TILE_SIZE);
	if (map->map1[y] && map->map1[y][x + 1] == 'D')
		map->map1[y][x + 1] = 'd';
	else if (map->map1[y] && map->map1[y][x - 1] == 'D')
		map->map1[y][x - 1] = 'd';
	else if (map->map1[y + 1] && map->map1[y + 1][x] == 'D')
		map->map1[y + 1][x] = 'd';
	else if (map->map1[y - 1] && map->map1[y - 1][x] == 'D')
		map->map1[y - 1][x] = 'd';
}

void	close_dor(t_map *map)
{
	int	x;
	int	y;

	x = floor(map->player.x / TILE_SIZE);
	y = floor(map->player.y / TILE_SIZE);
	if (map->map1[y] && map->map1[y][x + 1] == 'd')
		map->map1[y][x + 1] = 'D';
	else if (map->map1[y] && map->map1[y][x - 1] == 'd')
		map->map1[y][x - 1] = 'D';
	else if (map->map1[y + 1] && map->map1[y + 1][x] == 'd')
		map->map1[y + 1][x] = 'D';
	else if (map->map1[y - 1] && map->map1[y - 1][x] == 'd')
		map->map1[y - 1][x] = 'D';
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
	else if (keydata.key == MLX_KEY_O)
		open_dor(map);
	else if (keydata.key == MLX_KEY_C)
		close_dor(map);
	else if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS))
	{
		mlx_close_window(map->mlx);
		exit(0);
	}
	key_release(keydata, map);
}
